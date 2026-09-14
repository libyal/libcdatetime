#!/bin/sh
# Script to run tests
#
# Version: 20260714

if [ -f "${PWD}/libcdatetime/.libs/libcdatetime.1.dylib" ] && [ -f ./pycdatetime/.libs/pycdatetime.so ]
then
    install_name_tool -change /usr/local/lib/libcdatetime.1.dylib "${PWD}/libcdatetime/.libs/libcdatetime.1.dylib" ./pycdatetime/.libs/pycdatetime.so
fi

make check-build > /dev/null

# shellcheck disable=SC2068
make check $@
RESULT=$?

if [ ${RESULT} -ne 0 ]
then
    find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

