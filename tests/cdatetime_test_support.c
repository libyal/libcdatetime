/*
 * Library support functions test program
 *
 * Copyright (C) 2013-2025, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <file_stream.h>
#include <narrow_string.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "cdatetime_test_libcdatetime.h"
#include "cdatetime_test_libcerror.h"
#include "cdatetime_test_macros.h"
#include "cdatetime_test_unused.h"

#include "../libcdatetime/libcdatetime_support.h"

/* Tests the libcdatetime_get_version function
 * Returns 1 if successful or 0 if not
 */
int cdatetime_test_get_version(
     void )
{
	const char *version_string = NULL;
	int result                 = 0;

	version_string = libcdatetime_get_version();

	result = narrow_string_compare(
	          version_string,
	          LIBCDATETIME_VERSION_STRING,
	          9 );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	return( 1 );

on_error:
	return( 0 );
}

#if defined( __GNUC__ ) && !defined( LIBCDATETIME_DLL_IMPORT )

/* Tests the libcdatetime_is_leap_year function
 * Returns 1 if successful or 0 if not
 */
int cdatetime_test_is_leap_year(
     void )
{
	int result = 0;

	/* Test regular cases
	 */
	result = libcdatetime_is_leap_year(
	          1900 );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	result = libcdatetime_is_leap_year(
	          2000 );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	result = libcdatetime_is_leap_year(
	          2016 );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	result = libcdatetime_is_leap_year(
	          2017 );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	return( 1 );

on_error:
	return( 0 );
}

/* Tests the libcdatetime_get_days_in_month function
 * Returns 1 if successful or 0 if not
 */
int cdatetime_test_get_days_in_month(
     void )
{
	libcerror_error_t *error = NULL;
	uint8_t days_in_month    = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libcdatetime_get_days_in_month(
	          &days_in_month,
	          2000,
	          1,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	CDATETIME_TEST_ASSERT_EQUAL_UINT16(
	 "days_in_month",
	 days_in_month,
	 31 );

	result = libcdatetime_get_days_in_month(
	          &days_in_month,
	          2000,
	          2,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	CDATETIME_TEST_ASSERT_EQUAL_UINT16(
	 "days_in_month",
	 days_in_month,
	 29 );

	result = libcdatetime_get_days_in_month(
	          &days_in_month,
	          1999,
	          2,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	CDATETIME_TEST_ASSERT_EQUAL_UINT16(
	 "days_in_month",
	 days_in_month,
	 28 );

	result = libcdatetime_get_days_in_month(
	          &days_in_month,
	          2000,
	          4,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	CDATETIME_TEST_ASSERT_EQUAL_UINT16(
	 "days_in_month",
	 days_in_month,
	 30 );

	/* Test error cases
	 */
	result = libcdatetime_get_days_in_month(
	          NULL,
	          2000,
	          1,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libcdatetime_get_days_in_month(
	          &days_in_month,
	          2000,
	          0,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libcdatetime_get_days_in_month(
	          &days_in_month,
	          2000,
	          13,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	return( 0 );
}

/* Tests the libcdatetime_get_day_of_year function
 * Returns 1 if successful or 0 if not
 */
int cdatetime_test_get_day_of_year(
     void )
{
	libcerror_error_t *error = NULL;
	uint16_t day_of_year     = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libcdatetime_get_day_of_year(
	          &day_of_year,
	          2000,
	          12,
	          31,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	CDATETIME_TEST_ASSERT_EQUAL_UINT16(
	 "day_of_year",
	 day_of_year,
	 ( 31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30 + 31 ) - 1 );

	result = libcdatetime_get_day_of_year(
	          &day_of_year,
	          1999,
	          12,
	          31,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	CDATETIME_TEST_ASSERT_EQUAL_UINT16(
	 "day_of_year",
	 day_of_year,
	 ( 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30 + 31 ) - 1 );

	/* Test error cases
	 */
	result = libcdatetime_get_day_of_year(
	          NULL,
	          2000,
	          12,
	          31,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libcdatetime_get_day_of_year(
	          &day_of_year,
	          2000,
	          13,
	          0,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libcdatetime_get_day_of_year(
	          &day_of_year,
	          2000,
	          1,
	          0,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libcdatetime_get_day_of_year(
	          &day_of_year,
	          2000,
	          1,
	          32,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBCDATETIME_DLL_IMPORT ) */

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc CDATETIME_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] CDATETIME_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc CDATETIME_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] CDATETIME_TEST_ATTRIBUTE_UNUSED )
#endif
{
	CDATETIME_TEST_UNREFERENCED_PARAMETER( argc )
	CDATETIME_TEST_UNREFERENCED_PARAMETER( argv )

	CDATETIME_TEST_RUN(
	 "libcdatetime_get_version",
	 cdatetime_test_get_version );

#if defined( __GNUC__ ) && !defined( LIBCDATETIME_DLL_IMPORT )

	CDATETIME_TEST_RUN(
	 "libcdatetime_is_leap_year",
	 cdatetime_test_is_leap_year );

	CDATETIME_TEST_RUN(
	 "libcdatetime_get_days_in_month",
	 cdatetime_test_get_days_in_month );

	CDATETIME_TEST_RUN(
	 "libcdatetime_get_day_of_year",
	 cdatetime_test_get_day_of_year );

#endif /* defined( __GNUC__ ) && !defined( LIBCDATETIME_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

