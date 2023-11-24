#ifndef CHATGPT_API_H
#define CHATGPT_API_H

#include "postgres.h"

Datum call_chatgpt(text *api_key, text *prompt);

#endif