#include "postgres.h"
#include "fmgr.h"
#include "utils/builtins.h"
#include "lib/stringinfo.h"
#include "curl/curl.h"
#include "chatgpt_api.h"

/* Helper function to append data to a StringInfo buffer */
static size_t write_response(void *ptr, size_t size, size_t nmemb, StringInfoData *response) {
    size_t real_size = size * nmemb;
    appendBinaryStringInfo(response, ptr, real_size);
    return real_size;
}

/* Function to call the ChatGPT API */
Datum
call_chatgpt_api(text *api_key, text *prompt) {
    CURL *curl;
    CURLcode res;
    struct curl_slist *headers = NULL;
    StringInfoData response;

    // Initialize a dynamic string buffer for the response
    initStringInfo(&response);

    // Initialize a CURL handle
    curl = curl_easy_init();
    if (curl) {
        // Set the URL for the OpenAI API
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/engines/davinci-codex/completions");

        // Prepare headers
        char *auth_header;
        asprintf(&auth_header, "Authorization: Bearer %s", text_to_cstring(api_key));
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, auth_header);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Set POST fields
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, text_to_cstring(prompt));

        // Set a function to handle the response
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_response);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        // Cleanup
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
        free(auth_header);
    }

    // Convert the response to a PostgreSQL text*
    text *result = cstring_to_text(response.data);
    pfree(response.data);

    // Return the response
    PG_RETURN_TEXT_P(result);
}
