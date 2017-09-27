lib_LTLIBRARIES = libcpaq.la
libcpaq_la_SOURCES = cpaq.c
include_HEADERS = cpaq.h
#libcpaq_la_CFLAGS =

bin_PROGRAMS = cpaq-test
cpaq_test_SOURCES = cpaq-test.c
cpaq_test_LDADD = libcpaq.la
#cpaq_test_CFLAGS =

AM_CPPFLAGS = -D__STDC_INT64__
AM_CPPFLAGS += -I $(srcdir)/../glitter/src
