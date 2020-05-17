AM_CPPFLAGS = -D__STDC_INT64__

#include Makefile-LIBADD.inc
dist_bin_SCRIPTS = libcpaq_config cpaq_test_config

lib_LTLIBRARIES =
bin_PROGRAMS    =

lib_LTLIBRARIES += libcpaq.la
include_HEADERS = cpaq.h
#libcpaq_la_LIBADD = $(LIBCPAQ_LIBADD)
libcpaq_la_LIBADD = @LIBCPAQ_LIBADD@

#include $(top_srcdir)/StD/src/Makefile-LIBADD.inc

#include ../../StD/src/Makefile-LIBADD.inc
bin_PROGRAMS += cpaq-test
#cpaq_test_LDADD = libcpaq.la $(LIBCPAQ_LIBADD) -lsimon $(LIBSIMON_LIBADD)
#cpaq_test_LDADD = $(CPAQ_TEST_LIBADD)
cpaq_test_LDADD = @CPAQ_TEST_LIBADD@
EXTRA_cpaq_test_DEPENDENCIES = libcpaq.la
