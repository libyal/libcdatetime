include_HEADERS = \
	libcdatetime.h

pkginclude_HEADERS = \
	libcdatetime/definitions.h \
	libcdatetime/error.h \
	libcdatetime/extern.h \
	libcdatetime/features.h \
	libcdatetime/types.h

EXTRA_DIST = \
	libcdatetime.h.in \
	libcdatetime/definitions.h.in \
	libcdatetime/features.h.in \
	libcdatetime/types.h.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	-rm -f libcdatetime.h
	-rm -f libcdatetime/definitions.h
	-rm -f libcdatetime/features.h
	-rm -f libcdatetime/types.h
	-rm -f Makefile

