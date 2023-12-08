# NL_AI PostgreSQL Extension: natural_language_ai_pg_extn

NL_AI is a PostgreSQL extension that integrates with the ChatGPT API to provide natural language interaction with your PostgreSQL database. It allows you to retrieve the database schema, execute SQL queries, and get responses in a natural language format.

## Prerequisites
Before using this extension, ensure that you have the following:

- PostgreSQL installed on your system.
- ChatGPT API key for interaction with the natural language model.
- CURL library installed.

## Installation

1. Build the extension:

```bash
make install
```

2. Create the extension in your PostgreSQL database:

```
CREATE EXTENSION nl_ai;
```

## Usage

### Execute SQL Query

To execute an SQL query using natural language:

``` SQL
-- Replace 'your_api_key' with your ChatGPT API key
-- Replace 'your_prompt' with your natural language prompt
SELECT nl_ai('your_api_key', 'your_prompt');
```


### Example

```SQL
-- Execute SQL query using natural language
SELECT nl_ai('your_api_key', 'What are the names of all courses?');
```

## Important Note

This extension relies on the ChatGPT API for natural language understanding. Ensure that your API key is valid and accessible.

Installing PostgreSQL in the dev environment is essential for the project to compile.

## Getting API key from OpenAI

Open AI API keys can be created or found at https://platform.openai.com/api-keys

Article on how to generate keys: https://medium.com/@pawan329/how-to-generate-chat-gpt-api-key-daace2acc032

## Installing PostgreSQL
General installation guide on how to install Postgres can be found at https://www.postgresql.org/docs/current/tutorial-install.html




