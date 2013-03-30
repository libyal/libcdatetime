/*
 * Date and time elements functions
 *
 * Copyright (c) 2006-2013, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( WINAPI ) || defined( USE_CRT_FUNCTIONS )
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
#include "libcdatetime_types.h"

/* Initialize the date and time elements
 * Returns 1 if successful or -1 on error
 */
int libcdatetime_elements_initialize(
     libcdatetime_elements_t **elements,
     libcerror_error_t **error )
{
	libcdatetime_internal_elements_t *internal_elements = NULL;
	static char *function                               = "libcdatetime_elements_initialize";

	if( elements == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid elements.",
		 function );

		return( -1 );
	}
	if( *elements != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid elements value already set.",
		 function );

		return( -1 );
	}
	internal_elements = memory_allocate_structure(
	                     libcdatetime_internal_elements_t );

	if( internal_elements == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create elements.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_elements,
	     0,
	     sizeof( libcdatetime_internal_elements_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear elements.",
		 function );

		goto on_error;
	}
	*elements = (libcdatetime_elements_t *) internal_elements;

	return( 1 );

on_error:
	if( internal_elements != NULL )
	{
		memory_free(
		 internal_elements );
	}
	return( -1 );
}

/* Frees the date and time elements
 * Returns 1 if successful or -1 on error
 */
int libcdatetime_elements_free(
     libcdatetime_elements_t **elements,
     libcerror_error_t **error )
{
	libcdatetime_internal_elements_t *internal_elements = NULL;
	static char *function                               = "libcdatetime_elements_free";

	if( elements == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid elements.",
		 function );

		return( -1 );
	}
	if( *elements != NULL )
	{
		internal_elements = (libcdatetime_internal_elements_t *) *elements;
		*elements         = NULL;

		memory_free(
		 internal_elements );
	}
	return( 1 );
}

#if defined( WINAPI ) && ( WINVER >= 0x0500 ) && !defined( USE_CRT_FUNCTIONS )

/* Sets the date and time elements to the current (system) date and time in UTC
 * This function uses the WINAPI function for Windows 2000 or later
 * Returns 1 if successful or -1 on error
 */
int libcdatetime_elements_set_current_time_utc(
     libcdatetime_elements_t *elements,
     libcerror_error_t **error )
{
	libcdatetime_internal_elements_t *internal_elements = NULL;
	static char *function                               = "libcdatetime_elements_set_current_time_utc";

	if( elements == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid elements.",
		 function );

		return( -1 );
	}
	internal_elements = (libcdatetime_internal_elements_t *) elements;

	GetSystemTime(
	 internal_elements->systemtime );

	return( 1 );
}

#elif defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )

/* TODO */
#error WINAPI get current time function for Windows NT4 or earlier NOT implemented yet

#elif ( defined( HAVE_TIME ) && ( defined( HAVE_GMTIME ) || defined( HAVE_GMTIME_R ) ) ) || defined( WINAPI )

/* Sets the date and time elements to the current (system) date and time in UTC
 * This function uses the POSIX time function or equivalent
 * Returns 1 if successful or -1 on error
 */
int libcdatetime_elements_set_current_time_utc(
     libcdatetime_elements_t *elements,
     libcerror_error_t **error )
{
	libcdatetime_internal_elements_t *internal_elements = NULL;
	static char *function                               = "libcdatetime_elements_set_current_time_utc";
	time_t timestamp                                    = 0;

#if !defined( HAVE_GMTIME_R ) && !defined( _MSC_VER )
	struct tm *static_tm                                = NULL;
#endif

	if( elements == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid elements.",
		 function );

		return( -1 );
	}
	internal_elements = (libcdatetime_internal_elements_t *) elements;

	timestamp = time(
	             NULL );

	if( timestamp == (time_t) -1 )
	{
		libcerror_system_set_error(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 errno,
		 "%s: unable to get current timestamp.",
		 function );

		return( -1 );
	}
#if defined( _MSC_VER )
	if( gmtime_s(
	     time_elements,
	     timestamp ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set time elements.",
		 function );

		return( -1 );
	}

#elif defined( HAVE_GMTIME_R )
	if( gmtime_r(
	     timestamp,
	     time_elements ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set time elements.",
		 function );

		return( -1 );
	}

#else
	static_time_elements = gmtime(
	                        timestamp );

	if( static_time_elements == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to create static time elements.",
		 function );

		return( -1 );
	}
	if( memory_copy(
	     time_elements,
	     static_time_elements,
	     sizeof( struct tm ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set time elements.",
		 function );

		return( -1 );
	}
#endif

	return( 1 );
}

#else
#error Missing get current time function
#endif

#if defined( WINAPI ) && ( WINVER >= 0x0500 ) && !defined( USE_CRT_FUNCTIONS )

/* Determines the delta in seconds between the first and second date and time elements
 * This function uses the WINAPI function for Windows 2000 or later
 * The number_of_seconds value with be negative if the first date and time
 * pre-dates the second date and time
 * Returns 1 if successful or -1 on error
 */
int libcdatetime_elements_get_delta_in_seconds(
     libcdatetime_elements_t *first_elements,
     libcdatetime_elements_t *second_elements,
     int64_t *number_of_seconds,
     libcerror_error_t **error )
{
/* TODO */
#error WINAPI libcdatetime_elements_get_delta_in_seconds function for Windows 2000 or later NOT implemented yet
}

#elif defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )

/* TODO */
#error WINAPI date and time elements type for Windows NT4 or earlier NOT implemented yet

#else

/* Determines the delta in seconds between the first and second date and time elements
 * The number_of_seconds value with be negative if the first date and time
 * pre-dates the second date and time
 * Returns 1 if successful or -1 on error
 */
int libcdatetime_elements_get_delta_in_seconds(
     libcdatetime_elements_t *first_elements,
     libcdatetime_elements_t *second_elements,
     int64_t *number_of_seconds,
     libcerror_error_t **error )
{
	libcdatetime_internal_elements_t *internal_first_elements  = NULL;
	libcdatetime_internal_elements_t *internal_second_elements = NULL;
	static char *function                                      = "libcdatetime_elements_get_delta_in_seconds";
	time_t time_delta                                          = 0;

	if( first_elements == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid first elements.",
		 function );

		return( -1 );
	}
	internal_first_elements = (libcdatetime_internal_elements_t *) first_elements;

	if( second_elements == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid second elements.",
		 function );

		return( -1 );
	}
	internal_second_elements = (libcdatetime_internal_elements_t *) second_elements;

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
	time_delta = internal_first_elements->time - internal_second_elements->time;

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

/* Deterimes the size of the string for the date and time elements
 * The string size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libcdatetime_elements_get_string_size(
     libcdatetime_elements_t *elements,
     size_t *string_size,
     uint32_t string_format_flags,
     libcerror_error_t **error )
{
	static char *function       = "libcdatetime_elements_get_string_size";
	uint32_t string_format_type = 0;
	uint32_t supported_flags    = 0;

	if( elements == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid elements.",
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

/* Converts the date and time elements into a string
 * The string size should include the end of string character
 * Returns 1 if successful, 0 if the elements are not a valid or -1 on error
 */
int libcdatetime_elements_copy_to_string_with_index(
     libcdatetime_elements_t *elements,
     uint8_t *string,
     size_t string_size,
     size_t *string_index,
     uint32_t string_format_flags,
     libcerror_error_t **error )
{
	libcdatetime_internal_elements_t *internal_elements = NULL;
	char *month_string                                  = NULL;
	static char *function                               = "libcdatetime_elements_copy_to_string_with_index";
	size_t internal_string_index                        = 0;
	uint32_t string_format_type                         = 0;
	uint32_t supported_flags                            = 0;
	uint16_t micro_seconds                              = 0;
	uint16_t milli_seconds                              = 0;
	uint16_t nano_seconds                               = 0;
	uint16_t year_value                                 = 0;
	uint8_t days_in_month                               = 0;

	if( elements == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid date time values.",
		 function );

		return( -1 );
	}
	internal_elements = (libcdatetime_internal_elements_t *) elements;

	if( string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string.",
		 function );

		return( -1 );
	}
	if( string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( string_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string index.",
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
	internal_string_index = *string_index;

	/* Validate the date and time if necessary
	 */
	if( ( string_format_flags & LIBCDATETIME_STRING_FORMAT_FLAG_DATE ) != 0 )
	{
		if( date_time_values->year > 9999 )
		{
			return( 0 );
		}
		if( ( date_time_values->month == 0 )
		 || ( date_time_values->month > 12 ) )
		{
			return( 0 );
		}
		switch( date_time_values->month )
		{
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
				days_in_month = 31;
				break;
			case 4:
			case 6:
			case 9:
			case 11:
				days_in_month = 30;
				break;
			case 2:
				if( ( ( ( date_time_values->year % 4 ) == 0 )
				  &&  ( ( date_time_values->year % 100 ) != 0 ) )
				 || ( ( date_time_values->year % 400 ) == 0 ) )
				{
					days_in_month = 29;
				}
				else
				{
					days_in_month = 28;
				}
				break;
		}
		if( ( date_time_values->day == 0 )
		 || ( date_time_values->day > days_in_month ) )
		{
			return( 0 );
		}
	}
	if( ( string_format_flags & LIBCDATETIME_STRING_FORMAT_FLAG_TIME ) != 0 )
	{
		if( date_time_values->hours > 23 )
		{
			return( 0 );
		}
		if( date_time_values->minutes > 59 )
		{
			return( 0 );
		}
		if( date_time_values->seconds > 59 )
		{
			return( 0 );
		}
		if( ( ( string_format_flags & LIBCDATETIME_STRING_FORMAT_FLAG_TIME_MILLI_SECONDS ) != 0 )
		 || ( ( string_format_flags & LIBCDATETIME_STRING_FORMAT_FLAG_TIME_MICRO_SECONDS ) != 0 )
		 || ( ( string_format_flags & LIBCDATETIME_STRING_FORMAT_FLAG_TIME_NANO_SECONDS ) != 0 ) )
		{
			if( date_time_values->milli_seconds > 999 )
			{
				return( 0 );
			}
		}
		if( ( ( string_format_flags & LIBCDATETIME_STRING_FORMAT_FLAG_TIME_MICRO_SECONDS ) != 0 )
		 || ( ( string_format_flags & LIBCDATETIME_STRING_FORMAT_FLAG_TIME_NANO_SECONDS ) != 0 ) )
		{
			if( date_time_values->micro_seconds > 999 )
			{
				return( 0 );
			}
		}
		if( ( string_format_flags & LIBCDATETIME_STRING_FORMAT_FLAG_TIME_NANO_SECONDS ) != 0 )
		{
			if( date_time_values->nano_seconds > 999 )
			{
				return( 0 );
			}
		}
	}
	/* Create the date and time string
	 */
	if( ( string_format_flags & LIBCDATETIME_STRING_FORMAT_FLAG_DATE ) != 0 )
	{
		if( string_format_type == LIBCDATETIME_STRING_FORMAT_TYPE_CTIME )
		{
			switch( date_time_values->month )
			{
				case 1:
					month_string = "Jan";
					break;
				case 2:
					month_string = "Feb";
					break;
				case 3:
					month_string = "Mar";
					break;
				case 4:
					month_string = "Apr";
					break;
				case 5:
					month_string = "May";
					break;
				case 6:
					month_string = "Jun";
					break;
				case 7:
					month_string = "Jul";
					break;
				case 8:
					month_string = "Aug";
					break;
				case 9:
					month_string = "Sep";
					break;
				case 10:
					month_string = "Oct";
					break;
				case 11:
					month_string = "Nov";
					break;
				case 12:
					month_string = "Dec";
					break;
			}
			if( ( internal_string_index + 12 ) > string_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: string is too small.",
				 function );

				return( -1 );
			}
			/* Format: mmm dd, yyyy */
			string[ internal_string_index++ ] = month_string[ 0 ];
			string[ internal_string_index++ ] = month_string[ 1 ];
			string[ internal_string_index++ ] = month_string[ 2 ];

			string[ internal_string_index++ ] = ' ';

			string[ internal_string_index++ ] = '0' + (char) ( date_time_values->day / 10 );
			string[ internal_string_index++ ] = '0' + (char) ( date_time_values->day % 10 );

			string[ internal_string_index++ ] = ',';
			string[ internal_string_index++ ] = ' ';

			year_value                        = date_time_values->year;
			string[ internal_string_index++ ] = '0' + (char) ( year_value / 1000 );
			year_value                       %= 1000;
			string[ internal_string_index++ ] = '0' + (char) ( year_value / 100 );
			year_value                       %= 100;
			string[ internal_string_index++ ] = '0' + (char) ( year_value / 10 );
			year_value                       %= 10;
			string[ internal_string_index++ ] = '0' + (char) year_value;

			if( ( string_format_flags & LIBCDATETIME_STRING_FORMAT_FLAG_TIME ) != 0 )
			{
				if( ( internal_string_index + 1 ) > string_size )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: string is too small.",
					 function );

					return( -1 );
				}
				string[ internal_string_index++ ] = ' ';
			}
		}
		else if( string_format_type == LIBCDATETIME_STRING_FORMAT_TYPE_ISO8601 )
		{
			if( ( internal_string_index + 10 ) > string_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: string is too small.",
				 function );

				return( -1 );
			}
			/* Format: yyyy-mm-dd */
			year_value                        = date_time_values->year;
			string[ internal_string_index++ ] = '0' + (char) ( year_value / 1000 );
			year_value                       %= 1000;
			string[ internal_string_index++ ] = '0' + (char) ( year_value / 100 );
			year_value                       %= 100;
			string[ internal_string_index++ ] = '0' + (char) ( year_value / 10 );
			year_value                       %= 10;
			string[ internal_string_index++ ] = '0' + (char) year_value;

			string[ internal_string_index++ ] = '-';

			string[ internal_string_index++ ] = '0' + (char) ( date_time_values->month / 10 );
			string[ internal_string_index++ ] = '0' + (char) ( date_time_values->month % 10 );

			string[ internal_string_index++ ] = '-';

			string[ internal_string_index++ ] = '0' + (char) ( date_time_values->day / 10 );
			string[ internal_string_index++ ] = '0' + (char) ( date_time_values->day % 10 );

			if( ( string_format_flags & LIBCDATETIME_STRING_FORMAT_FLAG_TIME ) != 0 )
			{
				if( ( internal_string_index + 1 ) > string_size )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: string is too small.",
					 function );

					return( -1 );
				}
				string[ internal_string_index++ ] = (uint8_t) 'T';
			}
		}
	}
	if( ( string_format_flags & LIBCDATETIME_STRING_FORMAT_FLAG_TIME ) != 0 )
	{
		if( ( internal_string_index + 8 ) > string_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: string is too small.",
			 function );

			return( -1 );
		}
		/* Format: HH:MM:SS */
		string[ internal_string_index++ ] = '0' + (char) ( date_time_values->hours / 10 );
		string[ internal_string_index++ ] = '0' + (char) ( date_time_values->hours % 10 );

		string[ internal_string_index++ ] = ':';

		string[ internal_string_index++ ] = '0' + (char) ( date_time_values->minutes / 10 );
		string[ internal_string_index++ ] = '0' + (char) ( date_time_values->minutes % 10 );

		string[ internal_string_index++ ] = ':';

		string[ internal_string_index++ ] = '0' + (char) ( date_time_values->seconds / 10 );
		string[ internal_string_index++ ] = '0' + (char) ( date_time_values->seconds % 10 );

		if( ( ( string_format_flags & LIBCDATETIME_STRING_FORMAT_FLAG_TIME_MILLI_SECONDS ) != 0 )
		 || ( ( string_format_flags & LIBCDATETIME_STRING_FORMAT_FLAG_TIME_MICRO_SECONDS ) != 0 )
		 || ( ( string_format_flags & LIBCDATETIME_STRING_FORMAT_FLAG_TIME_NANO_SECONDS ) != 0 ) )
		{
			if( ( internal_string_index + 4 ) > string_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: string is too small.",
				 function );

				return( -1 );
			}
			/* Format: .### */
			string[ internal_string_index++ ] = '.';

			milli_seconds = date_time_values->milli_seconds;

			string[ internal_string_index + 2 ] = '0' + (char) ( milli_seconds % 10 );
			milli_seconds                      /= 10;

			string[ internal_string_index + 1 ] = '0' + (char) ( milli_seconds % 10 );
			milli_seconds                      /= 10;

			string[ internal_string_index ] = '0' + (char) ( milli_seconds % 10 );
			milli_seconds                  /= 10;

			internal_string_index += 3;
		}
		if( ( ( string_format_flags & LIBCDATETIME_STRING_FORMAT_FLAG_TIME_MICRO_SECONDS ) != 0 )
		 || ( ( string_format_flags & LIBCDATETIME_STRING_FORMAT_FLAG_TIME_NANO_SECONDS ) != 0 ) )
		{
			if( ( internal_string_index + 3 ) > string_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: string is too small.",
				 function );

				return( -1 );
			}
			/* Format: ### */
			micro_seconds = date_time_values->micro_seconds;

			string[ internal_string_index + 2 ] = '0' + (char) ( micro_seconds % 10 );
			micro_seconds                      /= 10;

			string[ internal_string_index + 1 ] = '0' + (char) ( micro_seconds % 10 );
			micro_seconds                      /= 10;

			string[ internal_string_index ] = '0' + (char) ( micro_seconds % 10 );
			micro_seconds                  /= 10;

			internal_string_index += 3;
		}
		if( ( string_format_flags & LIBCDATETIME_STRING_FORMAT_FLAG_TIME_NANO_SECONDS ) != 0 )
		{
			if( ( internal_string_index + 3 ) > string_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: string is too small.",
				 function );

				return( -1 );
			}
			/* Format: ### */
			nano_seconds = date_time_values->nano_seconds;

			string[ internal_string_index + 2 ] = '0' + (char) ( nano_seconds % 10 );
			nano_seconds                       /= 10;

			string[ internal_string_index + 1 ] = '0' + (char) ( nano_seconds % 10 );
			nano_seconds                       /= 10;

			string[ internal_string_index ] = '0' + (char) ( nano_seconds % 10 );
			nano_seconds                   /= 10;

			internal_string_index += 3;
		}
	}
	if( ( string_format_flags & LIBCDATETIME_STRING_FORMAT_FLAG_TIMEZONE_INDICATOR ) != 0 )
	{
		if( string_format_type == LIBCDATETIME_STRING_FORMAT_TYPE_CTIME )
		{
			if( ( internal_string_index + 4 ) > string_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: string is too small.",
				 function );

				return( -1 );
			}
			string[ internal_string_index++ ] = ' ';
			string[ internal_string_index++ ] = 'U';
			string[ internal_string_index++ ] = 'T';
			string[ internal_string_index++ ] = 'C';
		}
		else if( string_format_type == LIBCDATETIME_STRING_FORMAT_TYPE_ISO8601 )
		{
			if( ( internal_string_index + 1 ) > string_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
				 "%s: string is too small.",
				 function );

				return( -1 );
			}
			string[ internal_string_index++ ] = 'Z';
		}
	}
	if( ( internal_string_index + 1 ) > string_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: string is too small.",
		 function );

		return( -1 );
	}
	string[ internal_string_index++ ] = 0;

	*string_index = internal_string_index;

	return( 1 );
}

