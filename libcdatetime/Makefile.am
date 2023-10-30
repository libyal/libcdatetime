AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATETIME_DLL_EXPORT@

lib_LTLIBRARIES = libcdatetime.la

libcdatetime_la_SOURCES = \
	libcdatetime.c \
	libcdatetime_definitions.h \
	libcdatetime_elements.c libcdatetime_elements.h \
	libcdatetime_error.c libcdatetime_error.h \
	libcdatetime_extern.h \
	libcdatetime_libcerror.h \
	libcdatetime_timestamp.c libcdatetime_timestamp.h \
	libcdatetime_support.c libcdatetime_support.h \
	libcdatetime_types.h \
	libcdatetime_unused.h

libcdatetime_la_LIBADD = \
	@LIBCERROR_LIBADD@

libcdatetime_la_LDFLAGS = -no-undefined -version-info 1:0:0

EXTRA_DIST = \
	libcdatetime_definitions.h.in \
	libcdatetime.rc \
	libcdatetime.rc.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	-rm -f libcdatetime_definitions.h
	-rm -f libcdatetime.rc
	-rm -f Makefile

sources-local: $(BUILT_SOURCES)

splint-local:
	@echo "Running splint on libcdatetime ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libcdatetime_la_SOURCES)

