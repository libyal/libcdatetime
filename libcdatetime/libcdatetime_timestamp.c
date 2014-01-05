/*
 * Timestamp functions
 *
 * Copyright (c) 2006-2014, Joachim Metz <joachim.metz@gmail.com>
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
#include <memory.h>
#include <types.h>

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

#include <errno.h>

#include "libcdatetime_definitions.h"
#include "libcdatetime_elements.h"
#include "libcdatetime_libcerror.h"
#include "libcdatetime_timestamp.h"
#include "libcdatetime_types.h"

/* Creates a timestamp
 * Make sure the value timestamp is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libcdatetime_timestamp_initialize(
     libcdatetime_timestamp_t **timestamp,
     libcerror_error_t **error )
{
	libcdatetime_internal_timestamp_t *internal_timestamp = NULL;
	static char *function                                 = "libcdatetime_timestamp_initialize";

	if( timestamp == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid timestamp.",
		 function );

		return( -1 );
	}
	if( *timestamp != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid timestamp value already set.",
		 function );

		return( -1 );
	}
	internal_timestamp = memory_allocate_structure(
	                      libcdatetime_internal_timestamp_t );

	if( internal_timestamp == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create timestamp.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_timestamp,
	     0,
	     sizeof( libcdatetime_internal_timestamp_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear timestamp.",
		 function );

		goto on_error;
	}
	*timestamp = (libcdatetime_timestamp_t *) internal_timestamp;

	return( 1 );

on_error:
	if( internal_timestamp != NULL )
	{
		memory_free(
		 internal_timestamp );
	}
	return( -1 );
}

/* Frees a timestamp
 * Returns 1 if successful or -1 on error
 */
int libcdatetime_timestamp_free(
     libcdatetime_timestamp_t **timestamp,
     libcerror_error_t **error )
{
	libcdatetime_internal_timestamp_t *internal_timestamp = NULL;
	static char *function                                 = "libcdatetime_timestamp_free";

	if( timestamp == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid timestamp.",
		 function );

		return( -1 );
	}
	if( *timestamp != NULL )
	{
		internal_timestamp = (libcdatetime_internal_timestamp_t *) *timestamp;
		*timestamp         = NULL;

		memory_free(
		 internal_timestamp );
	}
	return( 1 );
}

/* Copies the timestamp
 * Returns 1 if successful or -1 on error
 */
int libcdatetime_timestamp_copy(
     libcdatetime_timestamp_t *destination_timestamp,
     const libcdatetime_timestamp_t *source_timestamp,
     libcerror_error_t **error )
{
	static char *function = "libcdatetime_timestamp_copy";

	if( destination_timestamp == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid destination timestamp.",
		 function );

		return( -1 );
	}
	if( source_timestamp == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source timestamp.",
		 function );

		return( -1 );
	}
	if( memory_copy(
	     destination_timestamp,
	     source_timestamp,
	     sizeof( libcdatetime_internal_timestamp_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy timestamp.",
		 function );

		return( -1 );
	}
	return( 1 );
}

#if defined( WINAPI ) && ( WINVER >= 0x0500 )

/* Sets the timestamp to the current (system) date and time in UTC
 * This function uses the WINAPI function for Windows 2000 or later
 * Returns 1 if successful or -1 on error
 */
int libcdatetime_timestamp_set_current_time(
     libcdatetime_timestamp_t *timestamp,
     libcerror_error_t **error )
{
	SYSTEMTIME systemtime;

	libcdatetime_internal_timestamp_t *internal_timestamp = NULL;
	static char *function                                 = "libcdatetime_timestamp_set_current_time";

	if( timestamp == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid timestamp.",
		 function );

		return( -1 );
	}
	internal_timestamp = (libcdatetime_internal_timestamp_t *) timestamp;

	if( memory_set(
	     &systemtime,
	     0,
	     sizeof( SYSTEMTIME ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear systemtime.",
		 function );

		return( -1 );
	}
	GetSystemTime(
	 &systemtime );

	if( SystemTimeToFileTime(
	     &systemtime,
	     &( internal_timestamp->filetime ) ) != 0 )
	{
		libcerror_system_set_error(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 errno,
		 "%s: unable to retrieve filetime.",
		 function );

		return( -1 );
	}
	return( 1 );
}

#elif defined( WINAPI )

/* TODO */
#error WINAPI get current time function for Windows NT4 or earlier NOT implemented yet

#elif defined( HAVE_TIME )

/* Sets the timestamp to the current (system) date and time in UTC
 * This function uses the POSIX time function or equivalent
 * Returns 1 if successful or -1 on error
 */
int libcdatetime_timestamp_set_current_time(
     libcdatetime_timestamp_t *timestamp,
     libcerror_error_t **error )
{
	libcdatetime_internal_timestamp_t *internal_timestamp = NULL;
	static char *function                                 = "libcdatetime_timestamp_set_current_time";

	if( timestamp == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid timestamp.",
		 function );

		return( -1 );
	}
	internal_timestamp = (libcdatetime_internal_timestamp_t *) timestamp;

	if( time(
	     &( internal_timestamp->time ) ) == (time_t) -1 )
	{
		libcerror_system_set_error(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 errno,
		 "%s: unable to set current time.",
		 function );

		return( -1 );
	}
	return( 1 );
}

#else
#error Missing get current time function
#endif

#if defined( WINAPI ) && ( WINVER >= 0x0500 )

/* Determines the delta in seconds between the first and second timestamp
 * This function uses the WINAPI function for Windows 2000 or later
 * The number_of_seconds value with be negative if the first timestamp
 * pre-dates the second timestamp
 * Returns 1 if successful or -1 on error
 */
int libcdatetime_timestamp_get_delta_in_seconds(
     libcdatetime_timestamp_t *first_timestamp,
     libcdatetime_timestamp_t *second_timestamp,
     int64_t *number_of_seconds,
     libcerror_error_t **error )
{
	libcdatetime_internal_timestamp_t *internal_first_timestamp  = NULL;
	libcdatetime_internal_timestamp_t *internal_second_timestamp = NULL;
	static char *function                                        = "libcdatetime_timestamp_get_delta_in_seconds";
	int64_t time_delta                                           = 0;

	if( first_timestamp == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid first timestamp.",
		 function );

		return( -1 );
	}
	internal_first_timestamp = (libcdatetime_internal_timestamp_t *) first_timestamp;

	if( second_timestamp == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid second timestamp.",
		 function );

		return( -1 );
	}
	internal_second_timestamp = (libcdatetime_internal_timestamp_t *) second_timestamp;

	if( number_of_seconds == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid number of seconds.",
		 function );

		return( -1 );
	}
	time_delta = (int64_t) internal_first_timestamp->filetime.dwHighDateTime - (int64_t) internal_second_timestamp->filetime.dwHighDateTime;

	if( time_delta < 0 )
	{
		if( (uint64_t) -time_delta > (uint64_t) INT32_MAX )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid time delta value out of bounds.",
			 function );

			return( -1 );
		}
	}
	else
	{
		if( (uint64_t) time_delta > (uint64_t) INT64_MAX )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid time delta value out of bounds.",
			 function );

			return( -1 );
		}
	}
	time_delta <<= 32;

	time_delta += (int64_t) internal_first_timestamp->filetime.dwLowDateTime - (int64_t) internal_second_timestamp->filetime.dwLowDateTime;

	if( time_delta < 0 )
	{
		if( (uint64_t) -time_delta > (uint64_t) INT64_MAX )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid time delta value out of bounds.",
			 function );

			return( -1 );
		}
	}
	else
	{
		if( (uint64_t) time_delta > (uint64_t) INT64_MAX )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid time delta value out of bounds.",
			 function );

			return( -1 );
		}
	}
	*number_of_seconds = (int64_t) time_delta;

	return( 1 );
}


#elif defined( WINAPI )

/* TODO */
#error WINAPI timestamp type for Windows NT4 or earlier NOT implemented yet

#else

/* Determines the delta in seconds between the first and second timestamp
 * The number_of_seconds value with be negative if the first timestamp
 * pre-dates the second timestamp
 * Returns 1 if successful or -1 on error
 */
int libcdatetime_timestamp_get_delta_in_seconds(
     libcdatetime_timestamp_t *first_timestamp,
     libcdatetime_timestamp_t *second_timestamp,
     int64_t *number_of_seconds,
     libcerror_error_t **error )
{
	libcdatetime_internal_timestamp_t *internal_first_timestamp  = NULL;
	libcdatetime_internal_timestamp_t *internal_second_timestamp = NULL;
	static char *function                                        = "libcdatetime_timestamp_set_current_time";
	time_t time_delta                                            = 0;

	if( first_timestamp == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid first timestamp.",
		 function );

		return( -1 );
	}
	internal_first_timestamp = (libcdatetime_internal_timestamp_t *) first_timestamp;

	if( second_timestamp == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid second timestamp.",
		 function );

		return( -1 );
	}
	internal_second_timestamp = (libcdatetime_internal_timestamp_t *) second_timestamp;

	if( number_of_seconds == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid number of seconds.",
		 function );

		return( -1 );
	}
	time_delta = internal_first_timestamp->time - internal_second_timestamp->time;

	if( time_delta < 0 )
	{
		if( (uint64_t) -time_delta > (uint64_t) INT64_MAX )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid time delta value out of bounds.",
			 function );

			return( -1 );
		}
	}
	else
	{
		if( (uint64_t) time_delta > (uint64_t) INT64_MAX )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid time delta value out of bounds.",
			 function );

			return( -1 );
		}
	}
	*number_of_seconds = (int64_t) time_delta;

	return( 1 );
}

#endif

/* Deterimes the size of the string for the timestamp
 * The string size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libcdatetime_timestamp_get_string_size(
     libcdatetime_timestamp_t *timestamp,
     size_t *string_size,
     uint32_t string_format_flags,
     libcerror_error_t **error )
{
	static char *function       = "libcdatetime_timestamp_get_string_size";
	uint32_t string_format_type = 0;
	uint32_t supported_flags    = 0;

	if( timestamp == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid date time values.",
		 function );

		return( -1 );
	}
	if( string_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string size.",
		 function );

		return( -1 );
	}
	supported_flags = 0x000000ffUL
	                | LIBCDATETIME_STRING_FORMAT_FLAG_DATE
	                | LIBCDATETIME_STRING_FORMAT_FLAG_TIME
	                | LIBCDATETIME_STRING_FORMAT_FLAG_DURATION
	                | LIBCDATETIME_STRING_FORMAT_FLAG_TIME_MILLI_SECONDS
	                | LIBCDATETIME_STRING_FORMAT_FLAG_TIME_MICRO_SECONDS
	                | LIBCDATETIME_STRING_FORMAT_FLAG_TIME_NANO_SECONDS
	                | LIBCDATETIME_STRING_FORMAT_FLAG_TIMEZONE_INDICATOR;

	if( ( string_format_flags & supported_flags ) == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported string format flags: 0x%08" PRIx32 ".",
		 function,
		 string_format_flags );

		return( -1 );
	}
	string_format_type = string_format_flags & 0x000000ffUL;

	if( ( string_format_type != LIBCDATETIME_STRING_FORMAT_TYPE_CTIME )
	 && ( string_format_type != LIBCDATETIME_STRING_FORMAT_TYPE_ISO8601 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported string format type: 0x%08" PRIx32 ".",
		 function,
		 string_format_type );

		return( -1 );
	}
	/* End of string character
	 */
	*string_size = 1;

	/* Determine the size of the date and time string
	 */
	if( ( string_format_flags & LIBCDATETIME_STRING_FORMAT_FLAG_DATE ) != 0 )
	{
		/* Example: Jan 01, 1970
		 */
		if( string_format_type == LIBCDATETIME_STRING_FORMAT_TYPE_CTIME )
		{
			*string_size += 12;
		}
		/* Example: 1970-01-01
		 */
		else if( string_format_type == LIBCDATETIME_STRING_FORMAT_TYPE_ISO8601 )
		{
			*string_size += 10;
		}
	}
	if( ( string_format_flags & LIBCDATETIME_STRING_FORMAT_FLAG_TIME ) != 0 )
	{
		/* Date and time separator
		 */
		if( ( string_format_flags & LIBCDATETIME_STRING_FORMAT_FLAG_DATE ) != 0 )
		{
			*string_size += 1;
		}
		/* Example: 00:00:00
		 */
		*string_size += 8;

		/* Example: .000
		 */
		if( ( ( string_format_flags & LIBCDATETIME_STRING_FORMAT_FLAG_TIME_MILLI_SECONDS ) != 0 )
		 || ( ( string_format_flags & LIBCDATETIME_STRING_FORMAT_FLAG_TIME_MICRO_SECONDS ) != 0 )
		 || ( ( string_format_flags & LIBCDATETIME_STRING_FORMAT_FLAG_TIME_NANO_SECONDS ) != 0 ) )
		{
			*string_size += 4;
		}
		/* Example: .000000
		 */
		if( ( ( string_format_flags & LIBCDATETIME_STRING_FORMAT_FLAG_TIME_MICRO_SECONDS ) != 0 )
		 || ( ( string_format_flags & LIBCDATETIME_STRING_FORMAT_FLAG_TIME_NANO_SECONDS ) != 0 ) )
		{
			*string_size += 3;
		}
		/* Example: .000000000
		 */
		if( ( string_format_flags & LIBCDATETIME_STRING_FORMAT_FLAG_TIME_NANO_SECONDS ) != 0 )
		{
			*string_size += 3;
		}
	}
	if( ( string_format_flags & LIBCDATETIME_STRING_FORMAT_FLAG_TIMEZONE_INDICATOR ) != 0 )
	{
		/* Example: UTC
		 */
		if( string_format_type == LIBCDATETIME_STRING_FORMAT_TYPE_CTIME )
		{
			*string_size += 4;
		}
		/* Example: Z
		 */
		else if( string_format_type == LIBCDATETIME_STRING_FORMAT_TYPE_ISO8601 )
		{
			*string_size += 1;
		}
	}
	return( 1 );
}

/* Converts the timestamp into a string
 * The string size should include the end of string character
 * Returns 1 if successful, 0 if the timestamp is not a valid or -1 on error
 */
int libcdatetime_timestamp_copy_to_string(
     libcdatetime_timestamp_t *timestamp,
     uint8_t *string,
     size_t string_size,
     uint32_t string_format_flags,
     libcerror_error_t **error )
{
	static char *function = "libcdatetime_timestamp_copy_to_string";
	size_t string_index   = 0;

	if( libcdatetime_timestamp_copy_to_string_with_index(
	     timestamp,
	     string,
	     string_size,
	     &string_index,
	     string_format_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy timestamp to string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Converts the timestamp into a string
 * The string size should include the end of string character
 * Returns 1 if successful, 0 if the timestamp is not a valid or -1 on error
 */
int libcdatetime_timestamp_copy_to_string_with_index(
     libcdatetime_timestamp_t *timestamp,
     uint8_t *string,
     size_t string_size,
     size_t *string_index,
     uint32_t string_format_flags,
     libcerror_error_t **error )
{
	libcdatetime_elements_t *time_elements                = NULL;
	libcdatetime_internal_timestamp_t *internal_timestamp = NULL;
	static char *function                                 = "libcdatetime_timestamp_copy_to_string_with_index";

	if( timestamp == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid date time values.",
		 function );

		return( -1 );
	}
	internal_timestamp = (libcdatetime_internal_timestamp_t *) timestamp;

	if( libcdatetime_elements_initialize(
	     &time_elements,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create time elements.",
		 function );

		goto on_error;
	}
/* TODO convert timestamp into elements */

#if defined( WINAPI ) && ( WINVER < 0x0500 )
/* TODO */
#error WINAPI support for Windows NT4 or earlier NOT implemented yet
#endif

/* TODO move this function into time elements ? */
#if defined( WINAPI )
	if( libcdatetime_internal_elements_set_from_filetime_utc(
	     (libcdatetime_internal_elements_t *) time_elements,
	     &( internal_timestamp->filetime ),
	     error ) != 1 )
#else
	if( libcdatetime_internal_elements_set_from_time_utc(
	     (libcdatetime_internal_elements_t *) time_elements,
	     &( internal_timestamp->time ),
	     error ) != 1 )
#endif
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set time elements from timestamp.",
		 function );

		goto on_error;
	}
	if( libcdatetime_elements_copy_to_string_with_index(
	     time_elements,
	     string,
	     string_size,
	     string_index,
	     string_format_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy time elements to string.",
		 function );

		goto on_error;
	}
	if( libcdatetime_elements_free(
	     &time_elements,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free time elements.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( time_elements != NULL )
	{
		libcdatetime_elements_free(
		 &time_elements,
		 error );
	}
	return( -1 );
}

