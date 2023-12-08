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

## Individual contributions

### Designing the OpenAI ChatGPT and prompt

#### Contributers
- Brian Tran
- Rahul Thakur

This contribution focused on seamlessly integrating the powerful OpenAI ChatGPT model into PostgreSQL for natural language interaction with the database.
The design involved creating a robust interface to communicate with the ChatGPT API, enabling users to pose database-related queries in a conversational format.

#### Key Achievements: 

**API Integration**: Implemented a reliable connection to the ChatGPT API, allowing dynamic communication between the PostgreSQL extension and the natural language model.

**Prompt Generation**: Developed a sophisticated prompt generation mechanism that leverages the database schema information. The prompts are intelligently crafted to seek SQL queries from users in a natural and context-aware manner.

**Security Measures**: Implemented security measures to prevent SQL injection risks, ensuring that queries generated from natural language prompts are safe for execution.

**Error Handling**: Implemented robust error handling to gracefully manage cases where the natural language prompts may lead to invalid or insecure SQL queries

This contribution plays a pivotal role in enhancing the usability of NL_AI, making it intuitive and efficient for users to interact with PostgreSQL databases using natural language queries. The thoughtful design choices aim to provide a seamless and secure experience for users leveraging the power of ChatGPT for database interactions.

### Designing PostgreSQL Extension for Natural Language Interaction

#### Contributers

- Yashwanth Thummala

This contribution focused on architecting a PostgreSQL extension, NL_AI, to empower users with natural language interaction capabilities for querying databases. This extension seamlessly integrates with the ChatGPT model, allowing users to interact with PostgreSQL databases using conversational prompts.

#### Key Achievements:

**Database Schema Query**: Implemented a function to dynamically query the database schema, providing users with detailed information about tables, columns, and key constraints. This information serves as the foundation for generating context-aware prompts.

**SQL Query Execution**: Developed a robust mechanism for executing SQL queries generated from natural language prompts. The extension ensures secure and efficient execution of user queries on the PostgreSQL database.

**User Prompt Preparation**: Designed a function for crafting user prompts based on the retrieved database schema. These prompts guide users in formulating SQL queries, enhancing the user experience, and promoting effective communication with the database.

**Error Handling and Security**: Implemented comprehensive error handling mechanisms to address potential issues during query execution—additionally, integrated security measures to prevent SQL injection risks, ensuring the integrity of the database.

**Readability and Usability**: Prioritized readability and usability in the design of NL_AI, making it accessible for users with varying levels of SQL proficiency. The extension aims to simplify the interaction with databases, especially for users less familiar with SQL syntax.

### Project report generation and Presentation/Demo

#### Contributors

- Brian Tran (Project report and presentation)
- Rahul Thakur (Project report and presentation)
- Yashwanth Thummala (Project Demo)

In this role, the primary responsibility was to create a comprehensive project report and develop materials for an effective presentation/demo showcasing the NL_AI PostgreSQL extension. This involved synthesizing technical details, design choices, and implementation insights into a coherent narrative for both written and visual communication.

#### Key Achievements:

**Project Report**: Compiled a detailed project report that provides an in-depth overview of the NL_AI PostgreSQL extension. The report covers aspects such as project objectives, design considerations, implementation details, challenges faced, and solutions devised. It serves as a comprehensive documentation resource for developers, contributors, and users.

**Technical Documentation**: Authored technical documentation for the NL_AI extension, outlining installation procedures, usage guidelines, and code documentation. Ensured that the technical documentation aligned with industry standards and facilitated a smooth onboarding process for everyone.

**Presentation Development**: Designed an engaging and informative presentation deck for the project. The presentation strategically highlights key features, benefits, and the innovative integration of ChatGPT with PostgreSQL for natural language interactions. Visual aids and demonstrations are incorporated to enhance understanding.

**Live Demo Preparation**: Orchestrated the preparation of a live demonstration showcasing the NL_AI extension in action. The live demo effectively illustrates the practical application of natural language queries in a database context, emphasizing the user-friendly and intuitive nature of the extension.



