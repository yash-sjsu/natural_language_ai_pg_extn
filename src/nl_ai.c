#include "postgres.h"
#include "fmgr.h"
#include "db_queries.h"
#include "chatgpt_api.h"
#include "utils/builtins.h"
#include "utils/elog.h"

#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif

PG_FUNCTION_INFO_V1(nl_ai);

Datum
nl_ai(PG_FUNCTION_ARGS)
{
    // Extract the argument values
    text *token = PG_GETARG_TEXT_P(0);  // The first argument is the API token of chatgpt API
    text *prompt = PG_GETARG_TEXT_P(1); // The second argument is the prompt to be sent to the API

    // fetch the information schema of the database and all its tables
    Datum *database_schema = query_database_schema();
    text *database_schema_text = DatumGetCString(database_schema);
    // elog(INFO, "Queried database schema of database, schema: { %s }", text_to_cstring(database_schema_text));

    // prepare new prompt based on the information schema of the database and all its tables
    const char *prompt_template1 = "I have the following schema of my database: [ ";
    const char *prompt_template2 = " ]. Could you give me an sql query compatible with PostgreSQL in a pair of brackets for : [ ";
    const char *prompt_template3 = " ]. Without giving an explanation, if it can't be done say invalid query. "
                                "Don't forget to add semicolon at the end of the query."
                                "I want entire query in a single line no matter how long the generated query is, do not any lines.";

    int prompt_len = strlen(text_to_cstring(prompt)) + strlen(text_to_cstring(database_schema_text)) + strlen(prompt_template1) + strlen(prompt_template2) + strlen(prompt_template3) + 1;
    prompt_len *= 10; // Just to be safe

    char *chatgpt_prompt = (char *) malloc(prompt_len); // Allocate memory for the prompt string
    snprintf(chatgpt_prompt, prompt_len, "%s%s%s%s%s", prompt_template1, text_to_cstring(database_schema_text), prompt_template2, text_to_cstring(prompt), prompt_template3); // Construct the prompt string

    // start the API call to chatgpt
    Datum chatgpt_response = call_chatgpt_api(token, chatgpt_prompt);

    text *gpt_sql_string = DatumGetTextP(chatgpt_response);

    // execute the SQL against the database
    Datum query_result = execute_query(gpt_sql_string);

    // Return the response to the client
    PG_RETURN_TEXT_P(query_result);
}
