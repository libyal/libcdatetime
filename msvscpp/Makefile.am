MSVSCPP_FILES = \
	cdatetime_test_elements/cdatetime_test_elements.vcproj \
	cdatetime_test_error/cdatetime_test_error.vcproj \
	cdatetime_test_get_version/cdatetime_test_get_version.vcproj \
	cdatetime_test_timestamp/cdatetime_test_timestamp.vcproj \
	libcdatetime/libcdatetime.vcproj \
	libcerror/libcerror.vcproj \
	libcstring/libcstring.vcproj \
	libcdatetime.sln

SCRIPT_FILES = \
	scripts/vs2008_x64.sh \
	scripts/vs2008_x64_sln.sed \
	scripts/vs2008_x64_vcproj.sed \
	scripts/vs2010_x64.sh \
	scripts/vs2010_x64_sln.sed \
	scripts/vs2010_x64_vcxproj.sed

EXTRA_DIST = \
	$(MSVSCPP_FILES) \
	$(SCRIPT_FILES)

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

