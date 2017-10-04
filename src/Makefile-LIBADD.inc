#include $(top_srcdir)/MultiMalloc/src/Makefile-LIBADD.inc
include $(top_srcdir)/PArray/src/Makefile-LIBADD.inc

LIBCPAQ_LIBADD = -lparray $(LIBPARRAY_LIBADD)
