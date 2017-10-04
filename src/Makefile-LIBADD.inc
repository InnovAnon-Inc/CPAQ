include $(top_srcdir)/PArray/src/Makefile-LIBADD.inc
include $(top_srcdir)/StD/src/Makefile-LIBADD.inc

LIBCPAQ_LIBADD = -lparray $(LIBPARRAY_LIBADD)
