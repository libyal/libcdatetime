AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
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
	cdatetime_test_support \
	cdatetime_test_timestamp

cdatetime_test_elements_SOURCES = \
	cdatetime_test_elements.c \
	cdatetime_test_libcdatetime.h \
	cdatetime_test_libcerror.h \
	cdatetime_test_macros.h \
	cdatetime_test_memory.c cdatetime_test_memory.h \
	cdatetime_test_unused.h

cdatetime_test_elements_LDADD = \
	../libcdatetime/libcdatetime.la \
	@LIBCERROR_LIBADD@

cdatetime_test_error_SOURCES = \
	cdatetime_test_error.c \
	cdatetime_test_libcdatetime.h \
	cdatetime_test_macros.h \
	cdatetime_test_unused.h

cdatetime_test_error_LDADD = \
	../libcdatetime/libcdatetime.la

cdatetime_test_support_SOURCES = \
	cdatetime_test_libcdatetime.h \
	cdatetime_test_macros.h \
	cdatetime_test_support.c \
	cdatetime_test_unused.h

cdatetime_test_support_LDADD = \
	../libcdatetime/libcdatetime.la

cdatetime_test_timestamp_SOURCES = \
	cdatetime_test_libcdatetime.h \
	cdatetime_test_libcerror.h \
	cdatetime_test_macros.h \
	cdatetime_test_memory.c cdatetime_test_memory.h \
	cdatetime_test_timestamp.c \
	cdatetime_test_unused.h

cdatetime_test_timestamp_LDADD = \
	../libcdatetime/libcdatetime.la \
	@LIBCERROR_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

