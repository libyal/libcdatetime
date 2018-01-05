/*
 * Library timestamp type test program
 *
 * Copyright (C) 2013-2018, Joachim Metz <joachim.metz@gmail.com>
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
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#if !defined( WINAPI )
#if defined( TIME_WITH_SYS_TIME )
#include <sys/time.h>
#include <time.h>
#elif defined( HAVE_SYS_TIME_H )
#include <sys/time.h>
#else
#include <time.h>
#endif
#endif

#if defined( HAVE_GNU_DL_DLSYM ) && defined( __GNUC__ ) && !defined( __CYGWIN__ )
#define __USE_GNU
#include <dlfcn.h>
#undef __USE_GNU
#endif

#include "cdatetime_test_libcdatetime.h"
#include "cdatetime_test_libcerror.h"
#include "cdatetime_test_macros.h"
#include "cdatetime_test_memory.h"
#include "cdatetime_test_unused.h"

#if defined( HAVE_GNU_DL_DLSYM ) && defined( __GNUC__ ) && !defined( __CYGWIN__ )

static time_t (*cdatetime_test_real_time)(time_t *) = NULL;

int cdatetime_test_time_attempts_before_fail        = -1;

/* Custom time for testing memory error cases
 * Returns a pointer to newly allocated data or NULL
 */
time_t time(
     time_t *tloc )
{
	int print_count = 0;

	if( cdatetime_test_real_time == NULL )
	{
		cdatetime_test_real_time = dlsym(
		                            RTLD_NEXT,
		                            "time" );
	}
	if( cdatetime_test_time_attempts_before_fail == 0 )
	{
		cdatetime_test_time_attempts_before_fail = -1;

		return( -1 );
	}
	else if( cdatetime_test_time_attempts_before_fail > 0 )
	{
		cdatetime_test_time_attempts_before_fail--;
	}
	print_count = cdatetime_test_real_time(
	               tloc );

	return( print_count );
}

#endif /* defined( HAVE_GNU_DL_DLSYM ) && defined( __GNUC__ ) && !defined( __CYGWIN__ ) */

/* Tests the libcdatetime_timestamp_initialize function
 * Returns 1 if successful or 0 if not
 */
int cdatetime_test_timestamp_initialize(
     void )
{
	libcdatetime_timestamp_t *timestamp = NULL;
	libcerror_error_t *error            = NULL;
	int result                          = 0;

#if defined( HAVE_CDATETIME_TEST_MEMORY )
	int number_of_malloc_fail_tests     = 1;
	int number_of_memset_fail_tests     = 1;
	int test_number                     = 0;
#endif

	/* Test regular cases
	 */
	result = libcdatetime_timestamp_initialize(
	          &timestamp,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
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

	CDATETIME_TEST_ASSERT_EQUAL_INT(
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

	CDATETIME_TEST_ASSERT_EQUAL_INT(
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

	CDATETIME_TEST_ASSERT_EQUAL_INT(
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

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libcdatetime_timestamp_initialize with malloc failing
		 */
		cdatetime_test_malloc_attempts_before_fail = test_number;

		result = libcdatetime_timestamp_initialize(
		          &timestamp,
		          &error );

		if( cdatetime_test_malloc_attempts_before_fail != -1 )
		{
			cdatetime_test_malloc_attempts_before_fail = -1;

			if( timestamp != NULL )
			{
				libcdatetime_timestamp_free(
				 &timestamp,
				 NULL );
			}
		}
		else
		{
			CDATETIME_TEST_ASSERT_EQUAL_INT(
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
	}
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test libcdatetime_timestamp_initialize with memset failing
		 */
		cdatetime_test_memset_attempts_before_fail = test_number;

		result = libcdatetime_timestamp_initialize(
		          &timestamp,
		          &error );

		if( cdatetime_test_memset_attempts_before_fail != -1 )
		{
			cdatetime_test_memset_attempts_before_fail = -1;

			if( timestamp != NULL )
			{
				libcdatetime_timestamp_free(
				 &timestamp,
				 NULL );
			}
		}
		else
		{
			CDATETIME_TEST_ASSERT_EQUAL_INT(
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

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "timestamp",
	 timestamp );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcdatetime_timestamp_initialize(
	          &destination_timestamp,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "destination_timestamp",
	 destination_timestamp );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libcdatetime_timestamp_copy(
	          destination_timestamp,
	          timestamp,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
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

	CDATETIME_TEST_ASSERT_EQUAL_INT(
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

	CDATETIME_TEST_ASSERT_EQUAL_INT(
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
		CDATETIME_TEST_ASSERT_EQUAL_INT(
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

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "destination_timestamp",
	 destination_timestamp );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcdatetime_timestamp_free(
	          &timestamp,
	          NULL );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "timestamp",
	 timestamp );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

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

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "timestamp",
	 timestamp );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libcdatetime_timestamp_set_current_time(
	          timestamp,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
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

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( WINAPI ) && ( WINVER >= 0x0500 )

#if defined( HAVE_CDATETIME_TEST_MEMORY )

	/* Test libcdatetime_timestamp_set_current_time with memset failing
	 */
	cdatetime_test_memset_attempts_before_fail = 0;

	result = libcdatetime_timestamp_set_current_time(
	          timestamp,
	          &error );

	if( cdatetime_test_memset_attempts_before_fail != -1 )
	{
		cdatetime_test_memset_attempts_before_fail = -1;
	}
	else
	{
		CDATETIME_TEST_ASSERT_EQUAL_INT(
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

	/* TODO: Test libcdatetime_timestamp_set_current_time with SystemTimeToFileTime failing
	 */

#else

#if defined( HAVE_GNU_DL_DLSYM ) && defined( __GNUC__ ) && !defined( __CYGWIN__ )
	/* Test libcdatetime_timestamp_set_current_time with time failing
	 */
	cdatetime_test_time_attempts_before_fail = 0;

	result = libcdatetime_timestamp_set_current_time(
	          timestamp,
	          &error );

	if( cdatetime_test_time_attempts_before_fail != -1 )
	{
		cdatetime_test_time_attempts_before_fail = -1;
	}
	else
	{
		CDATETIME_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		CDATETIME_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );

	}
#endif /* defined( HAVE_GNU_DL_DLSYM ) && defined( __GNUC__ ) && !defined( __CYGWIN__ ) */

#endif /* defined( WINAPI ) && ( WINVER >= 0x0500 ) */

	/* Clean up
	 */
	result = libcdatetime_timestamp_free(
	          &timestamp,
	          NULL );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "timestamp",
	 timestamp );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

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

/* Tests the libcdatetime_timestamp_get_delta_in_seconds function
 * Returns 1 if successful or 0 if not
 */
int cdatetime_test_timestamp_get_delta_in_seconds(
     void )
{
	libcdatetime_timestamp_t *first_timestamp  = NULL;
	libcdatetime_timestamp_t *second_timestamp = NULL;
	libcerror_error_t *error                   = NULL;
	int64_t number_of_seconds                  = 0;
	int result                                 = 0;

	/* Initialize test
	 */
	result = libcdatetime_timestamp_initialize(
	          &first_timestamp,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "first_timestamp",
	 first_timestamp );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcdatetime_timestamp_initialize(
	          &second_timestamp,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "second_timestamp",
	 second_timestamp );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcdatetime_timestamp_set_current_time(
	          second_timestamp,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libcdatetime_timestamp_get_delta_in_seconds(
	          first_timestamp,
	          second_timestamp,
	          &number_of_seconds,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcdatetime_timestamp_get_delta_in_seconds(
	          second_timestamp,
	          first_timestamp,
	          &number_of_seconds,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libcdatetime_timestamp_get_delta_in_seconds(
	          NULL,
	          second_timestamp,
	          &number_of_seconds,
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

	result = libcdatetime_timestamp_get_delta_in_seconds(
	          first_timestamp,
	          NULL,
	          &number_of_seconds,
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

	result = libcdatetime_timestamp_get_delta_in_seconds(
	          first_timestamp,
	          second_timestamp,
	          NULL,
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

	/* Clean up
	 */
	result = libcdatetime_timestamp_free(
	          &second_timestamp,
	          NULL );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "second_timestamp",
	 second_timestamp );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcdatetime_timestamp_free(
	          &first_timestamp,
	          NULL );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "first_timestamp",
	 first_timestamp );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( second_timestamp != NULL )
	{
		libcdatetime_timestamp_free(
		 &second_timestamp,
		 NULL );
	}
	if( first_timestamp != NULL )
	{
		libcdatetime_timestamp_free(
		 &first_timestamp,
		 NULL );
	}
	return( 0 );
}

/* Tests the libcdatetime_timestamp_get_string_size function
 * Returns 1 if successful or 0 if not
 */
int cdatetime_test_timestamp_get_string_size(
     void )
{
	libcdatetime_timestamp_t *timestamp = NULL;
	libcerror_error_t *error            = NULL;
	size_t string_size                  = 0;
	int result                          = 0;

	/* Initialize test
	 */
	result = libcdatetime_timestamp_initialize(
	          &timestamp,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "timestamp",
	 timestamp );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libcdatetime_timestamp_get_string_size(
	          timestamp,
	          &string_size,
	          LIBCDATETIME_STRING_FORMAT_TYPE_CTIME | LIBCDATETIME_STRING_FORMAT_FLAG_DATE_TIME | LIBCDATETIME_STRING_FORMAT_FLAG_TIMEZONE_INDICATOR,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcdatetime_timestamp_get_string_size(
	          timestamp,
	          &string_size,
	          LIBCDATETIME_STRING_FORMAT_TYPE_ISO8601 | LIBCDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS | LIBCDATETIME_STRING_FORMAT_FLAG_TIMEZONE_INDICATOR,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libcdatetime_timestamp_get_string_size(
	          NULL,
	          &string_size,
	          LIBCDATETIME_STRING_FORMAT_TYPE_CTIME | LIBCDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
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

	result = libcdatetime_timestamp_get_string_size(
	          timestamp,
	          NULL,
	          LIBCDATETIME_STRING_FORMAT_TYPE_CTIME | LIBCDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
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

	result = libcdatetime_timestamp_get_string_size(
	          timestamp,
	          &string_size,
	          LIBCDATETIME_STRING_FORMAT_TYPE_CTIME | 0xffffff00UL,
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

	result = libcdatetime_timestamp_get_string_size(
	          timestamp,
	          &string_size,
	          0x000000ffUL | LIBCDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
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

	/* Clean up
	 */
	result = libcdatetime_timestamp_free(
	          &timestamp,
	          NULL );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "timestamp",
	 timestamp );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

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

/* Tests the libcdatetime_timestamp_copy_to_string function
 * Returns 1 if successful or 0 if not
 */
int cdatetime_test_timestamp_copy_to_string(
     void )
{
	uint8_t string[ 64 ];

	libcdatetime_timestamp_t *timestamp = NULL;
	libcerror_error_t *error            = NULL;
	int result                          = 0;

	/* Initialize test
	 */
	result = libcdatetime_timestamp_initialize(
	          &timestamp,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "timestamp",
	 timestamp );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libcdatetime_timestamp_copy_to_string(
	          timestamp,
	          string,
	          64,
	          LIBCDATETIME_STRING_FORMAT_TYPE_CTIME | LIBCDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libcdatetime_timestamp_copy_to_string(
	          NULL,
	          string,
	          64,
	          LIBCDATETIME_STRING_FORMAT_TYPE_CTIME | LIBCDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
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

	/* Clean up
	 */
	result = libcdatetime_timestamp_free(
	          &timestamp,
	          NULL );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "timestamp",
	 timestamp );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

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

/* Tests the libcdatetime_timestamp_copy_to_string_with_index function
 * Returns 1 if successful or 0 if not
 */
int cdatetime_test_timestamp_copy_to_string_with_index(
     void )
{
	uint8_t string[ 64 ];

	libcdatetime_timestamp_t *timestamp = NULL;
	libcerror_error_t *error            = NULL;
	size_t string_index                 = 0;
	int result                          = 0;

	/* Initialize test
	 */
	result = libcdatetime_timestamp_initialize(
	          &timestamp,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "timestamp",
	 timestamp );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libcdatetime_timestamp_copy_to_string_with_index(
	          timestamp,
	          string,
	          64,
	          &string_index,
	          LIBCDATETIME_STRING_FORMAT_TYPE_CTIME | LIBCDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libcdatetime_timestamp_copy_to_string_with_index(
	          NULL,
	          string,
	          64,
	          &string_index,
	          LIBCDATETIME_STRING_FORMAT_TYPE_CTIME | LIBCDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	/* TODO: Test libcdatetime_timestamp_copy_to_string_with_index with libcdatetime_internal_elements_set_from_filetime_utc failing
	 */

#if defined( HAVE_CDATETIME_TEST_MEMORY )

	/* Test libcdatetime_timestamp_copy_to_string_with_index with malloc failing in libcdatetime_elements_initialize
	 */
	cdatetime_test_malloc_attempts_before_fail = 0;

	result = libcdatetime_timestamp_copy_to_string_with_index(
	          timestamp,
	          string,
	          64,
	          &string_index,
	          LIBCDATETIME_STRING_FORMAT_TYPE_CTIME | LIBCDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
	          &error );

	if( cdatetime_test_malloc_attempts_before_fail != -1 )
	{
		cdatetime_test_malloc_attempts_before_fail = -1;
	}
	else
	{
		CDATETIME_TEST_ASSERT_EQUAL_INT(
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

	/* Test libcdatetime_timestamp_copy_to_string_with_index with libcdatetime_elements_copy_to_string_with_index failing
	 */
	result = libcdatetime_timestamp_copy_to_string_with_index(
	          timestamp,
	          NULL,
	          64,
	          &string_index,
	          LIBCDATETIME_STRING_FORMAT_TYPE_CTIME | LIBCDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
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

	/* TODO: Test libcdatetime_timestamp_copy_to_string_with_index with free failing in libcdatetime_elements_free
	 */

	/* Clean up
	 */
	result = libcdatetime_timestamp_free(
	          &timestamp,
	          NULL );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "timestamp",
	 timestamp );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

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
	 "libcdatetime_timestamp_initialize",
	 cdatetime_test_timestamp_initialize );

	CDATETIME_TEST_RUN(
	 "libcdatetime_timestamp_free",
	 cdatetime_test_timestamp_free );

	CDATETIME_TEST_RUN(
	 "libcdatetime_timestamp_copy",
	 cdatetime_test_timestamp_copy );

	CDATETIME_TEST_RUN(
	 "libcdatetime_timestamp_set_current_time",
	 cdatetime_test_timestamp_set_current_time );

	CDATETIME_TEST_RUN(
	 "libcdatetime_timestamp_get_delta_in_seconds",
	 cdatetime_test_timestamp_get_delta_in_seconds );

	CDATETIME_TEST_RUN(
	 "libcdatetime_timestamp_get_string_size",
	 cdatetime_test_timestamp_get_string_size );

	CDATETIME_TEST_RUN(
	 "libcdatetime_timestamp_copy_to_string",
	 cdatetime_test_timestamp_copy_to_string );

	CDATETIME_TEST_RUN(
	 "libcdatetime_timestamp_copy_to_string_with_index",
	 cdatetime_test_timestamp_copy_to_string_with_index );

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

