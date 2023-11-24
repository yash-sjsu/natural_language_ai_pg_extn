#include "postgres.h"
#include "fmgr.h"
#include "funcapi.h"
#include "utils/builtins.h"
#include "executor/spi.h"
#include "db_queries.h"
#include "lib/stringinfo.h"

Datum
query_database_schema() {
    char *query;
    int ret;
    SPIPlanPtr plan;
    SPITupleTable *tuptable;
    TupleDesc tupdesc;
    HeapTuple tuple;
    StringInfoData buf;

    // Initialize a dynamic string buffer
    initStringInfo(&buf);

    // Connect to SPI manager
    SPI_connect();

    char *database_name = "test";

    // Your query to fetch schema information
    query = "SELECT table_schema, table_name FROM information_schema.tables WHERE table_catalog = " + database_name;

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

            // Append to the string buffer
            appendStringInfo(&buf, "%s.%s, ", table_schema, table_name);
        }
    }

    // Disconnect from SPI manager
    SPI_finish();

    // Convert the string buffer to text and return
    text *result = cstring_to_text(buf.data);
    pfree(buf.data);
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

    // Connect to SPI manager
    SPI_connect();

    // Prepare and execute the query
    plan = SPI_prepare(query, 0, NULL);
    ret = SPI_execute_plan(plan, NULL, NULL, true, 0);

    if (ret > 0 && SPI_tuptable != NULL) {
        tuptable = SPI_tuptable;
        tupdesc = tuptable->tupdesc;

        // Process each tuple
        for (int i = 0; i < tuptable->numvals; i++) {
            tuple = tuptable->vals[i];
            // Append the tuple's textual representation to the buffer
            appendStringInfo(&buf, "%s, ", SPI_getvalue(tuple, tupdesc, 1));
            // Depending on your needs, you may need to handle more columns
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
