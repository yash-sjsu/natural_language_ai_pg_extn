#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
#include <postgres.h>
#include <fmgr.h>
#include <utils/builtins.h>

// Function to handle the response from CURL
static size_t write_response(void *ptr, size_t size, size_t nmemb, StringInfo str) {
    size_t real_size = size * nmemb;
    appendBinaryStringInfo(str, ptr, real_size);
    return real_size;
}

// Main function to call the ChatGPT API
Datum call_chatgpt_api(text *api_key, char *prompt) {
    CURL *curl;
    CURLcode res;
    struct curl_slist *headers = NULL;
    StringInfoData response;

    // Initialize a dynamic string buffer for the response
    initStringInfo(&response);

    // elog(INFO, "Calling ChatGPT API with prompt: %s", prompt);

    // Initialize a CURL handle
    curl = curl_easy_init();
    if (curl) {
        // Set the URL for the OpenAI API
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/chat/completions");

        // Prepare the authorization header
        char *auth_header;
        asprintf(&auth_header, "Authorization: Bearer %s", text_to_cstring(api_key));
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, auth_header);

        // Construct JSON payload
        char *json_payload;
        asprintf(&json_payload, "{\"model\": \"gpt-3.5-turbo\", \"messages\": [{\"role\": \"user\", \"content\": \"%s\"}], \"max_tokens\": 1024}", prompt);

        // Set the headers and POST fields
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_payload);

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
        free(json_payload);
    }

    // Convert the response to a PostgreSQL text*
    char *full_response = response.data;
    // pfree(response.data);

    // Find the start of the content string
    char *start = strstr(full_response, "\"content\": \"");
    if (start == NULL) {
        elog(ERROR, "Could not find content in response: %s", full_response);
        PG_RETURN_BPCHAR_P("NOT FOUND");
    }
    start += strlen("\"content\": \""); // Move past the "content": "

    // Find the end of the content string, looking for a semicolon
    char *end = strchr(start, ';');
    if (end == NULL) {
        elog(ERROR, "Could not find semicolon in response: %s", full_response);
        PG_RETURN_BPCHAR_P("INVALID RESPONSE");
    }
    end++;

    // Extract the content substring
    char *content = pnstrdup(start, end - start); // Allocate a new string in PostgreSQL's memory context

    // Cleanup
    pfree(response.data);

    // Return the response
    PG_RETURN_TEXT_P(cstring_to_text(content));
}
