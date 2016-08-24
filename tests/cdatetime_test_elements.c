/*
 * Library elements type testing program
 *
 * Copyright (C) 2013-2016, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "cdatetime_test_libcdatetime.h"
#include "cdatetime_test_libcerror.h"
#include "cdatetime_test_libcstring.h"
#include "cdatetime_test_macros.h"
#include "cdatetime_test_memory.h"
#include "cdatetime_test_unused.h"

/* Tests the libcdatetime_elements_initialize function
 * Returns 1 if successful or 0 if not
 */
int cdatetime_test_elements_initialize(
     void )
{
	libcdatetime_elements_t *elements = NULL;
	libcerror_error_t *error          = NULL;
	int result                        = 0;

	/* Test libcdatetime_elements_initialize
	 */
	result = libcdatetime_elements_initialize(
	          &elements,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL(
	 "result",
	 result,
	 1 );

        CDATETIME_TEST_ASSERT_IS_NOT_NULL(
         "elements",
         elements );

        CDATETIME_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libcdatetime_elements_free(
	          &elements,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL(
	 "result",
	 result,
	 1 );

        CDATETIME_TEST_ASSERT_IS_NULL(
         "elements",
         elements );

        CDATETIME_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libcdatetime_elements_initialize(
	          NULL,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL(
	 "result",
	 result,
	 -1 );

        CDATETIME_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	elements = (libcdatetime_elements_t *) 0x12345678UL;

	result = libcdatetime_elements_initialize(
	          &elements,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL(
	 "result",
	 result,
	 -1 );

        CDATETIME_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	elements = NULL;

#if defined( HAVE_CDATETIME_TEST_MEMORY )

	/* Test libcdatetime_elements_initialize with malloc failing
	 */
	cdatetime_test_malloc_attempts_before_fail = 0;

	result = libcdatetime_elements_initialize(
	          &elements,
	          &error );

	if( cdatetime_test_malloc_attempts_before_fail != -1 )
	{
		cdatetime_test_malloc_attempts_before_fail = -1;
	}
	else
	{
		CDATETIME_TEST_ASSERT_EQUAL(
		 "result",
		 result,
		 -1 );

		CDATETIME_TEST_ASSERT_IS_NULL(
		 "elements",
		 elements );

		CDATETIME_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libcdatetime_elements_initialize with memset failing
	 */
	cdatetime_test_memset_attempts_before_fail = 0;

	result = libcdatetime_elements_initialize(
	          &elements,
	          &error );

	if( cdatetime_test_memset_attempts_before_fail != -1 )
	{
		cdatetime_test_memset_attempts_before_fail = -1;
	}
	else
	{
		CDATETIME_TEST_ASSERT_EQUAL(
		 "result",
		 result,
		 -1 );

		CDATETIME_TEST_ASSERT_IS_NULL(
		 "elements",
		 elements );

		CDATETIME_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_CDATETIME_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( elements != NULL )
	{
		libcdatetime_elements_free(
		 &elements,
		 NULL );
	}
	return( 0 );
}

/* Tests the libcdatetime_elements_free function
 * Returns 1 if successful or 0 if not
 */
int cdatetime_test_elements_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libcdatetime_elements_free(
	          NULL,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL(
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
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* The main program
 */
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
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
	 "libcdatetime_elements_initialize",
	 cdatetime_test_elements_initialize() )

	CDATETIME_TEST_RUN(
	 "libcdatetime_elements_free",
	 cdatetime_test_elements_free() )

/* TODO test get functions
 * libcdatetime_elements_get_year
 * libcdatetime_elements_get_day_of_year
 * libcdatetime_elements_get_month
 * libcdatetime_elements_get_day_of_month
 * libcdatetime_elements_get_date_values
 * libcdatetime_elements_get_hours
 * libcdatetime_elements_get_minutes
 * libcdatetime_elements_get_seconds
 * libcdatetime_elements_get_milli_seconds
 * libcdatetime_elements_get_micro_seconds
 * libcdatetime_elements_get_nano_seconds
 * libcdatetime_elements_get_time_values
 */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

