/*
 * Timestamp functions
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
#include "libcdatetime_libcerror.h"
#include "libcdatetime_timestamp.h"
#include "libcdatetime_types.h"

/* Initialize the timestamp
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

#if defined( WINAPI ) && ( WINVER >= 0x0500 ) && !defined( USE_CRT_FUNCTIONS )

/* Sets the timestamp to the current (system) date and time in UTC
 * This function uses the WINAPI function for Windows 2000 or later
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

	GetSystemTime(
	 internal_timestamp->systemtime );

	return( 1 );
}

#elif defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )

/* TODO */
#error WINAPI get current time function for Windows NT4 or earlier NOT implemented yet

#elif defined( HAVE_TIME ) || defined( WINAPI )

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
	time_t result                                         = 0;

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

	result = time(
	 &( internal_timestamp->time ) );

	if( result == (time_t) -1 )
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

#if defined( WINAPI ) && ( WINVER >= 0x0500 ) && !defined( USE_CRT_FUNCTIONS )

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
/* TODO */
#error WINAPI libcdatetime_timestamp_get_delta_in_seconds function for Windows 2000 or later NOT implemented yet
}

#elif defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )

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
int libcdatetime_timestamp_copy_to_string_with_index(
     libcdatetime_timestamp_t *timestamp,
     uint8_t *string,
     size_t string_size,
     size_t *string_index,
     uint32_t string_format_flags,
     libcerror_error_t **error )
{
	libcdatetime_internal_timestamp_t *internal_timestamp = NULL;
	char *month_string                                    = NULL;
	static char *function                                 = "libcdatetime_timestamp_copy_to_string_with_index";
	size_t internal_string_index                          = 0;
	uint32_t string_format_type                           = 0;
	uint32_t supported_flags                              = 0;
	uint16_t micro_seconds                                = 0;
	uint16_t milli_seconds                                = 0;
	uint16_t nano_seconds                                 = 0;
	uint16_t year                                         = 0;
	uint8_t day_of_month                                  = 0;
	uint8_t days_in_month                                 = 0;
	uint8_t hours                                         = 0;
	uint8_t minutes                                       = 0;
	uint8_t seconds                                       = 0;

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

/* TODO */
	year          = (uint16_t) date_time_values->year;
	month         = (uint8_t) date_time_values->month;
	day_of_month  = (uint8_t) date_time_values->day;
	hours         = (uint8_t) date_time_values->hours;
	minutes       = (uint8_t) date_time_values->minutes;
	seconds       = (uint8_t) date_time_values->seconds;
	milli_seconds = (uint16_t) date_time_values->milli_seconds;
	micro_seconds = (uint16_t) date_time_values->micro_seconds;
	nano_seconds  = (uint16_t) date_time_values->nano_seconds;

	/* Validate the date and time if necessary
	 */
	if( ( string_format_flags & LIBCDATETIME_STRING_FORMAT_FLAG_DATE ) != 0 )
	{
		if( year > 9999 )
		{
			return( 0 );
		}
		if( ( month == 0 )
		 || ( month > 12 ) )
		{
			return( 0 );
		}
		switch( month )
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
				if( ( ( ( year % 4 ) == 0 )
				  &&  ( ( year % 100 ) != 0 ) )
				 || ( ( year % 400 ) == 0 ) )
				{
					days_in_month = 29;
				}
				else
				{
					days_in_month = 28;
				}
				break;
		}
		if( ( day_of_month == 0 )
		 || ( day_of_month > days_in_month ) )
		{
			return( 0 );
		}
	}
	if( ( string_format_flags & LIBCDATETIME_STRING_FORMAT_FLAG_TIME ) != 0 )
	{
		if( hours > 23 )
		{
			return( 0 );
		}
		if( minutes > 59 )
		{
			return( 0 );
		}
		if( seconds > 59 )
		{
			return( 0 );
		}
		if( ( ( string_format_flags & LIBCDATETIME_STRING_FORMAT_FLAG_TIME_MILLI_SECONDS ) != 0 )
		 || ( ( string_format_flags & LIBCDATETIME_STRING_FORMAT_FLAG_TIME_MICRO_SECONDS ) != 0 )
		 || ( ( string_format_flags & LIBCDATETIME_STRING_FORMAT_FLAG_TIME_NANO_SECONDS ) != 0 ) )
		{
			if( milli_seconds > 999 )
			{
				return( 0 );
			}
		}
		if( ( ( string_format_flags & LIBCDATETIME_STRING_FORMAT_FLAG_TIME_MICRO_SECONDS ) != 0 )
		 || ( ( string_format_flags & LIBCDATETIME_STRING_FORMAT_FLAG_TIME_NANO_SECONDS ) != 0 ) )
		{
			if( micro_seconds > 999 )
			{
				return( 0 );
			}
		}
		if( ( string_format_flags & LIBCDATETIME_STRING_FORMAT_FLAG_TIME_NANO_SECONDS ) != 0 )
		{
			if( nano_seconds > 999 )
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
			switch( month )
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

			string[ internal_string_index++ ] = '0' + (char) ( day_of_month / 10 );
			string[ internal_string_index++ ] = '0' + (char) ( day_of_month % 10 );

			string[ internal_string_index++ ] = ',';
			string[ internal_string_index++ ] = ' ';

			string[ internal_string_index++ ] = '0' + (char) ( year / 1000 );
			year                             %= 1000;
			string[ internal_string_index++ ] = '0' + (char) ( year / 100 );
			year                             %= 100;
			string[ internal_string_index++ ] = '0' + (char) ( year / 10 );
			year                             %= 10;
			string[ internal_string_index++ ] = '0' + (char) year;

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
			string[ internal_string_index++ ] = '0' + (char) ( year / 1000 );
			year                             %= 1000;
			string[ internal_string_index++ ] = '0' + (char) ( year / 100 );
			year                             %= 100;
			string[ internal_string_index++ ] = '0' + (char) ( year / 10 );
			year                             %= 10;
			string[ internal_string_index++ ] = '0' + (char) year;

			string[ internal_string_index++ ] = '-';

			string[ internal_string_index++ ] = '0' + (char) ( month / 10 );
			string[ internal_string_index++ ] = '0' + (char) ( month % 10 );

			string[ internal_string_index++ ] = '-';

			string[ internal_string_index++ ] = '0' + (char) ( day_of_month / 10 );
			string[ internal_string_index++ ] = '0' + (char) ( day_of_month % 10 );

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
		string[ internal_string_index++ ] = '0' + (char) ( hours / 10 );
		string[ internal_string_index++ ] = '0' + (char) ( hours % 10 );

		string[ internal_string_index++ ] = ':';

		string[ internal_string_index++ ] = '0' + (char) ( minutes / 10 );
		string[ internal_string_index++ ] = '0' + (char) ( minutes % 10 );

		string[ internal_string_index++ ] = ':';

		string[ internal_string_index++ ] = '0' + (char) ( seconds / 10 );
		string[ internal_string_index++ ] = '0' + (char) ( seconds % 10 );

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

