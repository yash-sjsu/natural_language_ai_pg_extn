CREATE OR REPLACE FUNCTION natural_language_ai(
    key    TEXT,
    prompt TEXT,
)RETURNS TEXT AS 'MODULE_PATHNAME', 'natural_language_ai' LANGUAGE C IMMUTABLE;
