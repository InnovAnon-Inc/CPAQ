AM_CPPFLAGS = -D__STDC_INT64__

SUBDIRS = ../glitter
AM_CPPFLAGS += -I $(top_srcdir)/glitter/src

include Makefile-LIBADD.inc

lib_LTLIBRARIES = libcpaq.la
include_HEADERS = cpaq.h
libcpaq_la_LIBADD = $(LIBCPAQ_LIBADD)

bin_PROGRAMS = cpaq-test
cpaq_test_LDADD = libcpaq.la $(LIBCPAQ_LIBADD)
