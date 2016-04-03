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

#include <stdio.h>

#include "cdatetime_test_libcdatetime.h"
#include "cdatetime_test_libcerror.h"
#include "cdatetime_test_libcstring.h"
#include "cdatetime_test_unused.h"

/* Tests initializing the timestamp
 * Make sure the value timestamp is referencing, is set to NULL
 * Returns 1 if successful, 0 if not or -1 on error
 */
int cdatetime_test_timestamp_initialize(
     libcdatetime_timestamp_t **timestamp,
     int expected_result )
{
	libcerror_error_t *error = NULL;
	static char *function    = "cdatetime_test_timestamp_initialize";
	int result               = 0;

	fprintf(
	 stdout,
	 "Testing initialize\t" );

	result = libcdatetime_timestamp_initialize(
	          timestamp,
	          &error );

	if( result == -1 )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create timestamp.",
		 function );
	}
	if( result != expected_result )
	{
		fprintf(
		 stdout,
		 "(FAIL)" );
	}
	else
	{
		fprintf(
		 stdout,
		 "(PASS)" );
	}
	fprintf(
	 stdout,
	 "\n" );

	if( result == 1 )
	{
		result = libcdatetime_timestamp_free(
		          timestamp,
		          &error );

		if( result != 1 )
		{
			libcerror_error_set(
			 &error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free timestamp.",
			 function );
		}
	}
	if( error != NULL )
	{
		if( result != expected_result )
		{
			libcerror_error_backtrace_fprint(
			 error,
			 stderr );
		}
		libcerror_error_free(
		 &error );
	}
	if( result != expected_result )
	{
		return( 0 );
	}
	return( 1 );
}

/* The main program
 */
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
int wmain( int argc, wchar_t * const argv[] CDATETIME_TEST_ATTRIBUTE_UNUSED )
#else
int main( int argc, char * const argv[] CDATETIME_TEST_ATTRIBUTE_UNUSED )
#endif
{
	libcdatetime_timestamp_t *timestamp = NULL;

	CDATETIME_TEST_UNREFERENCED_PARAMETER( argv )

	if( argc != 1 )
	{
		fprintf(
		 stderr,
		 "Unsupported number of arguments.\n" );

		return( EXIT_FAILURE );
	}
	/* Initialization tests
	 */
	timestamp = NULL;

	if( cdatetime_test_timestamp_initialize(
	     &timestamp,
	     1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test initialize.\n" );

		return( EXIT_FAILURE );
	}
	timestamp = (libcdatetime_timestamp_t *) 0x12345678UL;

	if( cdatetime_test_timestamp_initialize(
	     &timestamp,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test initialize.\n" );

		return( EXIT_FAILURE );
	}
	if( cdatetime_test_timestamp_initialize(
	     NULL,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test initialize.\n" );

		return( EXIT_FAILURE );
	}
	/* TODO: test functions
	 */
	return( EXIT_SUCCESS );
}

