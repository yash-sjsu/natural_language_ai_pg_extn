#ifndef DB_QUERIES_H
#define DB_QUERIES_H

#include "postgres.h"

// this is the function that will be called for getting the schema of a database
Datum query_database_schema();

// this is the function that will be called for executing a general query
Datum execute_query(text *query);

#endif