# Install the pkg-config file.
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = src/libcpaq.pc src/cpaq-test.pc

DISTCLEANFILES = $(pkgconfig_DATA)
EXTRA_DIST = src/libcpaq.pc.in src/libcpaq-test.pc.in

SUBDIRS = src
dist_doc_DATA = README.md
ACLOCAL_AMFLAGS = -I m4

