#!/bin/sh
# Script to run tests
#
# Version: 20201121

if test -f ${PWD}/libcdatetime/.libs/libcdatetime.1.dylib && test -f ./pycdatetime/.libs/pycdatetime.so;
then
	install_name_tool -change /usr/local/lib/libcdatetime.1.dylib ${PWD}/libcdatetime/.libs/libcdatetime.1.dylib ./pycdatetime/.libs/pycdatetime.so;
fi

make check CHECK_WITH_STDERR=1;
RESULT=$?;

if test ${RESULT} -ne 0 && test -f tests/test-suite.log;
then
	cat tests/test-suite.log;
fi
exit ${RESULT};

