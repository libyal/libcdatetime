AM_CPPFLAGS = \
	-I../include -I$(top_srcdir)/include \
	-I../common -I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATETIME_DLL_IMPORT@

BUILT_SOURCES = package.m4

check_AUTOTESTS = \
	test_library \
	test_manpages

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
	cdatetime_test_libcerror.h \
	cdatetime_test_macros.h \
	cdatetime_test_support.c \
	cdatetime_test_unused.h

cdatetime_test_support_LDADD = \
	../libcdatetime/libcdatetime.la \
	@LIBCERROR_LIBADD@

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

AUTOM4TE = autom4te
AUTOTEST = $(AUTOM4TE) --language=autotest

SUFFIXES = .at

.at:
	$(AM_V_GEN)rm -f $@ $@.tmp; \
	$(AUTOTEST) -I '$(srcdir)' -o $@.tmp $< && \
	mv $@.tmp $@

atconfig: $(top_builddir)/config.status
	cd $(top_builddir) && $(SHELL) ./config.status tests/$@

check-build: $(check_PROGRAMS)

check-local: $(check_AUTOTESTS)
	@fail=0; \
	for test_suite in $(check_AUTOTESTS); do \
		$(AM_TESTS_ENVIRONMENT) $(SHELL) "./$$test_suite" $(TESTSUITEFLAGS) || fail=1; \
		echo ""; \
	done; \
	exit $$fail

clean-local:
	for test_suite in $(check_AUTOTESTS); do \
		test ! -f "$$test_suite" || $(SHELL) "./$$test_suite" --clean; \
	done

package.m4: $(top_srcdir)/configure.ac
	$(AM_V_GEN):; \
	{ \
	  echo 'm4_define([AT_PACKAGE_NAME], [$(PACKAGE_NAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_TARNAME], [$(PACKAGE_TARNAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_VERSION], [$(PACKAGE_VERSION)])' ; \
	  echo 'm4_define([AT_PACKAGE_STRING], [$(PACKAGE_STRING)])' ; \
	  echo 'm4_define([AT_PACKAGE_BUGREPORT], [$(PACKAGE_BUGREPORT)])' ; \
	} > $@

test_library: package.m4 test_library.at test_macros.at

test_manpages: package.m4 test_macros.at test_manpages.at

EXTRA_DIST = \
	$(check_AUTOTESTS:=.at) \
	package.m4 \
	test_macros.at

CLEANFILES = \
	$(check_AUTOTESTS) \
	*.exe \
	*.tmp

DISTCLEANFILES = \
	*.log \
	atconfig \
	Makefile \
	Makefile.in

