# contrib/pg_testgen/Makefile

MODULE_big = pg_testgen
OBJS = pg_testgen.o $(WIN32RES) 
PGFILEDESC = "pg_testgen - test data generator"

PG_CPPFLAGS = -I$(libpq_srcdir)
SHLIB_LINK_INTERNAL = $(libpq)

EXTENSION = pg_testgen
DATA = pg_testgen--1.0.sql

REGRESS = pg_testgen # sql、expected 文件夹下的测试，

ifdef USE_PGXS
PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
else
SHLIB_PREREQS = submake-libpq
subdir = contrib/pg_testgen
top_builddir = ../..
include $(top_builddir)/src/Makefile.global
include $(top_srcdir)/contrib/contrib-global.mk
endif
