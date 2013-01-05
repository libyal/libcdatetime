include_HEADERS = \
	libcdatetime.h

pkginclude_HEADERS = \
	libcdatetime/codepage.h \
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
	/bin/rm -f libcdatetime.h
	/bin/rm -f libcdatetime/definitions.h
	/bin/rm -f libcdatetime/features.h
	/bin/rm -f libcdatetime/types.h
	/bin/rm -f Makefile

