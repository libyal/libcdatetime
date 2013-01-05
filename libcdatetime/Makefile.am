AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@

lib_LTLIBRARIES = libcdatetime.la

libcdatetime_la_SOURCES = \
	libcdatetime.c \
	libcdatetime_definitions.h \
	libcdatetime_extern.h \
	libcdatetime_error.c libcdatetime_error.h \
	libcdatetime_narrow_split_string.c libcdatetime_narrow_split_string.h \
	libcdatetime_narrow_string.c libcdatetime_narrow_string.h \
	libcdatetime_libcerror.h \
	libcdatetime_libcstring.h \
	libcdatetime_support.c libcdatetime_support.h \
	libcdatetime_types.h \
	libcdatetime_unused.h \
	libcdatetime_wide_split_string.c libcdatetime_wide_split_string.h \
	libcdatetime_wide_string.c libcdatetime_wide_string.h

libcdatetime_la_LIBADD  = \
	@LIBCSTRING_LIBADD@ \
	@LIBCERROR_LIBADD@

libcdatetime_la_LDFLAGS = -no-undefined -version-info 1:0:0

EXTRA_DIST = \
	libcdatetime_definitions.h.in \
	libcdatetime.rc \
	libcdatetime.rc.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f libcdatetime_definitions.h
	/bin/rm -f libcdatetime.rc
	/bin/rm -f Makefile

splint:
	@echo "Running splint on libcdatetime ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libcdatetime_la_SOURCES)

