#ifndef CHATGPT_API_H
#define CHATGPT_API_H

#include "postgres.h"

Datum call_chatgpt_api(text *api_key, char *prompt);

#endif