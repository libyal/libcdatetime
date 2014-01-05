dnl Functions for libcdatetime
dnl
dnl Version: 20140105

dnl The AX_LIBCDATETIME_CHECK_FUNC_CTIME function is currently not used
dnl but kept as a reference for the time being.

dnl Function to detect if ctime_r or ctime is available
dnl Also checks how to use ctime_r
AC_DEFUN([AX_LIBCDATETIME_CHECK_FUNC_CTIME],
 [AC_CHECK_FUNCS([ctime_r])

 AS_IF(
  [test "x$ac_cv_func_ctime_r" = xyes],
  [AC_MSG_CHECKING(
   [how to use ctime_r])

  AC_LANG_PUSH(C)

  AC_LINK_IFELSE(
   [AC_LANG_PROGRAM(
    [[#include <time.h>]],
    [[ctime_r( NULL, NULL, 0 )]] )],
    [AC_MSG_RESULT(
     [with additional size argument])
    ac_cv_cv_ctime_r_size=yes],
    [ac_cv_cv_ctime_r_size=no])

  AS_IF(
   [test "x$ac_cv_cv_ctime_r_size" = xno],
   [AC_LINK_IFELSE(
    [AC_LANG_PROGRAM(
     [[#include <time.h>]],
     [[ctime_r( NULL, NULL )]] )],
    [AC_MSG_RESULT(
     [with two arguments])
    ac_cv_cv_ctime_r_posix=yes],
    [ac_cv_cv_ctime_r_posix=no])
   ])

  AS_IF(
   [test "x$ac_cv_cv_ctime_r_posix" = xno],
   [CPPFLAGS="$CPPFLAGS -D_POSIX_PTHREAD_SEMANTICS"
   AC_LINK_IFELSE(
    [AC_LANG_PROGRAM(
     [[#include <time.h>]],
     [[ctime_r( NULL, NULL )]] )],
    [AC_MSG_RESULT(
     [with two arguments and definition _POSIX_PTHREAD_SEMANTICS])
     ac_cv_cv_ctime_r_posix=yes],
    [ac_cv_cv_ctime_r_posix=no])
   ])

  AC_LANG_POP(C)

  AS_IF(
   [test "x$ac_cv_cv_ctime_r_size" = xno && test "x$ac_cv_cv_ctime_r_posix" = xno],
   [AC_MSG_WARN(
    [unknown])
   ac_cv_func_ctime_r=no])

  AS_IF(
   [test "x$ac_cv_func_ctime_r" = xyes],
   [AC_DEFINE(
    [HAVE_CTIME_R],
    [1],
    [Define to 1 if you have the ctime_r function.])
   ])

  AS_IF(
   [test "x$ac_cv_cv_ctime_r_size" = xyes],
   [AC_DEFINE(
    [HAVE_CTIME_R_SIZE],
    [1],
    [Define to 1 if you have the ctime_r function with a third size argument.])
   ])
  ])

 AS_IF(
  [test "x$ac_cv_func_ctime_r" = xno],
  [AC_CHECK_FUNCS([ctime])

  AS_IF(
   [test "x$ac_cv_func_ctime" = xno],
   [AC_MSG_FAILURE(
    [Missing function: ctime_r and ctime],
    [1])
   ])
  ])
 ])

dnl Function to detect if libcdatetime dependencies are available
AC_DEFUN([AX_LIBCDATETIME_CHECK_LOCAL],
 [dnl Headers included in libcdatetime/libcdatetime_elements.c
 AC_CHECK_HEADERS([errno.h])

 AC_HEADER_TIME

 dnl Types used in libcdatetime/libcdatetime_elements.c
 AC_STRUCT_TM

 dnl Date and time functions used in libcdatetime/libcdatetime_elements.c
 AC_CHECK_FUNCS([gmtime gmtime_r localtime localtime_r mktime time])

 AS_IF(
  [test "x$ac_cv_func_gmtime" != xyes && test "x$ac_cv_func_gmtime_r" != xyes],
  [AC_MSG_FAILURE(
   [Missing functions: gmtime_r and gmtime],
   [1])
  ])
 
 AS_IF(
  [test "x$ac_cv_func_localtime" != xyes && test "x$ac_cv_func_localtime_r" != xyes],
  [AC_MSG_FAILURE(
   [Missing functions: localtime_r and localtime],
   [1])
  ])
 
 AS_IF(
  [test "x$ac_cv_func_mktime" != xyes],
  [AC_MSG_FAILURE(
   [Missing function: mktime],
   [1])
  ])
 
 AS_IF(
  [test "x$ac_cv_func_time" != xyes],
  [AC_MSG_FAILURE(
   [Missing function: time],
   [1])
  ])
 ])

