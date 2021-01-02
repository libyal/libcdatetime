/*
 * Library elements type test program
 *
 * Copyright (C) 2013-2021, Joachim Metz <joachim.metz@gmail.com>
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
#include <memory.h>
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

#include "../libcdatetime/libcdatetime_elements.h"

#if defined( HAVE_GNU_DL_DLSYM ) && defined( __GNUC__ ) && !defined( __CYGWIN__ )

static struct tm *(*cdatetime_test_real_gmtime_r)(const time_t *, struct tm *) = NULL;
static time_t (*cdatetime_test_real_time)(time_t *)                            = NULL;

int cdatetime_test_gmtime_r_attempts_before_fail                               = -1;
int cdatetime_test_time_attempts_before_fail                                   = -1;

/* Custom time for testing error cases
 * Returns a pointer to newly allocated data or NULL
 */
struct tm *gmtime_r(
     const time_t *timep,
     struct tm *result )
{
	struct tm *result_tm = NULL;

	if( cdatetime_test_real_gmtime_r == NULL )
	{
		cdatetime_test_real_gmtime_r = dlsym(
		                                RTLD_NEXT,
		                                "gmtime_r" );
	}
	if( cdatetime_test_gmtime_r_attempts_before_fail == 0 )
	{
		cdatetime_test_gmtime_r_attempts_before_fail = -1;

		return( NULL );
	}
	else if( cdatetime_test_gmtime_r_attempts_before_fail > 0 )
	{
		cdatetime_test_gmtime_r_attempts_before_fail--;
	}
	result_tm = cdatetime_test_real_gmtime_r(
	             timep,
	             result );

	return( result_tm );
}

/* Custom time for testing error cases
 * Returns a pointer to newly allocated data or NULL
 */
time_t time(
     time_t *tloc )
{
	time_t result_time = 0;

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
	result_time = cdatetime_test_real_time(
	               tloc );

	return( result_time );
}

#endif /* defined( HAVE_GNU_DL_DLSYM ) && defined( __GNUC__ ) && !defined( __CYGWIN__ ) */

/* Tests the libcdatetime_elements_initialize function
 * Returns 1 if successful or 0 if not
 */
int cdatetime_test_elements_initialize(
     void )
{
	libcdatetime_elements_t *elements = NULL;
	libcerror_error_t *error          = NULL;
	int result                        = 0;

#if defined( HAVE_CDATETIME_TEST_MEMORY )
	int number_of_malloc_fail_tests   = 1;
	int number_of_memset_fail_tests   = 1;
	int test_number                   = 0;
#endif

	/* Test regular cases
	 */
	result = libcdatetime_elements_initialize(
	          &elements,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
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

	CDATETIME_TEST_ASSERT_EQUAL_INT(
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

	CDATETIME_TEST_ASSERT_EQUAL_INT(
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

	elements = NULL;

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

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libcdatetime_elements_initialize with malloc failing
		 */
		cdatetime_test_malloc_attempts_before_fail = test_number;

		result = libcdatetime_elements_initialize(
		          &elements,
		          &error );

		if( cdatetime_test_malloc_attempts_before_fail != -1 )
		{
			cdatetime_test_malloc_attempts_before_fail = -1;

			if( elements != NULL )
			{
				libcdatetime_elements_free(
				 &elements,
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
			 "elements",
			 elements );

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
		/* Test libcdatetime_elements_initialize with memset failing
		 */
		cdatetime_test_memset_attempts_before_fail = test_number;

		result = libcdatetime_elements_initialize(
		          &elements,
		          &error );

		if( cdatetime_test_memset_attempts_before_fail != -1 )
		{
			cdatetime_test_memset_attempts_before_fail = -1;

			if( elements != NULL )
			{
				libcdatetime_elements_free(
				 &elements,
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
			 "elements",
			 elements );

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

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "elements",
	 elements );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcdatetime_elements_initialize(
	          &destination_elements,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "destination_elements",
	 destination_elements );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test elements entry copy
	 */
	result = libcdatetime_elements_copy(
	          destination_elements,
	          elements,
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
	result = libcdatetime_elements_copy(
	          NULL,
	          elements,
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

	result = libcdatetime_elements_copy(
	          destination_elements,
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
	result = libcdatetime_elements_free(
	          &destination_elements,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "destination_elements",
	 destination_elements );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcdatetime_elements_free(
	          &elements,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "elements",
	 elements );

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
	uint16_t year                     = 0;
	int result                        = 0;

#if defined( WINAPI ) && ( WINVER >= 0x0500 )
	WORD time_elements_year           = 0;
#else
	int time_elements_year            = 0;
#endif

	/* Initialize test
	 */
	result = libcdatetime_elements_initialize(
	          &elements,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "elements",
	 elements );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#if defined( __GNUC__ ) && !defined( LIBCDATETIME_DLL_IMPORT )

	/* Test get year
	 */
	result = libcdatetime_elements_set_date_and_time_values(
	          elements,
	          2019,
	          2,
	          26,
	          6,
	          59,
	          51,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcdatetime_elements_get_year(
	          elements,
	          &year,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "year",
	 year,
	 2019 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#endif /* defined( __GNUC__ ) && !defined( LIBCDATETIME_DLL_IMPORT ) */

	/* Test error cases
	 */
	result = libcdatetime_elements_get_year(
	          NULL,
	          &year,
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

	result = libcdatetime_elements_get_year(
	          elements,
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
	time_elements_year = ( (libcdatetime_internal_elements_t *) elements )->systemtime.wYear;

	( (libcdatetime_internal_elements_t *) elements )->systemtime.wYear = 0;

	result = libcdatetime_elements_get_year(
	          elements,
	          &year,
	          &error );

	( (libcdatetime_internal_elements_t *) elements )->systemtime.wYear = time_elements_year;
#else
	time_elements_year = ( (libcdatetime_internal_elements_t *) elements )->tm.tm_year;

	( (libcdatetime_internal_elements_t *) elements )->tm.tm_year = (int) -UINT16_MAX - 1901;

	result = libcdatetime_elements_get_year(
	          elements,
	          &year,
	          &error );

	( (libcdatetime_internal_elements_t *) elements )->tm.tm_year = time_elements_year;
#endif

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
	result = libcdatetime_elements_free(
	          &elements,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "elements",
	 elements );

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
	uint16_t day_of_year              = 0;
	int result                        = 0;

#if defined( WINAPI ) && ( WINVER >= 0x0500 )
	WORD time_elements_month          = 0;
#else
	int time_elements_day_of_year     = 0;
#endif

	/* Initialize test
	 */
	result = libcdatetime_elements_initialize(
	          &elements,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "elements",
	 elements );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#if defined( __GNUC__ ) && !defined( LIBCDATETIME_DLL_IMPORT )

	/* Test get day of year in a leap year
	 */
	result = libcdatetime_elements_set_date_and_time_values(
	          elements,
	          2000,
	          3,
	          17,
	          14,
	          44,
	          32,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcdatetime_elements_get_day_of_year(
	          elements,
	          &day_of_year,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "day_of_year",
	 day_of_year,
	 76 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test get day of year in a non-leap year
	 */
	result = libcdatetime_elements_set_date_and_time_values(
	          elements,
	          2019,
	          2,
	          26,
	          6,
	          59,
	          51,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcdatetime_elements_get_day_of_year(
	          elements,
	          &day_of_year,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "day_of_year",
	 day_of_year,
	 56 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#endif /* defined( __GNUC__ ) && !defined( LIBCDATETIME_DLL_IMPORT ) */

	/* Test error cases
	 */
	result = libcdatetime_elements_get_day_of_year(
	          NULL,
	          &day_of_year,
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

	result = libcdatetime_elements_get_day_of_year(
	          elements,
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
	time_elements_month = ( (libcdatetime_internal_elements_t *) elements )->systemtime.wMonth;

	( (libcdatetime_internal_elements_t *) elements )->systemtime.wMonth = 0;

	result = libcdatetime_elements_get_day_of_year(
	          elements,
	          &day_of_year,
	          &error );

	( (libcdatetime_internal_elements_t *) elements )->systemtime.wMonth = time_elements_month;
#else
	time_elements_day_of_year = ( (libcdatetime_internal_elements_t *) elements )->tm.tm_yday;

	( (libcdatetime_internal_elements_t *) elements )->tm.tm_yday = -1;

	result = libcdatetime_elements_get_day_of_year(
	          elements,
	          &day_of_year,
	          &error );

	( (libcdatetime_internal_elements_t *) elements )->tm.tm_yday = time_elements_day_of_year;
#endif

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
	result = libcdatetime_elements_free(
	          &elements,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "elements",
	 elements );

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
	uint8_t month                     = 0;
	int result                        = 0;

#if defined( WINAPI ) && ( WINVER >= 0x0500 )
	WORD time_elements_month          = 0;
#else
	int time_elements_month           = 0;
#endif

	/* Initialize test
	 */
	result = libcdatetime_elements_initialize(
	          &elements,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "elements",
	 elements );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#if defined( __GNUC__ ) && !defined( LIBCDATETIME_DLL_IMPORT )

	/* Test get month
	 */
	result = libcdatetime_elements_set_date_and_time_values(
	          elements,
	          2019,
	          2,
	          26,
	          6,
	          59,
	          51,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcdatetime_elements_get_month(
	          elements,
	          &month,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "month",
	 month,
	 2 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#endif /* defined( __GNUC__ ) && !defined( LIBCDATETIME_DLL_IMPORT ) */

	/* Test error cases
	 */
	result = libcdatetime_elements_get_month(
	          NULL,
	          &month,
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

	result = libcdatetime_elements_get_month(
	          elements,
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
	time_elements_month = ( (libcdatetime_internal_elements_t *) elements )->systemtime.wMonth;

	( (libcdatetime_internal_elements_t *) elements )->systemtime.wMonth = 0;

	result = libcdatetime_elements_get_month(
	          elements,
	          &month,
	          &error );

	( (libcdatetime_internal_elements_t *) elements )->systemtime.wMonth = time_elements_month;
#else
	time_elements_month = ( (libcdatetime_internal_elements_t *) elements )->tm.tm_mon;

	( (libcdatetime_internal_elements_t *) elements )->tm.tm_mon = -1;

	result = libcdatetime_elements_get_month(
	          elements,
	          &month,
	          &error );

	( (libcdatetime_internal_elements_t *) elements )->tm.tm_mon = time_elements_month;
#endif

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
	result = libcdatetime_elements_free(
	          &elements,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "elements",
	 elements );

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
	uint8_t day_of_month              = 0;
	int result                        = 0;

#if defined( WINAPI ) && ( WINVER >= 0x0500 )
	WORD time_elements_day_of_month   = 0;
	WORD time_elements_month          = 0;
#else
	int time_elements_day_of_month    = 0;
	int time_elements_month           = 0;
#endif

	/* Initialize test
	 */
	result = libcdatetime_elements_initialize(
	          &elements,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "elements",
	 elements );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#if defined( __GNUC__ ) && !defined( LIBCDATETIME_DLL_IMPORT )

	/* Test get day of month
	 */
	result = libcdatetime_elements_set_date_and_time_values(
	          elements,
	          2019,
	          2,
	          26,
	          6,
	          59,
	          51,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcdatetime_elements_get_day_of_month(
	          elements,
	          &day_of_month,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "day_of_month",
	 day_of_month,
	 26 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#endif /* defined( __GNUC__ ) && !defined( LIBCDATETIME_DLL_IMPORT ) */

	/* Test error cases
	 */
	result = libcdatetime_elements_get_day_of_month(
	          NULL,
	          &day_of_month,
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

	result = libcdatetime_elements_get_day_of_month(
	          elements,
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
	time_elements_month = ( (libcdatetime_internal_elements_t *) elements )->systemtime.wMonth;

	( (libcdatetime_internal_elements_t *) elements )->systemtime.wMonth = 0;

	result = libcdatetime_elements_get_day_of_month(
	          elements,
	          &day_of_month,
	          &error );

	( (libcdatetime_internal_elements_t *) elements )->systemtime.wMonth = time_elements_month;
#else
	time_elements_month = ( (libcdatetime_internal_elements_t *) elements )->tm.tm_mon;

	( (libcdatetime_internal_elements_t *) elements )->tm.tm_mon = -1;

	result = libcdatetime_elements_get_day_of_month(
	          elements,
	          &day_of_month,
	          &error );

	( (libcdatetime_internal_elements_t *) elements )->tm.tm_mon = time_elements_month;
#endif

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
	time_elements_day_of_month = ( (libcdatetime_internal_elements_t *) elements )->systemtime.wDay;

	( (libcdatetime_internal_elements_t *) elements )->systemtime.wDay = 0;

	result = libcdatetime_elements_get_day_of_month(
	          elements,
	          &day_of_month,
	          &error );

	( (libcdatetime_internal_elements_t *) elements )->systemtime.wDay = time_elements_day_of_month;
#else
	time_elements_day_of_month = ( (libcdatetime_internal_elements_t *) elements )->tm.tm_mday;

	( (libcdatetime_internal_elements_t *) elements )->tm.tm_mday = -1;

	result = libcdatetime_elements_get_day_of_month(
	          elements,
	          &day_of_month,
	          &error );

	( (libcdatetime_internal_elements_t *) elements )->tm.tm_mday = time_elements_day_of_month;
#endif

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
	result = libcdatetime_elements_free(
	          &elements,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "elements",
	 elements );

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

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "elements",
	 elements );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#if defined( __GNUC__ ) && !defined( LIBCDATETIME_DLL_IMPORT )

	/* Test get date values
	 */
	result = libcdatetime_elements_set_date_and_time_values(
	          elements,
	          2019,
	          2,
	          26,
	          6,
	          59,
	          51,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcdatetime_elements_get_date_values(
	          elements,
	          &year,
	          &month,
	          &day_of_month,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "year",
	 year,
	 2019 );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "month",
	 month,
	 2 );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "day_of_month",
	 day_of_month,
	 26 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#endif /* defined( __GNUC__ ) && !defined( LIBCDATETIME_DLL_IMPORT ) */

	/* Test error cases
	 */
	result = libcdatetime_elements_get_date_values(
	          NULL,
	          &year,
	          &month,
	          &day_of_month,
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

	result = libcdatetime_elements_get_date_values(
	          elements,
	          NULL,
	          &month,
	          &day_of_month,
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

	result = libcdatetime_elements_get_date_values(
	          elements,
	          &year,
	          NULL,
	          &day_of_month,
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

	result = libcdatetime_elements_get_date_values(
	          elements,
	          &year,
	          &month,
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
	result = libcdatetime_elements_free(
	          &elements,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "elements",
	 elements );

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
	uint8_t hours                     = 0;
	int result                        = 0;

#if defined( WINAPI ) && ( WINVER >= 0x0500 )
	WORD time_elements_hour           = 0;
#else
	int time_elements_hour            = 0;
#endif

	/* Initialize test
	 */
	result = libcdatetime_elements_initialize(
	          &elements,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "elements",
	 elements );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#if defined( __GNUC__ ) && !defined( LIBCDATETIME_DLL_IMPORT )

	/* Test get hours
	 */
	result = libcdatetime_elements_set_date_and_time_values(
	          elements,
	          2019,
	          2,
	          26,
	          6,
	          59,
	          51,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcdatetime_elements_get_hours(
	          elements,
	          &hours,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "hours",
	 hours,
	 6 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#endif /* defined( __GNUC__ ) && !defined( LIBCDATETIME_DLL_IMPORT ) */

	/* Test error cases
	 */
	result = libcdatetime_elements_get_hours(
	          NULL,
	          &hours,
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

	result = libcdatetime_elements_get_hours(
	          elements,
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
	time_elements_hour = ( (libcdatetime_internal_elements_t *) elements )->systemtime.wHour;

	( (libcdatetime_internal_elements_t *) elements )->systemtime.wHour = 24;

	result = libcdatetime_elements_get_hours(
	          elements,
	          &hours,
	          &error );

	( (libcdatetime_internal_elements_t *) elements )->systemtime.wHour = time_elements_hour;
#else
	time_elements_hour = ( (libcdatetime_internal_elements_t *) elements )->tm.tm_hour;

	( (libcdatetime_internal_elements_t *) elements )->tm.tm_hour = -1;

	result = libcdatetime_elements_get_hours(
	          elements,
	          &hours,
	          &error );

	( (libcdatetime_internal_elements_t *) elements )->tm.tm_hour = time_elements_hour;
#endif

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
	result = libcdatetime_elements_free(
	          &elements,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "elements",
	 elements );

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
	uint8_t minutes                   = 0;
	int result                        = 0;

#if defined( WINAPI ) && ( WINVER >= 0x0500 )
	WORD time_elements_minute         = 0;
#else
	int time_elements_minute          = 0;
#endif

	/* Initialize test
	 */
	result = libcdatetime_elements_initialize(
	          &elements,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "elements",
	 elements );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#if defined( __GNUC__ ) && !defined( LIBCDATETIME_DLL_IMPORT )

	/* Test get minutes
	 */
	result = libcdatetime_elements_set_date_and_time_values(
	          elements,
	          2019,
	          2,
	          26,
	          6,
	          59,
	          51,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcdatetime_elements_get_minutes(
	          elements,
	          &minutes,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "minutes",
	 minutes,
	 59 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#endif /* defined( __GNUC__ ) && !defined( LIBCDATETIME_DLL_IMPORT ) */

	/* Test error cases
	 */
	result = libcdatetime_elements_get_minutes(
	          NULL,
	          &minutes,
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

	result = libcdatetime_elements_get_minutes(
	          elements,
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
	time_elements_minute = ( (libcdatetime_internal_elements_t *) elements )->systemtime.wMinute;

	( (libcdatetime_internal_elements_t *) elements )->systemtime.wMinute = 60;

	result = libcdatetime_elements_get_minutes(
	          elements,
	          &minutes,
	          &error );

	( (libcdatetime_internal_elements_t *) elements )->systemtime.wMinute = time_elements_minute;
#else
	time_elements_minute = ( (libcdatetime_internal_elements_t *) elements )->tm.tm_min;

	( (libcdatetime_internal_elements_t *) elements )->tm.tm_min = -1;

	result = libcdatetime_elements_get_minutes(
	          elements,
	          &minutes,
	          &error );

	( (libcdatetime_internal_elements_t *) elements )->tm.tm_min = time_elements_minute;
#endif

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
	result = libcdatetime_elements_free(
	          &elements,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "elements",
	 elements );

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
	uint8_t seconds                   = 0;
	int result                        = 0;

#if defined( WINAPI ) && ( WINVER >= 0x0500 )
	WORD time_elements_second         = 0;
#else
	int time_elements_second          = 0;
#endif

	/* Initialize test
	 */
	result = libcdatetime_elements_initialize(
	          &elements,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "elements",
	 elements );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#if defined( __GNUC__ ) && !defined( LIBCDATETIME_DLL_IMPORT )

	/* Test get seconds
	 */
	result = libcdatetime_elements_set_date_and_time_values(
	          elements,
	          2019,
	          2,
	          26,
	          6,
	          59,
	          51,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcdatetime_elements_get_seconds(
	          elements,
	          &seconds,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "seconds",
	 seconds,
	 51 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#endif /* defined( __GNUC__ ) && !defined( LIBCDATETIME_DLL_IMPORT ) */

	/* Test error cases
	 */
	result = libcdatetime_elements_get_seconds(
	          NULL,
	          &seconds,
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

	result = libcdatetime_elements_get_seconds(
	          elements,
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
	time_elements_second = ( (libcdatetime_internal_elements_t *) elements )->systemtime.wSecond;

	( (libcdatetime_internal_elements_t *) elements )->systemtime.wSecond = 60;

	result = libcdatetime_elements_get_seconds(
	          elements,
	          &seconds,
	          &error );

	( (libcdatetime_internal_elements_t *) elements )->systemtime.wSecond = time_elements_second;
#else
	time_elements_second = ( (libcdatetime_internal_elements_t *) elements )->tm.tm_sec;

	( (libcdatetime_internal_elements_t *) elements )->tm.tm_sec = -1;

	result = libcdatetime_elements_get_seconds(
	          elements,
	          &seconds,
	          &error );

	( (libcdatetime_internal_elements_t *) elements )->tm.tm_sec = time_elements_second;
#endif

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
	result = libcdatetime_elements_free(
	          &elements,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "elements",
	 elements );

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
	uint16_t milli_seconds            = 0;
	int result                        = 0;

#if defined( WINAPI ) && ( WINVER >= 0x0500 )
	WORD time_elements_milli_second   = 0;
#endif

	/* Initialize test
	 */
	result = libcdatetime_elements_initialize(
	          &elements,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "elements",
	 elements );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#if defined( __GNUC__ ) && !defined( LIBCDATETIME_DLL_IMPORT )

	/* Test get milli seconds
	 */
	result = libcdatetime_elements_set_date_and_time_values(
	          elements,
	          2019,
	          2,
	          26,
	          6,
	          59,
	          51,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcdatetime_elements_get_milli_seconds(
	          elements,
	          &milli_seconds,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "milli_seconds",
	 milli_seconds,
	 0 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#endif /* defined( __GNUC__ ) && !defined( LIBCDATETIME_DLL_IMPORT ) */

	/* Test error cases
	 */
	result = libcdatetime_elements_get_milli_seconds(
	          NULL,
	          &milli_seconds,
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

	result = libcdatetime_elements_get_milli_seconds(
	          elements,
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
	time_elements_milli_second = ( (libcdatetime_internal_elements_t *) elements )->systemtime.wMilliseconds;

	( (libcdatetime_internal_elements_t *) elements )->systemtime.wMilliseconds = 1000;

	result = libcdatetime_elements_get_milli_seconds(
	          elements,
	          &milli_seconds,
	          &error );

	( (libcdatetime_internal_elements_t *) elements )->systemtime.wMilliseconds = time_elements_milli_second;

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	CDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );
#endif

	/* Clean up
	 */
	result = libcdatetime_elements_free(
	          &elements,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "elements",
	 elements );

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
	uint16_t micro_seconds            = 0;
	int result                        = 0;

	/* Initialize test
	 */
	result = libcdatetime_elements_initialize(
	          &elements,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "elements",
	 elements );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#if defined( __GNUC__ ) && !defined( LIBCDATETIME_DLL_IMPORT )

	/* Test get micro seconds
	 */
	result = libcdatetime_elements_set_date_and_time_values(
	          elements,
	          2019,
	          2,
	          26,
	          6,
	          59,
	          51,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcdatetime_elements_get_micro_seconds(
	          elements,
	          &micro_seconds,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "micro_seconds",
	 micro_seconds,
	 0 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#endif /* defined( __GNUC__ ) && !defined( LIBCDATETIME_DLL_IMPORT ) */

	/* Test error cases
	 */
	result = libcdatetime_elements_get_micro_seconds(
	          NULL,
	          &micro_seconds,
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

	result = libcdatetime_elements_get_micro_seconds(
	          elements,
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
	result = libcdatetime_elements_free(
	          &elements,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "elements",
	 elements );

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
	uint16_t nano_seconds             = 0;
	int result                        = 0;

	/* Initialize test
	 */
	result = libcdatetime_elements_initialize(
	          &elements,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "elements",
	 elements );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#if defined( __GNUC__ ) && !defined( LIBCDATETIME_DLL_IMPORT )

	result = libcdatetime_elements_set_date_and_time_values(
	          elements,
	          2019,
	          2,
	          26,
	          6,
	          59,
	          51,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#endif /* defined( __GNUC__ ) && !defined( LIBCDATETIME_DLL_IMPORT ) */

	/* Test get nano seconds
	 */
	result = libcdatetime_elements_get_nano_seconds(
	          elements,
	          &nano_seconds,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "nano_seconds",
	 nano_seconds,
	 0 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libcdatetime_elements_get_nano_seconds(
	          NULL,
	          &nano_seconds,
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

	result = libcdatetime_elements_get_nano_seconds(
	          elements,
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
	result = libcdatetime_elements_free(
	          &elements,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "elements",
	 elements );

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
	uint8_t hours                     = 0;
	uint8_t minutes                   = 0;
	uint8_t seconds                   = 0;
	int result                        = 0;

	/* Initialize test
	 */
	result = libcdatetime_elements_initialize(
	          &elements,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "elements",
	 elements );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#if defined( __GNUC__ ) && !defined( LIBCDATETIME_DLL_IMPORT )

	/* Test get time values
	 */
	result = libcdatetime_elements_set_date_and_time_values(
	          elements,
	          2019,
	          2,
	          26,
	          6,
	          59,
	          51,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcdatetime_elements_get_time_values(
	          elements,
	          &hours,
	          &minutes,
	          &seconds,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "hours",
	 hours,
	 6 );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "minutes",
	 minutes,
	 59 );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "seconds",
	 seconds,
	 51 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#endif /* defined( __GNUC__ ) && !defined( LIBCDATETIME_DLL_IMPORT ) */

	/* Test error cases
	 */
	result = libcdatetime_elements_get_time_values(
	          NULL,
	          &hours,
	          &minutes,
	          &seconds,
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

	result = libcdatetime_elements_get_time_values(
	          elements,
	          NULL,
	          &minutes,
	          &seconds,
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

	result = libcdatetime_elements_get_time_values(
	          elements,
	          &hours,
	          NULL,
	          &seconds,
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

	result = libcdatetime_elements_get_time_values(
	          elements,
	          &hours,
	          &minutes,
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
	result = libcdatetime_elements_free(
	          &elements,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "elements",
	 elements );

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
	if( elements != NULL )
	{
		libcdatetime_elements_free(
		 &elements,
		 NULL );
	}
	return( 0 );
}

#if defined( __GNUC__ ) && !defined( LIBCDATETIME_DLL_IMPORT )

/* Tests the libcdatetime_elements_set_date_and_time_values function
 * Returns 1 if successful or 0 if not
 */
int cdatetime_test_elements_set_date_and_time_values(
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

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "elements",
	 elements );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test get time values
	 */
	result = libcdatetime_elements_set_date_and_time_values(
	          elements,
	          2019,
	          2,
	          26,
	          6,
	          59,
	          51,
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
	result = libcdatetime_elements_set_date_and_time_values(
	          NULL,
	          2019,
	          2,
	          26,
	          6,
	          59,
	          51,
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

	/* Test year value out of bounds
	 */
	result = libcdatetime_elements_set_date_and_time_values(
	          elements,
	          1234,
	          2,
	          26,
	          6,
	          59,
	          51,
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
#endif

	/* Test month value out of bounds
	 */
	result = libcdatetime_elements_set_date_and_time_values(
	          elements,
	          2019,
	          13,
	          26,
	          6,
	          59,
	          51,
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

	/* Test day of month value out of bounds
	 */
	result = libcdatetime_elements_set_date_and_time_values(
	          elements,
	          2019,
	          2,
	          31,
	          6,
	          59,
	          51,
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

	/* Test hours value out of bounds
	 */
	result = libcdatetime_elements_set_date_and_time_values(
	          elements,
	          2019,
	          2,
	          26,
	          24,
	          59,
	          51,
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

	/* Test minutes value out of bounds
	 */
	result = libcdatetime_elements_set_date_and_time_values(
	          elements,
	          2019,
	          2,
	          26,
	          6,
	          60,
	          51,
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

	/* Test seconds value out of bounds
	 */
	result = libcdatetime_elements_set_date_and_time_values(
	          elements,
	          2019,
	          2,
	          26,
	          6,
	          59,
	          60,
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
	result = libcdatetime_elements_free(
	          &elements,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "elements",
	 elements );

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
	if( elements != NULL )
	{
		libcdatetime_elements_free(
		 &elements,
		 NULL );
	}
	return( 0 );
}

#if defined( WINAPI ) && ( WINVER >= 0x0500 )

/* Tests the libcdatetime_internal_elements_set_from_filetime_utc function
 * Returns 1 if successful or 0 if not
 */
int cdatetime_test_internal_elements_set_from_filetime_utc(
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

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "elements",
	 elements );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */

	/* Test error cases
	 */
	result = libcdatetime_internal_elements_set_from_filetime_utc(
	          NULL,
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

	result = libcdatetime_internal_elements_set_from_filetime_utc(
	          elements,
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
	result = libcdatetime_elements_free(
	          &elements,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "elements",
	 elements );

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
	if( elements != NULL )
	{
		libcdatetime_elements_free(
		 &elements,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( WINAPI ) && ( WINVER >= 0x0500 ) */

#if !defined( WINAPI ) && defined( HAVE_TIME ) && ( defined( HAVE_GMTIME ) || defined( HAVE_GMTIME_R ) )

/* Tests the libcdatetime_internal_elements_set_from_time_utc function
 * Returns 1 if successful or 0 if not
 */
int cdatetime_test_internal_elements_set_from_time_utc(
     void )
{
	libcdatetime_elements_t *elements = NULL;
	libcerror_error_t *error          = NULL;
	time_t time_value                 = 0;
	int result                        = 0;

	/* Initialize test
	 */
	result = libcdatetime_elements_initialize(
	          &elements,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "elements",
	 elements );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test set current time in UTC
	 */
	result = libcdatetime_internal_elements_set_from_time_utc(
	          (libcdatetime_internal_elements_t *) elements,
	          &time_value,
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
	result = libcdatetime_internal_elements_set_from_time_utc(
	          NULL,
	          &time_value,
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

	result = libcdatetime_internal_elements_set_from_time_utc(
	          (libcdatetime_internal_elements_t *) elements,
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

#if defined( HAVE_GNU_DL_DLSYM ) && defined( __GNUC__ ) && !defined( __CYGWIN__ )

	/* Test libcdatetime_internal_elements_set_from_time_utc with gmtime_r failing
	 */
	cdatetime_test_gmtime_r_attempts_before_fail = 0;

	result = libcdatetime_internal_elements_set_from_time_utc(
	          (libcdatetime_internal_elements_t *) elements,
	          &time_value,
	          &error );

	if( cdatetime_test_gmtime_r_attempts_before_fail != -1 )
	{
		cdatetime_test_gmtime_r_attempts_before_fail = -1;
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

	/* Clean up
	 */
	result = libcdatetime_elements_free(
	          &elements,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "elements",
	 elements );

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
	if( elements != NULL )
	{
		libcdatetime_elements_free(
		 &elements,
		 NULL );
	}
	return( 0 );
}

#endif /* !defined( WINAPI ) && defined( HAVE_TIME ) && ( defined( HAVE_GMTIME ) || defined( HAVE_GMTIME_R ) ) */

#if !defined( WINAPI ) && defined( HAVE_TIME ) && ( defined( HAVE_LOCALTIME ) || defined( HAVE_LOCALTIME_R ) )

/* Tests the libcdatetime_internal_elements_set_from_time_localtime function
 * Returns 1 if successful or 0 if not
 */
int cdatetime_test_internal_elements_set_from_time_localtime(
     void )
{
	libcdatetime_elements_t *elements = NULL;
	libcerror_error_t *error          = NULL;
	time_t time_value                 = 0;
	int result                        = 0;

	/* Initialize test
	 */
	result = libcdatetime_elements_initialize(
	          &elements,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "elements",
	 elements );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test set current time in UTC
	 */
	result = libcdatetime_internal_elements_set_from_time_localtime(
	          (libcdatetime_internal_elements_t *) elements,
	          &time_value,
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
	result = libcdatetime_internal_elements_set_from_time_localtime(
	          NULL,
	          &time_value,
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

	result = libcdatetime_internal_elements_set_from_time_localtime(
	          (libcdatetime_internal_elements_t *) elements,
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
	result = libcdatetime_elements_free(
	          &elements,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "elements",
	 elements );

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
	if( elements != NULL )
	{
		libcdatetime_elements_free(
		 &elements,
		 NULL );
	}
	return( 0 );
}

#endif /* !defined( WINAPI ) && defined( HAVE_TIME ) && ( defined( HAVE_LOCALTIME ) || defined( HAVE_LOCALTIME_R ) ) */

#endif /* defined( __GNUC__ ) && !defined( LIBCDATETIME_DLL_IMPORT ) */

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

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "elements",
	 elements );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test set current time in UTC
	 */
	result = libcdatetime_elements_set_current_time_utc(
	          elements,
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
	result = libcdatetime_elements_set_current_time_utc(
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

#if defined( HAVE_GNU_DL_DLSYM ) && defined( __GNUC__ ) && !defined( __CYGWIN__ )

	/* Test libcdatetime_elements_set_current_time_utc with time failing
	 */
	cdatetime_test_time_attempts_before_fail = 0;

	result = libcdatetime_elements_set_current_time_utc(
	          elements,
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

	/* Clean up
	 */
	result = libcdatetime_elements_free(
	          &elements,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "elements",
	 elements );

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
	if( elements != NULL )
	{
		libcdatetime_elements_free(
		 &elements,
		 NULL );
	}
	return( 0 );
}

/* Tests the libcdatetime_elements_set_current_time_localtime function
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

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "elements",
	 elements );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test set current time in localtime
	 */
	result = libcdatetime_elements_set_current_time_localtime(
	          elements,
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
	result = libcdatetime_elements_set_current_time_localtime(
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

#if defined( HAVE_GNU_DL_DLSYM ) && defined( __GNUC__ ) && !defined( __CYGWIN__ )

	/* Test libcdatetime_elements_set_current_time_localtime with time failing
	 */
	cdatetime_test_time_attempts_before_fail = 0;

	result = libcdatetime_elements_set_current_time_localtime(
	          elements,
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

	/* Clean up
	 */
	result = libcdatetime_elements_free(
	          &elements,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "elements",
	 elements );

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

	/* Initialize test
	 */
	result = libcdatetime_elements_initialize(
	          &first_elements,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "first_elements",
	 first_elements );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcdatetime_elements_initialize(
	          &second_elements,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "second_elements",
	 second_elements );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libcdatetime_elements_get_delta_in_seconds(
	          first_elements,
	          second_elements,
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
	result = libcdatetime_elements_get_delta_in_seconds(
	          NULL,
	          second_elements,
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

	result = libcdatetime_elements_get_delta_in_seconds(
	          first_elements,
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

	result = libcdatetime_elements_get_delta_in_seconds(
	          first_elements,
	          second_elements,
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
	result = libcdatetime_elements_free(
	          &second_elements,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "second_elements",
	 second_elements );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcdatetime_elements_free(
	          &first_elements,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "first_elements",
	 first_elements );

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
	if( second_elements != NULL )
	{
		libcdatetime_elements_free(
		 &second_elements,
		 NULL );
	}
	if( first_elements != NULL )
	{
		libcdatetime_elements_free(
		 &first_elements,
		 NULL );
	}
	return( 0 );
}

/* Tests the libcdatetime_elements_set_from_delta_in_seconds function
 * Returns 1 if successful or 0 if not
 */
int cdatetime_test_elements_set_from_delta_in_seconds(
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

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "elements",
	 elements );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libcdatetime_elements_set_from_delta_in_seconds(
	          elements,
	          1,
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
	result = libcdatetime_elements_set_from_delta_in_seconds(
	          NULL,
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

	/* Clean up
	 */
	result = libcdatetime_elements_free(
	          &elements,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "elements",
	 elements );

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

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "elements",
	 elements );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcdatetime_elements_set_current_time_utc(
	          elements,
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
	result = libcdatetime_elements_get_string_size(
	          elements,
	          &string_size,
	          LIBCDATETIME_STRING_FORMAT_TYPE_CTIME | LIBCDATETIME_STRING_FORMAT_FLAG_DATE_TIME | LIBCDATETIME_STRING_FORMAT_FLAG_TIMEZONE_INDICATOR,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
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

	CDATETIME_TEST_ASSERT_EQUAL_INT(
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

	CDATETIME_TEST_ASSERT_EQUAL_INT(
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

	CDATETIME_TEST_ASSERT_EQUAL_INT(
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

	CDATETIME_TEST_ASSERT_EQUAL_INT(
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
	result = libcdatetime_elements_free(
	          &elements,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "elements",
	 elements );

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

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "elements",
	 elements );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libcdatetime_elements_set_current_time_utc(
	          elements,
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
	result = libcdatetime_elements_copy_to_string(
	          elements,
	          string,
	          128,
	          LIBCDATETIME_STRING_FORMAT_TYPE_CTIME | LIBCDATETIME_STRING_FORMAT_FLAG_DATE_TIME | LIBCDATETIME_STRING_FORMAT_FLAG_TIMEZONE_INDICATOR,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
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
	result = libcdatetime_elements_free(
	          &elements,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "elements",
	 elements );

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

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NOT_NULL(
	 "elements",
	 elements );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#if defined( __GNUC__ ) && !defined( LIBCDATETIME_DLL_IMPORT )

	/* Test copy a date in January to a ctime string
	 */
	result = libcdatetime_elements_set_date_and_time_values(
	          elements,
	          2019,
	          1,
	          26,
	          6,
	          59,
	          51,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	string_index = 0;

	result = libcdatetime_elements_copy_to_string_with_index(
	          elements,
	          string,
	          128,
	          &string_index,
	          LIBCDATETIME_STRING_FORMAT_TYPE_CTIME | LIBCDATETIME_STRING_FORMAT_FLAG_DATE_TIME | LIBCDATETIME_STRING_FORMAT_FLAG_TIMEZONE_INDICATOR,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_EQUAL_SSIZE(
	 "string_index",
	 string_index,
	 (ssize_t) 26 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          "Jan 26, 2019 06:59:51 UTC",
	          string,
	          26 );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test copy a date in February to a ctime string
	 */
	result = libcdatetime_elements_set_date_and_time_values(
	          elements,
	          2019,
	          2,
	          26,
	          6,
	          59,
	          51,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	string_index = 0;

	result = libcdatetime_elements_copy_to_string_with_index(
	          elements,
	          string,
	          128,
	          &string_index,
	          LIBCDATETIME_STRING_FORMAT_TYPE_CTIME | LIBCDATETIME_STRING_FORMAT_FLAG_DATE_TIME | LIBCDATETIME_STRING_FORMAT_FLAG_TIMEZONE_INDICATOR,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_EQUAL_SSIZE(
	 "string_index",
	 string_index,
	 (ssize_t) 26 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          "Feb 26, 2019 06:59:51 UTC",
	          string,
	          26 );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test copy a date in March to a ctime string
	 */
	result = libcdatetime_elements_set_date_and_time_values(
	          elements,
	          2019,
	          3,
	          26,
	          6,
	          59,
	          51,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	string_index = 0;

	result = libcdatetime_elements_copy_to_string_with_index(
	          elements,
	          string,
	          128,
	          &string_index,
	          LIBCDATETIME_STRING_FORMAT_TYPE_CTIME | LIBCDATETIME_STRING_FORMAT_FLAG_DATE_TIME | LIBCDATETIME_STRING_FORMAT_FLAG_TIMEZONE_INDICATOR,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_EQUAL_SSIZE(
	 "string_index",
	 string_index,
	 (ssize_t) 26 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          "Mar 26, 2019 06:59:51 UTC",
	          string,
	          26 );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test copy a date in April to a ctime string
	 */
	result = libcdatetime_elements_set_date_and_time_values(
	          elements,
	          2019,
	          4,
	          26,
	          6,
	          59,
	          51,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	string_index = 0;

	result = libcdatetime_elements_copy_to_string_with_index(
	          elements,
	          string,
	          128,
	          &string_index,
	          LIBCDATETIME_STRING_FORMAT_TYPE_CTIME | LIBCDATETIME_STRING_FORMAT_FLAG_DATE_TIME | LIBCDATETIME_STRING_FORMAT_FLAG_TIMEZONE_INDICATOR,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_EQUAL_SSIZE(
	 "string_index",
	 string_index,
	 (ssize_t) 26 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          "Apr 26, 2019 06:59:51 UTC",
	          string,
	          26 );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

/* TODO add test coverage for remaining months */

	/* Test copy a date in February to an ISO 8601 string
	 */
	result = libcdatetime_elements_set_date_and_time_values(
	          elements,
	          2019,
	          2,
	          26,
	          6,
	          59,
	          51,
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

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

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	CDATETIME_TEST_ASSERT_EQUAL_SSIZE(
	 "string_index",
	 string_index,
	 (ssize_t) 31 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          "2019-02-26T06:59:51.000000000Z",
	          string,
	          31 );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

#endif /* defined( __GNUC__ ) && !defined( LIBCDATETIME_DLL_IMPORT ) */

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

	CDATETIME_TEST_ASSERT_EQUAL_INT(
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

	CDATETIME_TEST_ASSERT_EQUAL_INT(
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

	CDATETIME_TEST_ASSERT_EQUAL_INT(
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

	CDATETIME_TEST_ASSERT_EQUAL_INT(
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

	CDATETIME_TEST_ASSERT_EQUAL_INT(
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

	CDATETIME_TEST_ASSERT_EQUAL_INT(
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

	CDATETIME_TEST_ASSERT_EQUAL_INT(
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

	CDATETIME_TEST_ASSERT_EQUAL_INT(
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

	CDATETIME_TEST_ASSERT_EQUAL_INT(
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

	CDATETIME_TEST_ASSERT_EQUAL_INT(
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

	CDATETIME_TEST_ASSERT_EQUAL_INT(
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

	CDATETIME_TEST_ASSERT_EQUAL_INT(
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

	CDATETIME_TEST_ASSERT_EQUAL_INT(
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

	CDATETIME_TEST_ASSERT_EQUAL_INT(
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

	CDATETIME_TEST_ASSERT_EQUAL_INT(
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

	CDATETIME_TEST_ASSERT_EQUAL_INT(
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

	CDATETIME_TEST_ASSERT_EQUAL_INT(
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
	          &error );

	CDATETIME_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	CDATETIME_TEST_ASSERT_IS_NULL(
	 "elements",
	 elements );

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
	 "libcdatetime_elements_initialize",
	 cdatetime_test_elements_initialize );

	CDATETIME_TEST_RUN(
	 "libcdatetime_elements_free",
	 cdatetime_test_elements_free );

	CDATETIME_TEST_RUN(
	 "libcdatetime_elements_copy",
	 cdatetime_test_elements_copy );

	CDATETIME_TEST_RUN(
	 "libcdatetime_elements_get_year",
	 cdatetime_test_elements_get_year );

	CDATETIME_TEST_RUN(
	 "libcdatetime_elements_get_day_of_year",
	 cdatetime_test_elements_get_day_of_year );

	CDATETIME_TEST_RUN(
	 "libcdatetime_elements_get_month",
	 cdatetime_test_elements_get_month );

	CDATETIME_TEST_RUN(
	 "libcdatetime_elements_get_day_of_month",
	 cdatetime_test_elements_get_day_of_month );

	CDATETIME_TEST_RUN(
	 "libcdatetime_elements_get_date_values",
	 cdatetime_test_elements_get_date_values );

	CDATETIME_TEST_RUN(
	 "libcdatetime_elements_get_hours",
	 cdatetime_test_elements_get_hours );

	CDATETIME_TEST_RUN(
	 "libcdatetime_elements_get_minutes",
	 cdatetime_test_elements_get_minutes );

	CDATETIME_TEST_RUN(
	 "libcdatetime_elements_get_seconds",
	 cdatetime_test_elements_get_seconds );

	CDATETIME_TEST_RUN(
	 "libcdatetime_elements_get_milli_seconds",
	 cdatetime_test_elements_get_milli_seconds );

	CDATETIME_TEST_RUN(
	 "libcdatetime_elements_get_micro_seconds",
	 cdatetime_test_elements_get_micro_seconds );

	CDATETIME_TEST_RUN(
	 "libcdatetime_elements_get_nano_seconds",
	 cdatetime_test_elements_get_nano_seconds );

	CDATETIME_TEST_RUN(
	 "libcdatetime_elements_get_time_values",
	 cdatetime_test_elements_get_time_values );

#if defined( __GNUC__ ) && !defined( LIBCDATETIME_DLL_IMPORT )

	CDATETIME_TEST_RUN(
	 "libcdatetime_elements_set_date_and_time_values",
	 cdatetime_test_elements_set_date_and_time_values );

#if defined( WINAPI ) && ( WINVER >= 0x0500 )

	CDATETIME_TEST_RUN(
	 "libcdatetime_internal_elements_set_from_filetime_utc",
	 cdatetime_test_internal_elements_set_from_filetime_utc );

#endif /* defined( WINAPI ) && ( WINVER >= 0x0500 ) */

#if !defined( WINAPI ) && defined( HAVE_TIME ) && ( defined( HAVE_GMTIME ) || defined( HAVE_GMTIME_R ) )

	CDATETIME_TEST_RUN(
	 "libcdatetime_internal_elements_set_from_time_utc",
	 cdatetime_test_internal_elements_set_from_time_utc );

#endif /* !defined( WINAPI ) && defined( HAVE_TIME ) && ( defined( HAVE_GMTIME ) || defined( HAVE_GMTIME_R ) ) */

#if !defined( WINAPI ) && defined( HAVE_TIME ) && ( defined( HAVE_LOCALTIME ) || defined( HAVE_LOCALTIME_R ) )

	CDATETIME_TEST_RUN(
	 "libcdatetime_internal_elements_set_from_time_localtime",
	 cdatetime_test_internal_elements_set_from_time_localtime );

#endif /* !defined( WINAPI ) && defined( HAVE_TIME ) && ( defined( HAVE_LOCALTIME ) || defined( HAVE_LOCALTIME_R ) ) */

#endif /* defined( __GNUC__ ) && !defined( LIBCDATETIME_DLL_IMPORT ) */

	CDATETIME_TEST_RUN(
	 "libcdatetime_elements_set_current_time_utc",
	 cdatetime_test_elements_set_current_time_utc );

	CDATETIME_TEST_RUN(
	 "libcdatetime_elements_set_current_time_localtime",
	 cdatetime_test_elements_set_current_time_localtime );

	CDATETIME_TEST_RUN(
	 "libcdatetime_elements_get_delta_in_seconds",
	 cdatetime_test_elements_get_delta_in_seconds );

	CDATETIME_TEST_RUN(
	 "libcdatetime_elements_set_from_delta_in_seconds",
	 cdatetime_test_elements_set_from_delta_in_seconds );

	CDATETIME_TEST_RUN(
	 "libcdatetime_elements_get_string_size",
	 cdatetime_test_elements_get_string_size );

	CDATETIME_TEST_RUN(
	 "libcdatetime_elements_copy_to_string",
	 cdatetime_test_elements_copy_to_string );

	CDATETIME_TEST_RUN(
	 "libcdatetime_elements_copy_to_string_with_index",
	 cdatetime_test_elements_copy_to_string_with_index );

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

