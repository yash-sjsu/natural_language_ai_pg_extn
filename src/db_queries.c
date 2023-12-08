#include "postgres.h"
#include "fmgr.h"
#include "funcapi.h"
#include "utils/builtins.h"
#include "executor/spi.h"
#include "db_queries.h"
#include "lib/stringinfo.h"
#include "utils/elog.h"

Datum
query_database_schema() {
    char *query;
    int ret;
    SPIPlanPtr plan;
    SPITupleTable *tuptable;
    TupleDesc tupdesc;
    HeapTuple tuple;
    StringInfoData buf;
    char *last_table = NULL;

    // Initialize a dynamic string buffer for the response
    initStringInfo(&buf);

    // Connect to SPI manager
    SPI_connect();

    // elog(INFO, "connected to database, to query schema");

    // Query to fetch schema, table, column information, and key constraints
    query = "SELECT t.table_schema, t.table_name, c.column_name, "
            "CASE WHEN tc.constraint_type = 'PRIMARY KEY' THEN 'PK' ELSE NULL END AS pk "
            "FROM information_schema.tables t "
            "LEFT JOIN information_schema.columns c ON t.table_schema = c.table_schema AND t.table_name = c.table_name "
            "LEFT JOIN information_schema.key_column_usage kcu ON c.table_schema = kcu.table_schema AND c.table_name = kcu.table_name AND c.column_name = kcu.column_name "
            "LEFT JOIN information_schema.table_constraints tc ON kcu.table_schema = tc.table_schema AND kcu.table_name = tc.table_name AND kcu.constraint_name = tc.constraint_name "
            "WHERE t.table_catalog = 'school' AND t.table_schema = 'public' AND (tc.constraint_type = 'PRIMARY KEY' OR tc.constraint_type IS NULL) "
            "ORDER BY t.table_schema, t.table_name, c.ordinal_position;";

    // Prepare and execute the query
    plan = SPI_prepare(query, 0, NULL);
    ret = SPI_execute_plan(plan, NULL, NULL, true, 0);

    if (ret > 0 && SPI_tuptable != NULL) {
        tuptable = SPI_tuptable;
        tupdesc = tuptable->tupdesc;

        // Process each tuple
        for (int i = 0; i < tuptable->numvals; i++) {
            tuple = tuptable->vals[i];
            char *table_schema = SPI_getvalue(tuple, tupdesc, 1);
            char *table_name = SPI_getvalue(tuple, tupdesc, 2);
            char *column_name = SPI_getvalue(tuple, tupdesc, 3);
            char *pk = SPI_getvalue(tuple, tupdesc, 4);

            // Check if we've moved to a new table
            if (last_table == NULL || strcmp(last_table, table_name) != 0) {
                if (last_table != NULL) {
                    // Not the first table, close the previous table's bracket
                    appendStringInfoChar(&buf, ')');
                    appendStringInfoString(&buf, ", ");
                }
                // Start a new table's column list
                appendStringInfo(&buf, "%s.%s(", table_schema, table_name);
                last_table = table_name;
            } else {
                // Same table, just append a comma for the next column
                appendStringInfoString(&buf, ", ");
            }

            // Append column name and PK if applicable
            appendStringInfo(&buf, "%s", column_name);
            if (pk != NULL) {
                appendStringInfoString(&buf, " - PK");
            }
        }

        // Close the last table's bracket
        appendStringInfoChar(&buf, ')');
    }

    // Disconnect from SPI manager
    SPI_finish();

    // Convert the string buffer to text and return
    text *result = cstring_to_text(buf.data);
    pfree(buf.data);
    // if (last_table != NULL) {
    //     pfree(last_table);
    // }

    PG_RETURN_TEXT_P(result);
}


Datum
execute_query(text *query_text) {
    char *query;
    int ret;
    SPIPlanPtr plan;
    SPITupleTable *tuptable;
    TupleDesc tupdesc;
    HeapTuple tuple;
    StringInfoData buf;

    // Initialize a dynamic string buffer for the response
    initStringInfo(&buf);

    // Convert the input text* to a C string
    query = text_to_cstring(query_text);

    // elog(INFO, "Executing query: %s", query);

    // remove string '\' followed by 'n' from the query and replace them with a space
    char *ptr = strstr(query, "\\n");
    while (ptr != NULL) {
        *ptr = ' ';
        *(ptr + 1) = ' ';
        ptr = strstr(ptr + 2, "\\n");
    }

    // Connect to SPI manager
    SPI_connect();

    // Prepare and execute the query
    plan = SPI_prepare(query, 0, NULL);
    ret = SPI_execute_plan(plan, NULL, NULL, true, 0);

    if (ret > 0 && SPI_tuptable != NULL) {
        tuptable = SPI_tuptable;
        tupdesc = tuptable->tupdesc;
        int ncolumns = tupdesc->natts;

        // Process each tuple
        for (int i = 0; i < SPI_processed; i++) {
            tuple = tuptable->vals[i];

            // Append each column's value for the tuple
            for (int col = 1; col <= ncolumns; col++) {
                char *value = SPI_getvalue(tuple, tupdesc, col);
                appendStringInfo(&buf, "%s%s", value ? value : "NULL", col < ncolumns ? ", " : "");
            }

            // Append a line break after each tuple
            if (i < SPI_processed - 1) {
                appendStringInfoString(&buf, "\n");
            }
        }
    }

    // Disconnect from SPI manager
    SPI_finish();

    // Convert the string buffer to text and return
    text *result = cstring_to_text(buf.data);
    pfree(buf.data);
    pfree(query);
    PG_RETURN_TEXT_P(result);
}
