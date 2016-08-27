/*
 * Library timestamp type testing program
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

/* Tests the libcdatetime_timestamp_initialize function
 * Returns 1 if successful or 0 if not
 */
int cdatetime_test_timestamp_initialize(
     void )
{
	libcdatetime_timestamp_t *timestamp = NULL;
	libcerror_error_t *error            = NULL;
	int result                          = 0;

	/* Test libcdatetime_timestamp_initialize
	 */
	result = libcdatetime_timestamp_initialize(
	          &timestamp,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL(
	 "result",
	 result,
	 1 );

        CDATETIME_TEST_ASSERT_IS_NOT_NULL(
         "timestamp",
         timestamp );

        CDATETIME_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libcdatetime_timestamp_free(
	          &timestamp,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL(
	 "result",
	 result,
	 1 );

        CDATETIME_TEST_ASSERT_IS_NULL(
         "timestamp",
         timestamp );

        CDATETIME_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libcdatetime_timestamp_initialize(
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

	timestamp = (libcdatetime_timestamp_t *) 0x12345678UL;

	result = libcdatetime_timestamp_initialize(
	          &timestamp,
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

	timestamp = NULL;

#if defined( HAVE_CDATETIME_TEST_MEMORY )

	/* Test libcdatetime_timestamp_initialize with malloc failing
	 */
	cdatetime_test_malloc_attempts_before_fail = 0;

	result = libcdatetime_timestamp_initialize(
	          &timestamp,
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
		 "timestamp",
		 timestamp );

		CDATETIME_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libcdatetime_timestamp_initialize with memset failing
	 */
	cdatetime_test_memset_attempts_before_fail = 0;

	result = libcdatetime_timestamp_initialize(
	          &timestamp,
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
		 "timestamp",
		 timestamp );

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
	if( timestamp != NULL )
	{
		libcdatetime_timestamp_free(
		 &timestamp,
		 NULL );
	}
	return( 0 );
}

/* Tests the libcdatetime_timestamp_free function
 * Returns 1 if successful or 0 if not
 */
int cdatetime_test_timestamp_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libcdatetime_timestamp_free(
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

/* Tests the libcdatetime_timestamp_copy function
 * Returns 1 if successful or 0 if not
 */
int cdatetime_test_timestamp_copy(
     void )
{
	libcdatetime_timestamp_t *destination_timestamp = NULL;
	libcdatetime_timestamp_t *timestamp             = NULL;
	libcerror_error_t *error                        = NULL;
	int result                                      = 0;

	/* Initialize test
	 */
	result = libcdatetime_timestamp_initialize(
	          &timestamp,
	          &error );

	result = libcdatetime_timestamp_initialize(
	          &destination_timestamp,
	          &error );

	/* Test timestamp entry copy
	 */
	result = libcdatetime_timestamp_copy(
	          destination_timestamp,
	          timestamp,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL(
	 "result",
	 result,
	 1 );

        CDATETIME_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libcdatetime_timestamp_copy(
	          NULL,
	          timestamp,
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

	result = libcdatetime_timestamp_copy(
	          destination_timestamp,
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

#if defined( HAVE_CDATETIME_TEST_MEMORY )

	/* Test libcdatetime_timestamp_initialize with memcpy failing
	 */
	cdatetime_test_memcpy_attempts_before_fail = 0;

	result = libcdatetime_timestamp_copy(
	          destination_timestamp,
	          timestamp,
	          &error );

	if( cdatetime_test_memcpy_attempts_before_fail != -1 )
	{
		cdatetime_test_memcpy_attempts_before_fail = -1;
	}
	else
	{
		CDATETIME_TEST_ASSERT_EQUAL(
		 "result",
		 result,
		 -1 );

		CDATETIME_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_CDATETIME_TEST_MEMORY ) */

	/* Clean up
	 */
	result = libcdatetime_timestamp_free(
	          &destination_timestamp,
	          NULL );

	result = libcdatetime_timestamp_free(
	          &timestamp,
	          NULL );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( destination_timestamp != NULL )
	{
		libcdatetime_timestamp_free(
		 &destination_timestamp,
		 NULL );
	}
	if( timestamp != NULL )
	{
		libcdatetime_timestamp_free(
		 &timestamp,
		 NULL );
	}
	return( 0 );
}

/* Tests the libcdatetime_timestamp_set_current_time function
 * Returns 1 if successful or 0 if not
 */
int cdatetime_test_timestamp_set_current_time(
     void )
{
	libcdatetime_timestamp_t *timestamp = NULL;
	libcerror_error_t *error            = NULL;
	int result                          = 0;

	/* Initialize test
	 */
	result = libcdatetime_timestamp_initialize(
	          &timestamp,
	          &error );

	/* Test set current time
	 */
	result = libcdatetime_timestamp_set_current_time(
	          timestamp,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL(
	 "result",
	 result,
	 1 );

        CDATETIME_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libcdatetime_timestamp_set_current_time(
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

	/* Clean up
	 */
	result = libcdatetime_timestamp_free(
	          &timestamp,
	          NULL );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( timestamp != NULL )
	{
		libcdatetime_timestamp_free(
		 &timestamp,
		 NULL );
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
	 "libcdatetime_timestamp_initialize",
	 cdatetime_test_timestamp_initialize() )

	CDATETIME_TEST_RUN(
	 "libcdatetime_timestamp_free",
	 cdatetime_test_timestamp_free() )

	CDATETIME_TEST_RUN(
	 "libcdatetime_timestamp_copy",
	 cdatetime_test_timestamp_copy() )

	CDATETIME_TEST_RUN(
	 "libcdatetime_timestamp_set_current_time",
	 cdatetime_test_timestamp_set_current_time() )

	/* TODO: add test for libcdatetime_timestamp_get_delta_in_seconds */
	/* TODO: add test for libcdatetime_timestamp_get_string_size */
	/* TODO: add test for libcdatetime_timestamp_copy_to_string */
	/* TODO: add test for libcdatetime_timestamp_copy_to_string_with_index */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

