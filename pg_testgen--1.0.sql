/* contrib/pg_testgen/pg_testgen--1.0.sql */

-- complain if script is sourced in psql, rather than via CREATE EXTENSION
\echo Use "CREATE EXTENSION pg_testgen" to load this file. \quit

CREATE FUNCTION rand_int()
RETURNS integer
AS 'MODULE_PATHNAME', 'rand_int'
LANGUAGE C STRICT;

CREATE FUNCTION rand_int(integer, integer)
RETURNS integer
AS 'MODULE_PATHNAME', 'rand_int'
LANGUAGE C STRICT;

CREATE FUNCTION rand_text()
RETURNS text
AS 'MODULE_PATHNAME', 'rand_text'
LANGUAGE C STRICT;

CREATE FUNCTION rand_text(integer)
RETURNS text
AS 'MODULE_PATHNAME', 'rand_text'
LANGUAGE C STRICT;

CREATE FUNCTION rand_text(integer, integer)
RETURNS text
AS 'MODULE_PATHNAME', 'rand_text'
LANGUAGE C STRICT;

CREATE FUNCTION rows_int(integer)
RETURNS SETOF integer
AS 'MODULE_PATHNAME', 'rows_int'
LANGUAGE C STRICT;

CREATE FUNCTION rows_int(integer, integer, integer)
RETURNS SETOF integer
AS 'MODULE_PATHNAME', 'rows_int'
LANGUAGE C STRICT;

CREATE FUNCTION rows_text(integer)
RETURNS SETOF text
AS 'MODULE_PATHNAME', 'rows_text'
LANGUAGE C STRICT;

CREATE FUNCTION rows_text(integer, integer)
RETURNS SETOF text
AS 'MODULE_PATHNAME', 'rows_text'
LANGUAGE C STRICT;

CREATE FUNCTION rows_text(integer, integer, integer)
RETURNS SETOF text
AS 'MODULE_PATHNAME', 'rows_text'
LANGUAGE C STRICT;
