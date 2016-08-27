AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATETIME_DLL_IMPORT@

TESTS = \
	test_api_functions.sh \
	test_api_types.sh

check_SCRIPTS = \
	test_api_functions.sh \
	test_api_types.sh \
	test_runner.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	cdatetime_test_elements \
	cdatetime_test_error \
	cdatetime_test_get_version \
	cdatetime_test_timestamp

cdatetime_test_elements_SOURCES = \
	cdatetime_test_elements.c \
	cdatetime_test_libcdatetime.h \
	cdatetime_test_libcerror.h \
	cdatetime_test_libcstring.h \
	cdatetime_test_macros.h \
	cdatetime_test_memory.c cdatetime_test_memory.h \
	cdatetime_test_unused.h

cdatetime_test_elements_LDADD = \
	../libcdatetime/libcdatetime.la \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

cdatetime_test_error_SOURCES = \
	cdatetime_test_error.c \
	cdatetime_test_libcdatetime.h \
	cdatetime_test_libcerror.h \
	cdatetime_test_macros.h \
	cdatetime_test_unused.h

cdatetime_test_error_LDADD = \
	../libcdatetime/libcdatetime.la \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

cdatetime_test_get_version_SOURCES = \
	cdatetime_test_get_version.c \
	cdatetime_test_libcdatetime.h \
	cdatetime_test_libcstring.h \
	cdatetime_test_macros.h \
	cdatetime_test_unused.h

cdatetime_test_get_version_LDADD = \
	../libcdatetime/libcdatetime.la \
	@LIBCSTRING_LIBADD@

cdatetime_test_timestamp_SOURCES = \
	cdatetime_test_timestamp.c \
	cdatetime_test_libcdatetime.h \
	cdatetime_test_libcerror.h \
	cdatetime_test_libcstring.h \
	cdatetime_test_macros.h \
	cdatetime_test_memory.c cdatetime_test_memory.h \
	cdatetime_test_unused.h

cdatetime_test_timestamp_LDADD = \
	../libcdatetime/libcdatetime.la \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

