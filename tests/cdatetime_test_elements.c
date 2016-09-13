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

/* Tests the libcdatetime_elements_copy function
 * Returns 1 if successful or 0 if not
 */
int cdatetime_test_elements_copy(
     void )
{
	libcdatetime_elements_t *destination_elements = NULL;
	libcdatetime_elements_t *elements             = NULL;
	libcerror_error_t *error                      = NULL;
	int result                                    = 0;

	/* Initialize test
	 */
	result = libcdatetime_elements_initialize(
	          &elements,
	          &error );

	result = libcdatetime_elements_initialize(
	          &destination_elements,
	          &error );

	/* Test elements entry copy
	 */
	result = libcdatetime_elements_copy(
	          destination_elements,
	          elements,
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
	result = libcdatetime_elements_copy(
	          NULL,
	          elements,
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

	result = libcdatetime_elements_copy(
	          destination_elements,
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

	/* Test libcdatetime_elements_initialize with memcpy failing
	 */
	cdatetime_test_memcpy_attempts_before_fail = 0;

	result = libcdatetime_elements_copy(
	          destination_elements,
	          elements,
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
	result = libcdatetime_elements_free(
	          &destination_elements,
	          NULL );

	result = libcdatetime_elements_free(
	          &elements,
	          NULL );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( destination_elements != NULL )
	{
		libcdatetime_elements_free(
		 &destination_elements,
		 NULL );
	}
	if( elements != NULL )
	{
		libcdatetime_elements_free(
		 &elements,
		 NULL );
	}
	return( 0 );
}

/* Tests the libcdatetime_elements_get_year function
 * Returns 1 if successful or 0 if not
 */
int cdatetime_test_elements_get_year(
     void )
{
	libcdatetime_elements_t *elements = NULL;
	libcerror_error_t *error          = NULL;
	int result                        = 0;
	uint16_t year                     = 0;

	/* Initialize test
	 */
	result = libcdatetime_elements_initialize(
	          &elements,
	          &error );

	result = libcdatetime_elements_set_current_time_utc(
	          elements,
	          &error );

	/* Test get year
	 */
	result = libcdatetime_elements_get_year(
	          elements,
	          &year,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL(
	 "result",
	 result,
	 1 );

#ifdef TODO
	CDATETIME_TEST_ASSERT_EQUAL(
	 "year",
	 year,
	 1900 );
#endif

        CDATETIME_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libcdatetime_elements_get_year(
	          NULL,
	          &year,
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

	result = libcdatetime_elements_get_year(
	          elements,
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
	result = libcdatetime_elements_free(
	          &elements,
	          NULL );

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

/* Tests the libcdatetime_elements_get_day_of_year function
 * Returns 1 if successful or 0 if not
 */
int cdatetime_test_elements_get_day_of_year(
     void )
{
	libcdatetime_elements_t *elements = NULL;
	libcerror_error_t *error          = NULL;
	int result                        = 0;
	uint16_t day_of_year              = 0;

	/* Initialize test
	 */
	result = libcdatetime_elements_initialize(
	          &elements,
	          &error );

	result = libcdatetime_elements_set_current_time_utc(
	          elements,
	          &error );

	/* Test get day of year
	 */
	result = libcdatetime_elements_get_day_of_year(
	          elements,
	          &day_of_year,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL(
	 "result",
	 result,
	 1 );

#ifdef TODO
	CDATETIME_TEST_ASSERT_EQUAL(
	 "day_of_year",
	 day_of_year,
	 0 );
#endif

        CDATETIME_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libcdatetime_elements_get_day_of_year(
	          NULL,
	          &day_of_year,
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

	result = libcdatetime_elements_get_day_of_year(
	          elements,
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
	result = libcdatetime_elements_free(
	          &elements,
	          NULL );

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

/* Tests the libcdatetime_elements_get_month function
 * Returns 1 if successful or 0 if not
 */
int cdatetime_test_elements_get_month(
     void )
{
	libcdatetime_elements_t *elements = NULL;
	libcerror_error_t *error          = NULL;
	int result                        = 0;
	uint8_t month                     = 0;

	/* Initialize test
	 */
	result = libcdatetime_elements_initialize(
	          &elements,
	          &error );

	result = libcdatetime_elements_set_current_time_utc(
	          elements,
	          &error );

	/* Test get month
	 */
	result = libcdatetime_elements_get_month(
	          elements,
	          &month,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL(
	 "result",
	 result,
	 1 );

#ifdef TODO
	CDATETIME_TEST_ASSERT_EQUAL(
	 "month",
	 month,
	 1 );
#endif

        CDATETIME_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libcdatetime_elements_get_month(
	          NULL,
	          &month,
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

	result = libcdatetime_elements_get_month(
	          elements,
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
	result = libcdatetime_elements_free(
	          &elements,
	          NULL );

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

/* Tests the libcdatetime_elements_get_day_of_month function
 * Returns 1 if successful or 0 if not
 */
int cdatetime_test_elements_get_day_of_month(
     void )
{
	libcdatetime_elements_t *elements = NULL;
	libcerror_error_t *error          = NULL;
	int result                        = 0;
	uint8_t day_of_month              = 0;

	/* Initialize test
	 */
	result = libcdatetime_elements_initialize(
	          &elements,
	          &error );

	result = libcdatetime_elements_set_current_time_utc(
	          elements,
	          &error );

	/* Test get day of month
	 */
	result = libcdatetime_elements_get_day_of_month(
	          elements,
	          &day_of_month,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL(
	 "result",
	 result,
	 1 );

#ifdef TODO
	CDATETIME_TEST_ASSERT_EQUAL(
	 "day_of_month",
	 day_of_month,
	 0 );
#endif

        CDATETIME_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libcdatetime_elements_get_day_of_month(
	          NULL,
	          &day_of_month,
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

	result = libcdatetime_elements_get_day_of_month(
	          elements,
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
	result = libcdatetime_elements_free(
	          &elements,
	          NULL );

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

/* Tests the libcdatetime_elements_get_date_values function
 * Returns 1 if successful or 0 if not
 */
int cdatetime_test_elements_get_date_values(
     void )
{
	libcdatetime_elements_t *elements = NULL;
	libcerror_error_t *error          = NULL;
	int result                        = 0;
	uint16_t year                     = 0;
	uint8_t day_of_month              = 0;
	uint8_t month                     = 0;

	/* Initialize test
	 */
	result = libcdatetime_elements_initialize(
	          &elements,
	          &error );

	result = libcdatetime_elements_set_current_time_utc(
	          elements,
	          &error );

	/* Test get date values
	 */
	result = libcdatetime_elements_get_date_values(
	          elements,
	          &year,
	          &month,
	          &day_of_month,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL(
	 "result",
	 result,
	 1 );

#ifdef TODO
	CDATETIME_TEST_ASSERT_EQUAL(
	 "year",
	 year,
	 1970 );

	CDATETIME_TEST_ASSERT_EQUAL(
	 "month",
	 month,
	 0 );

	CDATETIME_TEST_ASSERT_EQUAL(
	 "day_of_month",
	 day_of_month,
	 0 );
#endif

        CDATETIME_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libcdatetime_elements_get_date_values(
	          NULL,
	          &year,
	          &month,
	          &day_of_month,
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

	result = libcdatetime_elements_get_date_values(
	          elements,
	          NULL,
	          &month,
	          &day_of_month,
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

	result = libcdatetime_elements_get_date_values(
	          elements,
	          &year,
	          NULL,
	          &day_of_month,
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

	result = libcdatetime_elements_get_date_values(
	          elements,
	          &year,
	          &month,
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
	result = libcdatetime_elements_free(
	          &elements,
	          NULL );

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

/* Tests the libcdatetime_elements_get_hours function
 * Returns 1 if successful or 0 if not
 */
int cdatetime_test_elements_get_hours(
     void )
{
	libcdatetime_elements_t *elements = NULL;
	libcerror_error_t *error          = NULL;
	int result                        = 0;
	uint8_t hours                     = 0;

	/* Initialize test
	 */
	result = libcdatetime_elements_initialize(
	          &elements,
	          &error );

	result = libcdatetime_elements_set_current_time_utc(
	          elements,
	          &error );

	/* Test get hours
	 */
	result = libcdatetime_elements_get_hours(
	          elements,
	          &hours,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL(
	 "result",
	 result,
	 1 );

#ifdef TODO
	CDATETIME_TEST_ASSERT_EQUAL(
	 "hours",
	 hours,
	 1 );
#endif

        CDATETIME_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libcdatetime_elements_get_hours(
	          NULL,
	          &hours,
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

	result = libcdatetime_elements_get_hours(
	          elements,
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
	result = libcdatetime_elements_free(
	          &elements,
	          NULL );

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

/* Tests the libcdatetime_elements_get_minutes function
 * Returns 1 if successful or 0 if not
 */
int cdatetime_test_elements_get_minutes(
     void )
{
	libcdatetime_elements_t *elements = NULL;
	libcerror_error_t *error          = NULL;
	int result                        = 0;
	uint8_t minutes                   = 0;

	/* Initialize test
	 */
	result = libcdatetime_elements_initialize(
	          &elements,
	          &error );

	result = libcdatetime_elements_set_current_time_utc(
	          elements,
	          &error );

	/* Test get minutes
	 */
	result = libcdatetime_elements_get_minutes(
	          elements,
	          &minutes,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL(
	 "result",
	 result,
	 1 );

#ifdef TODO
	CDATETIME_TEST_ASSERT_EQUAL(
	 "minutes",
	 minutes,
	 1 );
#endif

        CDATETIME_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libcdatetime_elements_get_minutes(
	          NULL,
	          &minutes,
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

	result = libcdatetime_elements_get_minutes(
	          elements,
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
	result = libcdatetime_elements_free(
	          &elements,
	          NULL );

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

/* Tests the libcdatetime_elements_get_seconds function
 * Returns 1 if successful or 0 if not
 */
int cdatetime_test_elements_get_seconds(
     void )
{
	libcdatetime_elements_t *elements = NULL;
	libcerror_error_t *error          = NULL;
	int result                        = 0;
	uint8_t seconds                   = 0;

	/* Initialize test
	 */
	result = libcdatetime_elements_initialize(
	          &elements,
	          &error );

	result = libcdatetime_elements_set_current_time_utc(
	          elements,
	          &error );

	/* Test get seconds
	 */
	result = libcdatetime_elements_get_seconds(
	          elements,
	          &seconds,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL(
	 "result",
	 result,
	 1 );

#ifdef TODO
	CDATETIME_TEST_ASSERT_EQUAL(
	 "seconds",
	 seconds,
	 1 );
#endif

        CDATETIME_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libcdatetime_elements_get_seconds(
	          NULL,
	          &seconds,
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

	result = libcdatetime_elements_get_seconds(
	          elements,
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
	result = libcdatetime_elements_free(
	          &elements,
	          NULL );

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

/* Tests the libcdatetime_elements_get_milli_seconds function
 * Returns 1 if successful or 0 if not
 */
int cdatetime_test_elements_get_milli_seconds(
     void )
{
	libcdatetime_elements_t *elements = NULL;
	libcerror_error_t *error          = NULL;
	int result                        = 0;
	uint16_t milli_seconds            = 0;

	/* Initialize test
	 */
	result = libcdatetime_elements_initialize(
	          &elements,
	          &error );

	result = libcdatetime_elements_set_current_time_utc(
	          elements,
	          &error );

	/* Test get milli seconds
	 */
	result = libcdatetime_elements_get_milli_seconds(
	          elements,
	          &milli_seconds,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL(
	 "result",
	 result,
	 1 );

#ifdef TODO
	CDATETIME_TEST_ASSERT_EQUAL(
	 "milli_seconds",
	 milli_seconds,
	 0 );
#endif

        CDATETIME_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libcdatetime_elements_get_milli_seconds(
	          NULL,
	          &milli_seconds,
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

	result = libcdatetime_elements_get_milli_seconds(
	          elements,
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
	result = libcdatetime_elements_free(
	          &elements,
	          NULL );

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

/* Tests the libcdatetime_elements_get_micro_seconds function
 * Returns 1 if successful or 0 if not
 */
int cdatetime_test_elements_get_micro_seconds(
     void )
{
	libcdatetime_elements_t *elements = NULL;
	libcerror_error_t *error          = NULL;
	int result                        = 0;
	uint16_t micro_seconds            = 0;

	/* Initialize test
	 */
	result = libcdatetime_elements_initialize(
	          &elements,
	          &error );

	result = libcdatetime_elements_set_current_time_utc(
	          elements,
	          &error );

	/* Test get micro seconds
	 */
	result = libcdatetime_elements_get_micro_seconds(
	          elements,
	          &micro_seconds,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL(
	 "result",
	 result,
	 1 );

#ifdef TODO
	CDATETIME_TEST_ASSERT_EQUAL(
	 "micro_seconds",
	 micro_seconds,
	 0 );
#endif

        CDATETIME_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libcdatetime_elements_get_micro_seconds(
	          NULL,
	          &micro_seconds,
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

	result = libcdatetime_elements_get_micro_seconds(
	          elements,
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
	result = libcdatetime_elements_free(
	          &elements,
	          NULL );

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

/* Tests the libcdatetime_elements_get_nano_seconds function
 * Returns 1 if successful or 0 if not
 */
int cdatetime_test_elements_get_nano_seconds(
     void )
{
	libcdatetime_elements_t *elements = NULL;
	libcerror_error_t *error          = NULL;
	int result                        = 0;
	uint16_t nano_seconds             = 0;

	/* Initialize test
	 */
	result = libcdatetime_elements_initialize(
	          &elements,
	          &error );

	result = libcdatetime_elements_set_current_time_utc(
	          elements,
	          &error );

	/* Test get nano seconds
	 */
	result = libcdatetime_elements_get_nano_seconds(
	          elements,
	          &nano_seconds,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL(
	 "result",
	 result,
	 1 );

#ifdef TODO
	CDATETIME_TEST_ASSERT_EQUAL(
	 "nano_seconds",
	 nano_seconds,
	 0 );
#endif

        CDATETIME_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libcdatetime_elements_get_nano_seconds(
	          NULL,
	          &nano_seconds,
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

	result = libcdatetime_elements_get_nano_seconds(
	          elements,
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
	result = libcdatetime_elements_free(
	          &elements,
	          NULL );

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

/* Tests the libcdatetime_elements_get_time_values function
 * Returns 1 if successful or 0 if not
 */
int cdatetime_test_elements_get_time_values(
     void )
{
	libcdatetime_elements_t *elements = NULL;
	libcerror_error_t *error          = NULL;
	int result                        = 0;
	uint8_t hours                     = 0;
	uint8_t minutes                   = 0;
	uint8_t seconds                   = 0;

	/* Initialize test
	 */
	result = libcdatetime_elements_initialize(
	          &elements,
	          &error );

	result = libcdatetime_elements_set_current_time_utc(
	          elements,
	          &error );

	/* Test get time values
	 */
	result = libcdatetime_elements_get_time_values(
	          elements,
	          &hours,
	          &minutes,
	          &seconds,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL(
	 "result",
	 result,
	 1 );

#ifdef TODO
	CDATETIME_TEST_ASSERT_EQUAL(
	 "hours",
	 hours,
	 0 );

	CDATETIME_TEST_ASSERT_EQUAL(
	 "minutes",
	 minutes,
	 0 );

	CDATETIME_TEST_ASSERT_EQUAL(
	 "seconds",
	 seconds,
	 0 );
#endif

        CDATETIME_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libcdatetime_elements_get_time_values(
	          NULL,
	          &hours,
	          &minutes,
	          &seconds,
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

	result = libcdatetime_elements_get_time_values(
	          elements,
	          NULL,
	          &minutes,
	          &seconds,
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

	result = libcdatetime_elements_get_time_values(
	          elements,
	          &hours,
	          NULL,
	          &seconds,
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

	result = libcdatetime_elements_get_time_values(
	          elements,
	          &hours,
	          &minutes,
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
	result = libcdatetime_elements_free(
	          &elements,
	          NULL );

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

/* Tests the libcdatetime_elements_get_delta_in_seconds function
 * Returns 1 if successful or 0 if not
 */
int cdatetime_test_elements_get_delta_in_seconds(
     void )
{
	libcdatetime_elements_t *first_elements  = NULL;
	libcdatetime_elements_t *second_elements = NULL;
	libcerror_error_t *error                 = NULL;
	int64_t number_of_seconds                = 0;
	int result                               = 0;

/* TODO: improve test coverage */

	/* Test error cases
	 */
	result = libcdatetime_elements_get_delta_in_seconds(
	          NULL,
	          second_elements,
	          &number_of_seconds,
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

	result = libcdatetime_elements_get_delta_in_seconds(
	          first_elements,
	          NULL,
	          &number_of_seconds,
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

	result = libcdatetime_elements_get_delta_in_seconds(
	          first_elements,
	          second_elements,
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

/* Tests the libcdatetime_elements_set_current_time_utc function
 * Returns 1 if successful or 0 if not
 */
int cdatetime_test_elements_set_current_time_utc(
     void )
{
	libcdatetime_elements_t *elements = NULL;
	libcerror_error_t *error          = NULL;
	int result                        = 0;

	/* Initialize test
	 */
	result = libcdatetime_elements_initialize(
	          &elements,
	          &error );

	/* Test set current time in UTC
	 */
	result = libcdatetime_elements_set_current_time_utc(
	          elements,
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
	result = libcdatetime_elements_set_current_time_utc(
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
	result = libcdatetime_elements_free(
	          &elements,
	          NULL );

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

/* Tests the libcdatetime_elements_set_current_time_local function
 * Returns 1 if successful or 0 if not
 */
int cdatetime_test_elements_set_current_time_localtime(
     void )
{
	libcdatetime_elements_t *elements = NULL;
	libcerror_error_t *error          = NULL;
	int result                        = 0;

	/* Initialize test
	 */
	result = libcdatetime_elements_initialize(
	          &elements,
	          &error );

	/* Test set current time in localtime
	 */
	result = libcdatetime_elements_set_current_time_localtime(
	          elements,
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
	result = libcdatetime_elements_set_current_time_localtime(
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
	result = libcdatetime_elements_free(
	          &elements,
	          NULL );

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

/* Tests the libcdatetime_elements_get_string_size function
 * Returns 1 if successful or 0 if not
 */
int cdatetime_test_elements_get_string_size(
     void )
{
	libcdatetime_elements_t *elements = NULL;
	libcerror_error_t *error          = NULL;
	size_t string_size                = 0;
	int result                        = 0;

	/* Initialize test
	 */
	result = libcdatetime_elements_initialize(
	          &elements,
	          &error );

	result = libcdatetime_elements_set_current_time_utc(
	          elements,
	          &error );

	/* Test copy to string
	 */
	result = libcdatetime_elements_get_string_size(
	          elements,
	          &string_size,
	          LIBCDATETIME_STRING_FORMAT_TYPE_CTIME | LIBCDATETIME_STRING_FORMAT_FLAG_DATE_TIME | LIBCDATETIME_STRING_FORMAT_FLAG_TIMEZONE_INDICATOR,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL(
	 "result",
	 result,
	 1 );

/* TODO: compare result string size */

        CDATETIME_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libcdatetime_elements_get_string_size(
	          elements,
	          &string_size,
	          LIBCDATETIME_STRING_FORMAT_TYPE_ISO8601 | LIBCDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS | LIBCDATETIME_STRING_FORMAT_FLAG_TIMEZONE_INDICATOR,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL(
	 "result",
	 result,
	 1 );

/* TODO: compare result string size */

        CDATETIME_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libcdatetime_elements_get_string_size(
	          NULL,
	          &string_size,
	          LIBCDATETIME_STRING_FORMAT_TYPE_CTIME | LIBCDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
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

	result = libcdatetime_elements_get_string_size(
	          elements,
	          NULL,
	          LIBCDATETIME_STRING_FORMAT_TYPE_CTIME | LIBCDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
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

	result = libcdatetime_elements_get_string_size(
	          elements,
	          &string_size,
	          0,
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

	result = libcdatetime_elements_get_string_size(
	          elements,
	          &string_size,
	          LIBCDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
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
	result = libcdatetime_elements_free(
	          &elements,
	          NULL );

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

/* Tests the libcdatetime_elements_copy_to_string function
 * Returns 1 if successful or 0 if not
 */
int cdatetime_test_elements_copy_to_string(
     void )
{
	uint8_t string[ 128 ];

	libcdatetime_elements_t *elements = NULL;
	libcerror_error_t *error          = NULL;
	int result                        = 0;

	/* Initialize test
	 */
	result = libcdatetime_elements_initialize(
	          &elements,
	          &error );

	result = libcdatetime_elements_set_current_time_utc(
	          elements,
	          &error );

	/* Test copy to string
	 */
	result = libcdatetime_elements_copy_to_string(
	          elements,
	          string,
	          128,
	          LIBCDATETIME_STRING_FORMAT_TYPE_CTIME | LIBCDATETIME_STRING_FORMAT_FLAG_DATE_TIME | LIBCDATETIME_STRING_FORMAT_FLAG_TIMEZONE_INDICATOR,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL(
	 "result",
	 result,
	 1 );

/* TODO: compare result string */

        CDATETIME_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libcdatetime_elements_copy_to_string(
	          NULL,
	          string,
	          128,
	          LIBCDATETIME_STRING_FORMAT_TYPE_CTIME | LIBCDATETIME_STRING_FORMAT_FLAG_DATE_TIME | LIBCDATETIME_STRING_FORMAT_FLAG_TIMEZONE_INDICATOR,
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
	result = libcdatetime_elements_free(
	          &elements,
	          NULL );

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

/* Tests the libcdatetime_elements_copy_to_string_with_index function
 * Returns 1 if successful or 0 if not
 */
int cdatetime_test_elements_copy_to_string_with_index(
     void )
{
	uint8_t string[ 128 ];

	libcdatetime_elements_t *elements = NULL;
	libcerror_error_t *error          = NULL;
	size_t string_index               = 0;
	int result                        = 0;

	/* Initialize test
	 */
	result = libcdatetime_elements_initialize(
	          &elements,
	          &error );

	result = libcdatetime_elements_set_current_time_utc(
	          elements,
	          &error );

	/* Test copy to string
	 */
	string_index = 0;

	result = libcdatetime_elements_copy_to_string_with_index(
	          elements,
	          string,
	          128,
	          &string_index,
	          LIBCDATETIME_STRING_FORMAT_TYPE_CTIME | LIBCDATETIME_STRING_FORMAT_FLAG_DATE_TIME | LIBCDATETIME_STRING_FORMAT_FLAG_TIMEZONE_INDICATOR,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL(
	 "result",
	 result,
	 1 );

/* TODO: compare result string */

        CDATETIME_TEST_ASSERT_IS_NULL(
         "error",
         error );

	string_index = 0;

	result = libcdatetime_elements_copy_to_string_with_index(
	          elements,
	          string,
	          128,
	          &string_index,
	          LIBCDATETIME_STRING_FORMAT_TYPE_ISO8601 | LIBCDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS | LIBCDATETIME_STRING_FORMAT_FLAG_TIMEZONE_INDICATOR,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL(
	 "result",
	 result,
	 1 );

/* TODO: compare result string */

        CDATETIME_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test copy to string, which is too small for date
	 */
	string_index = 0;

	result = libcdatetime_elements_copy_to_string_with_index(
	          elements,
	          string,
	          11,
	          &string_index,
	          LIBCDATETIME_STRING_FORMAT_TYPE_CTIME | LIBCDATETIME_STRING_FORMAT_FLAG_DATE_TIME | LIBCDATETIME_STRING_FORMAT_FLAG_TIMEZONE_INDICATOR,
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

	/* Test copy to string, which is too small for date and time seperator
	 */
	string_index = 0;

	result = libcdatetime_elements_copy_to_string_with_index(
	          elements,
	          string,
	          12,
	          &string_index,
	          LIBCDATETIME_STRING_FORMAT_TYPE_CTIME | LIBCDATETIME_STRING_FORMAT_FLAG_DATE_TIME | LIBCDATETIME_STRING_FORMAT_FLAG_TIMEZONE_INDICATOR,
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

	/* Test copy to string, which is too small for time zone
	 */
	string_index = 0;

	result = libcdatetime_elements_copy_to_string_with_index(
	          elements,
	          string,
	          21,
	          &string_index,
	          LIBCDATETIME_STRING_FORMAT_TYPE_CTIME | LIBCDATETIME_STRING_FORMAT_FLAG_DATE_TIME | LIBCDATETIME_STRING_FORMAT_FLAG_TIMEZONE_INDICATOR,
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

	/* Test copy to string, which is too small for date
	 */
	string_index = 0;

	result = libcdatetime_elements_copy_to_string_with_index(
	          elements,
	          string,
	          9,
	          &string_index,
	          LIBCDATETIME_STRING_FORMAT_TYPE_ISO8601 | LIBCDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS | LIBCDATETIME_STRING_FORMAT_FLAG_TIMEZONE_INDICATOR,
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

	/* Test copy to string, which is too small for date and time seperator
	 */
	string_index = 0;

	result = libcdatetime_elements_copy_to_string_with_index(
	          elements,
	          string,
	          10,
	          &string_index,
	          LIBCDATETIME_STRING_FORMAT_TYPE_ISO8601 | LIBCDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS | LIBCDATETIME_STRING_FORMAT_FLAG_TIMEZONE_INDICATOR,
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

	/* Test copy to string, which is too small for time
	 */
	string_index = 0;

	result = libcdatetime_elements_copy_to_string_with_index(
	          elements,
	          string,
	          18,
	          &string_index,
	          LIBCDATETIME_STRING_FORMAT_TYPE_ISO8601 | LIBCDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS | LIBCDATETIME_STRING_FORMAT_FLAG_TIMEZONE_INDICATOR,
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

	/* Test copy to string, which is too small for time with milli seconds precision
	 */
	string_index = 0;

	result = libcdatetime_elements_copy_to_string_with_index(
	          elements,
	          string,
	          22,
	          &string_index,
	          LIBCDATETIME_STRING_FORMAT_TYPE_ISO8601 | LIBCDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS | LIBCDATETIME_STRING_FORMAT_FLAG_TIMEZONE_INDICATOR,
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

	/* Test copy to string, which is too small for time with micro seconds precision
	 */
	string_index = 0;

	result = libcdatetime_elements_copy_to_string_with_index(
	          elements,
	          string,
	          25,
	          &string_index,
	          LIBCDATETIME_STRING_FORMAT_TYPE_ISO8601 | LIBCDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS | LIBCDATETIME_STRING_FORMAT_FLAG_TIMEZONE_INDICATOR,
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

	/* Test copy to string, which is too small for time with nano seconds precision
	 */
	string_index = 0;

	result = libcdatetime_elements_copy_to_string_with_index(
	          elements,
	          string,
	          28,
	          &string_index,
	          LIBCDATETIME_STRING_FORMAT_TYPE_ISO8601 | LIBCDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS | LIBCDATETIME_STRING_FORMAT_FLAG_TIMEZONE_INDICATOR,
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

	/* Test copy to string, which is too small for time zone
	 */
	string_index = 0;

	result = libcdatetime_elements_copy_to_string_with_index(
	          elements,
	          string,
	          29,
	          &string_index,
	          LIBCDATETIME_STRING_FORMAT_TYPE_ISO8601 | LIBCDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS | LIBCDATETIME_STRING_FORMAT_FLAG_TIMEZONE_INDICATOR,
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

	/* Test copy to string, which is too small for end-of-string character
	 */
	string_index = 0;

	result = libcdatetime_elements_copy_to_string_with_index(
	          elements,
	          string,
	          30,
	          &string_index,
	          LIBCDATETIME_STRING_FORMAT_TYPE_ISO8601 | LIBCDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS | LIBCDATETIME_STRING_FORMAT_FLAG_TIMEZONE_INDICATOR,
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

	/* Test error cases
	 */
	string_index = 0;

	result = libcdatetime_elements_copy_to_string_with_index(
	          NULL,
	          string,
	          128,
	          &string_index,
	          LIBCDATETIME_STRING_FORMAT_TYPE_CTIME | LIBCDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
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

	result = libcdatetime_elements_copy_to_string_with_index(
	          elements,
	          NULL,
	          128,
	          &string_index,
	          LIBCDATETIME_STRING_FORMAT_TYPE_CTIME | LIBCDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
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

	result = libcdatetime_elements_copy_to_string_with_index(
	          elements,
	          string,
	          (size_t) SSIZE_MAX + 1,
	          &string_index,
	          LIBCDATETIME_STRING_FORMAT_TYPE_CTIME | LIBCDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
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

	result = libcdatetime_elements_copy_to_string_with_index(
	          elements,
	          string,
	          128,
	          NULL,
	          LIBCDATETIME_STRING_FORMAT_TYPE_CTIME | LIBCDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
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

	result = libcdatetime_elements_copy_to_string_with_index(
	          elements,
	          string,
	          128,
	          &string_index,
	          0,
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

	result = libcdatetime_elements_copy_to_string_with_index(
	          elements,
	          string,
	          128,
	          &string_index,
	          LIBCDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
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

	string_index = 0;

	/* Clean up
	 */
	result = libcdatetime_elements_free(
	          &elements,
	          NULL );

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

	CDATETIME_TEST_RUN(
	 "libcdatetime_elements_copy",
	 cdatetime_test_elements_copy() )

	CDATETIME_TEST_RUN(
	 "libcdatetime_elements_get_year",
	 cdatetime_test_elements_get_year() )

	CDATETIME_TEST_RUN(
	 "libcdatetime_elements_get_day_of_year",
	 cdatetime_test_elements_get_day_of_year() )

	CDATETIME_TEST_RUN(
	 "libcdatetime_elements_get_month",
	 cdatetime_test_elements_get_month() )

	CDATETIME_TEST_RUN(
	 "libcdatetime_elements_get_day_of_month",
	 cdatetime_test_elements_get_day_of_month() )

	CDATETIME_TEST_RUN(
	 "libcdatetime_elements_get_date_values",
	 cdatetime_test_elements_get_date_values() )

	CDATETIME_TEST_RUN(
	 "libcdatetime_elements_get_hours",
	 cdatetime_test_elements_get_hours() )

	CDATETIME_TEST_RUN(
	 "libcdatetime_elements_get_minutes",
	 cdatetime_test_elements_get_minutes() )

	CDATETIME_TEST_RUN(
	 "libcdatetime_elements_get_seconds",
	 cdatetime_test_elements_get_seconds() )

	CDATETIME_TEST_RUN(
	 "libcdatetime_elements_get_milli_seconds",
	 cdatetime_test_elements_get_milli_seconds() )

	CDATETIME_TEST_RUN(
	 "libcdatetime_elements_get_micro_seconds",
	 cdatetime_test_elements_get_micro_seconds() )

	CDATETIME_TEST_RUN(
	 "libcdatetime_elements_get_nano_seconds",
	 cdatetime_test_elements_get_nano_seconds() )

	CDATETIME_TEST_RUN(
	 "libcdatetime_elements_get_time_values",
	 cdatetime_test_elements_get_time_values() )

	/* TODO: add test for libcdatetime_internal_elements_set_from_filetime_utc */
	/* TODO: add test for libcdatetime_internal_elements_set_from_time_utc */
	/* TODO: add test for libcdatetime_internal_elements_set_from_time_localtime */

	CDATETIME_TEST_RUN(
	 "libcdatetime_elements_set_current_time_utc",
	 cdatetime_test_elements_set_current_time_utc() )

	CDATETIME_TEST_RUN(
	 "libcdatetime_elements_set_current_time_localtime",
	 cdatetime_test_elements_set_current_time_localtime() )

	CDATETIME_TEST_RUN(
	 "libcdatetime_elements_get_delta_in_seconds",
	 cdatetime_test_elements_get_delta_in_seconds() )

	/* TODO: add test for libcdatetime_elements_set_from_delta_in_seconds */

	CDATETIME_TEST_RUN(
	 "libcdatetime_elements_get_string_size",
	 cdatetime_test_elements_get_string_size() )

	CDATETIME_TEST_RUN(
	 "libcdatetime_elements_copy_to_string",
	 cdatetime_test_elements_copy_to_string() )

	CDATETIME_TEST_RUN(
	 "libcdatetime_elements_copy_to_string_with_index",
	 cdatetime_test_elements_copy_to_string_with_index() )

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

