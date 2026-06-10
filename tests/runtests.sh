#!/bin/sh
# Script to run tests
#
# Version: 20260609

if test -f ${PWD}/libcdatetime/.libs/libcdatetime.1.dylib && test -f ./pycdatetime/.libs/pycdatetime.so
then
	install_name_tool -change /usr/local/lib/libcdatetime.1.dylib ${PWD}/libcdatetime/.libs/libcdatetime.1.dylib ./pycdatetime/.libs/pycdatetime.so
fi

make check-build > /dev/null

make check $@
RESULT=$?

if test ${RESULT} -ne 0
then
	find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

