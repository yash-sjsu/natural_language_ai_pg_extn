#include "postgres.h"
#include "fmgr.h"
#include "db_queries.h"
#include "chatgpt_api.h"

#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif

PG_FUNCTION_INFO_V1(natural_language_ai);

Datum
natural_language_ai(PG_FUNCTION_ARGS)
{
    // Extract the argument values
    text *token = PG_GETARG_TEXT_P(0);  // The first argument is the API token of chatgpt API
    text *prompt = PG_GETARG_TEXT_P(1); // The second argument is the prompt to be sent to the API

    // fetch the information schema of the database and all its tables
    Datam *database_schema = query_database_schema();   // @todo: Result should be formatted to a format that chatgpt understands


    // @todo: prepare new prompt based on the information schema of the database and all its tables


    // @todo: start the API call to chatgpt
    Datum response = call_chatgpt_api(token, prompt);


    // @todo: extract the SQL string from the response of the API call


    // @todo: execute the SQL against the database
    Datum query_result = execute_query(query);


    // @todo: prepare the response to be sent back to the client from the result of the SQL query
    text *response = cstring_to_text("Hello, world!");

    // Return the response to the client
    PG_RETURN_TEXT_P(response);
}
