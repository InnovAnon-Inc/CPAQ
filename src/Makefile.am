LIBCPAQ_LIBADD =

lib_LTLIBRARIES = libcpaq.la
include_HEADERS = cpaq.h
libcpaq_la_LIBADD = $(LIBCPAQ_LIBADD)

bin_PROGRAMS = cpaq-test
cpaq_test_LDADD = libcpaq.la $(LIBCPAQ_LIBADD)

AM_CPPFLAGS = -D__STDC_INT64__

SUBDIRS = ../glitter
AM_CPPFLAGS += -I ../glitter/src
