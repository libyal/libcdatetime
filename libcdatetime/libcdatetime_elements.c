/*
 * Date and time elements functions
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
#include "libcdatetime_types.h"

/* Creates date and time elements
 * Make sure the value elements is referencing, is set to NULL
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

/* Frees date and time elements
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

/* Copies the date and time elements
 * Returns 1 if successful or -1 on error
 */
int libcdatetime_elements_copy(
     libcdatetime_elements_t *destination_elements,
     const libcdatetime_elements_t *source_elements,
     libcerror_error_t **error )
{
	static char *function = "libcdatetime_elements_copy";

	if( destination_elements == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid destination elements.",
		 function );

		return( -1 );
	}
	if( source_elements == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source elements.",
		 function );

		return( -1 );
	}
	if( memory_copy(
	     destination_elements,
	     source_elements,
	     sizeof( libcdatetime_internal_elements_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy elements.",
		 function );

		return( -1 );
	}
	return( 1 );
}

#if defined( WINAPI ) && ( WINVER >= 0x0500 )

/* Retrieves the year
 * Returns 1 if successful or -1 on error
 */
int libcdatetime_elements_get_year(
     libcdatetime_elements_t *elements,
     uint16_t *year,
     libcerror_error_t **error )
{
	libcdatetime_internal_elements_t *internal_elements = NULL;
	static char *function                               = "libcdatetime_elements_get_year";

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

	if( year == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid year.",
		 function );

		return( -1 );
	}
	/* Valid values for the wYear member are 1601 through 30827.
	 */
	if( ( internal_elements->systemtime.wYear < (WORD) 1601 )
	 || ( internal_elements->systemtime.wYear > (WORD) 30827 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid time member year value out of bounds.",
		 function );

		return( -1 );
	}
	*year = (uint16_t) internal_elements->systemtime.wYear;

	return( 1 );
}

#elif defined( WINAPI )

/* TODO */
#error WINAPI get year function for Windows NT4 or earlier NOT implemented yet

#else

/* Retrieves the year
 * Returns 1 if successful or -1 on error
 */
int libcdatetime_elements_get_year(
     libcdatetime_elements_t *elements,
     uint16_t *year,
     libcerror_error_t **error )
{
	libcdatetime_internal_elements_t *internal_elements = NULL;
	static char *function                               = "libcdatetime_elements_get_year";
	int safe_year                                       = 0;

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

	if( year == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid year.",
		 function );

		return( -1 );
	}
	safe_year = 1900 + internal_elements->tm.tm_year;

	/* The number of years since 1900
	 */
	if( ( safe_year < (int) -UINT16_MAX )
	 || ( safe_year > (int) UINT16_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid time member year value out of bounds.",
		 function );

		return( -1 );
	}
	*year = (uint16_t) safe_year;

	return( 1 );
}

#endif

#if defined( WINAPI ) && ( WINVER >= 0x0500 )

/* Retrieves the day of year
 * Returns 1 if successful or -1 on error
 */
int libcdatetime_elements_get_day_of_year(
     libcdatetime_elements_t *elements,
     uint16_t *day_of_year,
     libcerror_error_t **error )
{
	libcdatetime_internal_elements_t *internal_elements = NULL;
	static char *function                               = "libcdatetime_elements_get_day_of_year";

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

	if( day_of_year == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid day of year.",
		 function );

		return( -1 );
	}
	/* Valid values for the wMonth member are 1 through 12.
	 */
	if( ( internal_elements->systemtime.wMonth == (WORD) 0 )
	 || ( internal_elements->systemtime.wMonth > (WORD) 12 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid time member month value out of bounds.",
		 function );

		return( -1 );
	}
	*day_of_year = 0;

	switch( internal_elements->systemtime.wMonth - 1 )
	{
		case 11:
			*day_of_year += 30;
		case 10:
			*day_of_year += 31;
		case 9:
			*day_of_year += 30;
		case 8:
			*day_of_year += 31;
		case 7:
			*day_of_year += 31;
		case 6:
			*day_of_year += 30;
		case 5:
			*day_of_year += 31;
		case 4:
			*day_of_year += 30;
		case 3:
			*day_of_year += 31;
		case 2:
			if( ( ( ( internal_elements->systemtime.wYear % 4 ) == 0 )
			  &&  ( ( internal_elements->systemtime.wYear % 100 ) != 0 ) )
			 || ( ( internal_elements->systemtime.wYear % 400 ) == 0 ) )
			{
				*day_of_year += 29;
			}
			else
			{
				*day_of_year += 28;
			}
		case 1:
			*day_of_year += 31;
		default:
			*day_of_year += internal_elements->systemtime.wDay - 1;
	}
	return( 1 );
}

#elif defined( WINAPI )

/* TODO */
#error WINAPI get day of year function for Windows NT4 or earlier NOT implemented yet

#else

/* Retrieves the day of year
 * Returns 1 if successful or -1 on error
 */
int libcdatetime_elements_get_day_of_year(
     libcdatetime_elements_t *elements,
     uint16_t *day_of_year,
     libcerror_error_t **error )
{
	libcdatetime_internal_elements_t *internal_elements = NULL;
	static char *function                               = "libcdatetime_elements_get_day_of_year";
	int days_in_year                                    = 0;
	int safe_year                                       = 0;

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

	if( day_of_year == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid day of year.",
		 function );

		return( -1 );
	}
	safe_year = 1900 + internal_elements->tm.tm_year;

	if( ( ( ( safe_year % 4 ) == 0 )
	  &&  ( ( safe_year % 100 ) != 0 ) )
	 || ( ( safe_year % 400 ) == 0 ) )
	{
		days_in_year = 366;
	}
	else
	{
		days_in_year = 365;
	}
	/* Valid values for the tm_yday member are 0 through 365.
	 */
	if( ( internal_elements->tm.tm_yday < 0 )
	 || ( internal_elements->tm.tm_yday >= days_in_year ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid time member day of year value out of bounds.",
		 function );

		return( -1 );
	}
	*day_of_year = (uint8_t) internal_elements->tm.tm_yday;

	return( 1 );
}

#endif

#if defined( WINAPI ) && ( WINVER >= 0x0500 )

/* Retrieves the month
 * Returns 1 if successful or -1 on error
 */
int libcdatetime_elements_get_month(
     libcdatetime_elements_t *elements,
     uint8_t *month,
     libcerror_error_t **error )
{
	libcdatetime_internal_elements_t *internal_elements = NULL;
	static char *function                               = "libcdatetime_elements_get_month";

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

	if( month == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid month.",
		 function );

		return( -1 );
	}
	/* Valid values for the wMonth member are 1 through 12.
	 */
	if( ( internal_elements->systemtime.wMonth == (WORD) 0 )
	 || ( internal_elements->systemtime.wMonth > (WORD) 12 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid time member month value out of bounds.",
		 function );

		return( -1 );
	}
	*month = (uint8_t) internal_elements->systemtime.wMonth;

	return( 1 );
}

#elif defined( WINAPI )

/* TODO */
#error WINAPI get month function for Windows NT4 or earlier NOT implemented yet

#else

/* Retrieves the month
 * Returns 1 if successful or -1 on error
 */
int libcdatetime_elements_get_month(
     libcdatetime_elements_t *elements,
     uint8_t *month,
     libcerror_error_t **error )
{
	libcdatetime_internal_elements_t *internal_elements = NULL;
	static char *function                               = "libcdatetime_elements_get_month";

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

	if( month == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid month.",
		 function );

		return( -1 );
	}
	/* Valid values for the tm_mon member are 0 through 11.
	 */
	if( ( internal_elements->tm.tm_mon < 0 )
	 || ( internal_elements->tm.tm_mon > 11 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid time member month value out of bounds.",
		 function );

		return( -1 );
	}
	*month = (uint8_t) internal_elements->tm.tm_mon + 1;

	return( 1 );
}

#endif

#if defined( WINAPI ) && ( WINVER >= 0x0500 )

/* Retrieves the day of month
 * Returns 1 if successful or -1 on error
 */
int libcdatetime_elements_get_day_of_month(
     libcdatetime_elements_t *elements,
     uint8_t *day_of_month,
     libcerror_error_t **error )
{
	libcdatetime_internal_elements_t *internal_elements = NULL;
	static char *function                               = "libcdatetime_elements_get_day_of_month";
	WORD days_in_month                                  = 0;

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

	if( day_of_month == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid day of month.",
		 function );

		return( -1 );
	}
	/* Valid values for the wMonth member are 1 through 12.
	 */
	if( ( internal_elements->systemtime.wMonth == (WORD) 0 )
	 || ( internal_elements->systemtime.wMonth > (WORD) 12 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid time member month value out of bounds.",
		 function );

		return( -1 );
	}
	switch( internal_elements->systemtime.wMonth )
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
			if( ( ( ( internal_elements->systemtime.wYear % 4 ) == 0 )
			  &&  ( ( internal_elements->systemtime.wYear % 100 ) != 0 ) )
			 || ( ( internal_elements->systemtime.wYear % 400 ) == 0 ) )
			{
				days_in_month = 29;
			}
			else
			{
				days_in_month = 28;
			}
			break;
	}
	/* Valid values for the wDay member are 1 through 31.
	 */
	if( ( internal_elements->systemtime.wDay == (WORD) 0 )
	 || ( internal_elements->systemtime.wDay >= days_in_month ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid time member day of month value out of bounds.",
		 function );

		return( -1 );
	}
	*day_of_month = (uint8_t) internal_elements->systemtime.wDay;

	return( 1 );
}

#elif defined( WINAPI )

/* TODO */
#error WINAPI get day of month function for Windows NT4 or earlier NOT implemented yet

#else

/* Retrieves the day of month
 * Returns 1 if successful or -1 on error
 */
int libcdatetime_elements_get_day_of_month(
     libcdatetime_elements_t *elements,
     uint8_t *day_of_month,
     libcerror_error_t **error )
{
	libcdatetime_internal_elements_t *internal_elements = NULL;
	static char *function                               = "libcdatetime_elements_get_day_of_month";
	int days_in_month                                   = 0;
	int safe_year                                       = 0;

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

	if( day_of_month == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid day of month.",
		 function );

		return( -1 );
	}
	/* Valid values for the tm_mon member are 0 through 11.
	 */
	if( ( internal_elements->tm.tm_mon < 0 )
	 || ( internal_elements->tm.tm_mon > 11 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid time member month value out of bounds.",
		 function );

		return( -1 );
	}
	safe_year = 1900 + internal_elements->tm.tm_year;

	switch( internal_elements->tm.tm_mon + 1 )
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
			if( ( ( ( safe_year % 4 ) == 0 )
			  &&  ( ( safe_year % 100 ) != 0 ) )
			 || ( ( safe_year % 400 ) == 0 ) )
			{
				days_in_month = 29;
			}
			else
			{
				days_in_month = 28;
			}
			break;
	}
	/* Valid values for the tm_mday member are 1 through 31.
	 */
	if( ( internal_elements->tm.tm_mday <= 0 )
	 || ( internal_elements->tm.tm_mday > days_in_month ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid time member day of month value out of bounds.",
		 function );

		return( -1 );
	}
	*day_of_month = (uint8_t) internal_elements->tm.tm_mday;

	return( 1 );
}

#endif

/* Retrieves the date values
 * Returns 1 if successful or -1 on error
 */
int libcdatetime_elements_get_date_values(
     libcdatetime_elements_t *elements,
     uint16_t *year,
     uint8_t *month,
     uint8_t *day_of_month,
     libcerror_error_t **error )
{
	static char *function = "libcdatetime_elements_get_date_values";

	if( libcdatetime_elements_get_year(
	     elements,
	     year,
	     error ) != 1 )
	{
		libcerror_system_set_error(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 errno,
		 "%s: unable to retrieve year.",
		 function );

		return( -1 );
	}
	if( libcdatetime_elements_get_month(
	     elements,
	     month,
	     error ) != 1 )
	{
		libcerror_system_set_error(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 errno,
		 "%s: unable to retrieve month.",
		 function );

		return( -1 );
	}
	if( libcdatetime_elements_get_day_of_month(
	     elements,
	     day_of_month,
	     error ) != 1 )
	{
		libcerror_system_set_error(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 errno,
		 "%s: unable to retrieve day of month.",
		 function );

		return( -1 );
	}
	return( 1 );
}

#if defined( WINAPI ) && ( WINVER >= 0x0500 )

/* Retrieves the hours
 * Returns 1 if successful or -1 on error
 */
int libcdatetime_elements_get_hours(
     libcdatetime_elements_t *elements,
     uint8_t *hours,
     libcerror_error_t **error )
{
	libcdatetime_internal_elements_t *internal_elements = NULL;
	static char *function                               = "libcdatetime_elements_get_hours";

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

	if( hours == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid hours.",
		 function );

		return( -1 );
	}
	/* Valid values for the wHour member are 0 through 23.
	 */
	if( internal_elements->systemtime.wHour > (WORD) 23 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid time member hours value out of bounds.",
		 function );

		return( -1 );
	}
	*hours = (uint8_t) internal_elements->systemtime.wHour;

	return( 1 );
}

#elif defined( WINAPI )

/* TODO */
#error WINAPI get hours function for Windows NT4 or earlier NOT implemented yet

#else

/* Retrieves the hours
 * Returns 1 if successful or -1 on error
 */
int libcdatetime_elements_get_hours(
     libcdatetime_elements_t *elements,
     uint8_t *hours,
     libcerror_error_t **error )
{
	libcdatetime_internal_elements_t *internal_elements = NULL;
	static char *function                               = "libcdatetime_elements_get_hours";

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

	if( hours == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid hours.",
		 function );

		return( -1 );
	}
	/* Valid values for the tm_hour member are 0 through 23.
	 */
	if( ( internal_elements->tm.tm_hour < 0 )
	 || ( internal_elements->tm.tm_hour > 23 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid time member hours value out of bounds.",
		 function );

		return( -1 );
	}
	*hours = (uint8_t) internal_elements->tm.tm_hour;

	return( 1 );
}

#endif

#if defined( WINAPI ) && ( WINVER >= 0x0500 )

/* Retrieves the minutes
 * Returns 1 if successful or -1 on error
 */
int libcdatetime_elements_get_minutes(
     libcdatetime_elements_t *elements,
     uint8_t *minutes,
     libcerror_error_t **error )
{
	libcdatetime_internal_elements_t *internal_elements = NULL;
	static char *function                               = "libcdatetime_elements_get_minutes";

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

	if( minutes == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid minutes.",
		 function );

		return( -1 );
	}
	/* Valid values for the wMinute member are 0 through 59.
	 */
	if( internal_elements->systemtime.wMinute > (WORD) 59 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid time member minutes value out of bounds.",
		 function );

		return( -1 );
	}
	*minutes = (uint8_t) internal_elements->systemtime.wMinute;

	return( 1 );
}

#elif defined( WINAPI )

/* TODO */
#error WINAPI get minutes function for Windows NT4 or earlier NOT implemented yet

#else

/* Retrieves the minutes
 * Returns 1 if successful or -1 on error
 */
int libcdatetime_elements_get_minutes(
     libcdatetime_elements_t *elements,
     uint8_t *minutes,
     libcerror_error_t **error )
{
	libcdatetime_internal_elements_t *internal_elements = NULL;
	static char *function                               = "libcdatetime_elements_get_minutes";

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

	if( minutes == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid minutes.",
		 function );

		return( -1 );
	}
	/* Valid values for the tm_min member are 0 through 59.
	 */
	if( ( internal_elements->tm.tm_min < 0 )
	 || ( internal_elements->tm.tm_min > 59 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid time member minutes value out of bounds.",
		 function );

		return( -1 );
	}
	*minutes = (uint8_t) internal_elements->tm.tm_min;

	return( 1 );
}

#endif

#if defined( WINAPI ) && ( WINVER >= 0x0500 )

/* Retrieves the seconds
 * Returns 1 if successful or -1 on error
 */
int libcdatetime_elements_get_seconds(
     libcdatetime_elements_t *elements,
     uint8_t *seconds,
     libcerror_error_t **error )
{
	libcdatetime_internal_elements_t *internal_elements = NULL;
	static char *function                               = "libcdatetime_elements_get_seconds";

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

	if( seconds == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid seconds.",
		 function );

		return( -1 );
	}
	/* Valid values for the wSecond member are 0 through 59.
	 */
	if( internal_elements->systemtime.wSecond > (WORD) 59 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid time member seconds value out of bounds.",
		 function );

		return( -1 );
	}
	*seconds = (uint8_t) internal_elements->systemtime.wSecond;

	return( 1 );
}

#elif defined( WINAPI )

/* TODO */
#error WINAPI get seconds function for Windows NT4 or earlier NOT implemented yet

#else

/* Retrieves the seconds
 * Returns 1 if successful or -1 on error
 */
int libcdatetime_elements_get_seconds(
     libcdatetime_elements_t *elements,
     uint8_t *seconds,
     libcerror_error_t **error )
{
	libcdatetime_internal_elements_t *internal_elements = NULL;
	static char *function                               = "libcdatetime_elements_get_seconds";

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

	if( seconds == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid seconds.",
		 function );

		return( -1 );
	}
	/* Valid values for the tm_sec member are 0 through 59.
	 */
	if( ( internal_elements->tm.tm_sec < 0 )
	 || ( internal_elements->tm.tm_sec > 59 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid time member seconds value out of bounds.",
		 function );

		return( -1 );
	}
	*seconds = (uint8_t) internal_elements->tm.tm_sec;

	return( 1 );
}

#endif

#if defined( WINAPI ) && ( WINVER >= 0x0500 )

/* Retrieves the milli seconds
 * Returns 1 if successful or -1 on error
 */
int libcdatetime_elements_get_milli_seconds(
     libcdatetime_elements_t *elements,
     uint16_t *milli_seconds,
     libcerror_error_t **error )
{
	libcdatetime_internal_elements_t *internal_elements = NULL;
	static char *function                               = "libcdatetime_elements_get_milli_seconds";

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

	if( milli_seconds == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid milli seconds.",
		 function );

		return( -1 );
	}
	/* Valid values for the wMilliseconds member are 0 through 999.
	 */
	if( internal_elements->systemtime.wMilliseconds > (WORD) 999 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid time member milli seconds value out of bounds.",
		 function );

		return( -1 );
	}
	*milli_seconds = (uint16_t) internal_elements->systemtime.wMilliseconds;

	return( 1 );
}

#elif defined( WINAPI )

/* TODO */
#error WINAPI get milli seconds function for Windows NT4 or earlier NOT implemented yet

#else

/* Retrieves the milli seconds
 * Returns 1 if successful or -1 on error
 */
int libcdatetime_elements_get_milli_seconds(
     libcdatetime_elements_t *elements,
     uint16_t *milli_seconds,
     libcerror_error_t **error )
{
	static char *function = "libcdatetime_elements_get_milli_seconds";

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
	if( milli_seconds == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid milli seconds.",
		 function );

		return( -1 );
	}
	/* Seconds is the smallest granularity we have so default to 0.
	 */
	*milli_seconds = 0;

	return( 1 );
}

#endif

/* Retrieves the micro seconds
 * Returns 1 if successful or -1 on error
 */
int libcdatetime_elements_get_micro_seconds(
     libcdatetime_elements_t *elements,
     uint16_t *micro_seconds,
     libcerror_error_t **error )
{
	static char *function = "libcdatetime_elements_get_micro_seconds";

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
	if( micro_seconds == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid micro seconds.",
		 function );

		return( -1 );
	}
	/* Milli seconds is the smallest granularity we have so default to 0.
	 */
	*micro_seconds = 0;

	return( 1 );
}

/* Retrieves the nano seconds
 * Returns 1 if successful or -1 on error
 */
int libcdatetime_elements_get_nano_seconds(
     libcdatetime_elements_t *elements,
     uint16_t *nano_seconds,
     libcerror_error_t **error )
{
	static char *function = "libcdatetime_elements_get_nano_seconds";

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
	if( nano_seconds == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid nano seconds.",
		 function );

		return( -1 );
	}
	/* Milli seconds is the smallest granularity we have so default to 0.
	 */
	*nano_seconds = 0;

	return( 1 );
}

/* Retrieves the time values
 * Returns 1 if successful or -1 on error
 */
int libcdatetime_elements_get_time_values(
     libcdatetime_elements_t *elements,
     uint8_t *hours,
     uint8_t *minutes,
     uint8_t *seconds,
     libcerror_error_t **error )
{
	static char *function = "libcdatetime_elements_get_time_values";

	if( libcdatetime_elements_get_hours(
	     elements,
	     hours,
	     error ) != 1 )
	{
		libcerror_system_set_error(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 errno,
		 "%s: unable to retrieve hours.",
		 function );

		return( -1 );
	}
	if( libcdatetime_elements_get_minutes(
	     elements,
	     minutes,
	     error ) != 1 )
	{
		libcerror_system_set_error(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 errno,
		 "%s: unable to retrieve minutes.",
		 function );

		return( -1 );
	}
	if( libcdatetime_elements_get_seconds(
	     elements,
	     seconds,
	     error ) != 1 )
	{
		libcerror_system_set_error(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 errno,
		 "%s: unable to retrieve seconds.",
		 function );

		return( -1 );
	}
	return( 1 );
}

#if defined( WINAPI ) && ( WINVER >= 0x0500 )

/* Sets the date and time elements from a FILETIME value in UTC
 * Returns 1 if successful or -1 on error
 */
int libcdatetime_internal_elements_set_from_filetime_utc(
     libcdatetime_internal_elements_t *internal_elements,
     FILETIME *filetime,
     libcerror_error_t **error )
{
	static char *function = "libcdatetime_internal_elements_set_from_filetime_utc";
	DWORD error_code      = 0;

	if( internal_elements == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid elements.",
		 function );

		return( -1 );
	}
	if( filetime == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filetime.",
		 function );

		return( -1 );
	}
	if( FileTimeToSystemTime(
	     filetime,
	     &( internal_elements->systemtime ) ) == 0 )
	{
		error_code = GetLastError();

		libcerror_system_set_error(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 error_code,
		 "%s: unable to retrieve systemtime.",
		 function );

		return( -1 );
	}
	return( 1 );
}

#endif

#if !defined( WINAPI ) && defined( HAVE_TIME ) && ( defined( HAVE_GMTIME ) || defined( HAVE_GMTIME_R ) )

/* Sets the date and time elements from a POSIX time value in UTC
 * Returns 1 if successful or -1 on error
 */
int libcdatetime_internal_elements_set_from_time_utc(
     libcdatetime_internal_elements_t *internal_elements,
     time_t *time,
     libcerror_error_t **error )
{
	static char *function = "libcdatetime_internal_elements_set_from_time_utc";

#if !defined( HAVE_GMTIME_R )
	struct tm *static_tm  = NULL;
#endif

	if( internal_elements == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid elements.",
		 function );

		return( -1 );
	}
	if( time == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid time.",
		 function );

		return( -1 );
	}
#if defined( HAVE_GMTIME_R )
	if( gmtime_r(
	     time,
	     &( internal_elements->tm ) ) == NULL )
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
	static_tm = gmtime(
	             time );

	if( static_tm == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to create static time members.",
		 function );

		return( -1 );
	}
	if( memory_copy(
	     internal_elements->tm,
	     static_tm,
	     sizeof( struct tm ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy time members.",
		 function );

		return( -1 );
	}
#endif
	return( 1 );
}

#endif /* !defined( WINAPI ) && defined( HAVE_TIME ) && ( defined( HAVE_GMTIME ) || defined( HAVE_GMTIME_R ) ) */

#if !defined( WINAPI ) && defined( HAVE_TIME ) && ( defined( HAVE_LOCALTIME ) || defined( HAVE_LOCALTIME_R ) )

/* Sets the date and time elements from a POSIX time value in localtime
 * Returns 1 if successful or -1 on error
 */
int libcdatetime_internal_elements_set_from_time_localtime(
     libcdatetime_internal_elements_t *internal_elements,
     time_t *time,
     libcerror_error_t **error )
{
	static char *function = "libcdatetime_internal_elements_set_from_time_localtime";

#if !defined( HAVE_LOCALTIME_R )
	struct tm *static_tm  = NULL;
#endif

	if( internal_elements == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid elements.",
		 function );

		return( -1 );
	}
	if( time == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid time.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LOCALTIME_R )
	if( localtime_r(
	     time,
	     &( internal_elements->tm ) ) == NULL )
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
	static_tm = localtime(
	             time );

	if( static_tm == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to create static time members.",
		 function );

		return( -1 );
	}
	if( memory_copy(
	     internal_elements->tm,
	     static_tm,
	     sizeof( struct tm ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy time members.",
		 function );

		return( -1 );
	}
#endif
	return( 1 );
}

#endif /* if !defined( WINAPI ) && defined( HAVE_TIME ) && ( defined( HAVE_LOCALTIME ) || defined( HAVE_LOCALTIME_R ) ) */

#if defined( WINAPI ) && ( WINVER >= 0x0500 )

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
	DWORD error_code                                    = 0;

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
	 &( internal_elements->systemtime ) );

	if( SystemTimeToFileTime(
	     &( internal_elements->systemtime ),
	     &( internal_elements->filetime ) ) == 0 )
	{
		error_code = GetLastError();

		libcerror_system_set_error(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 errno,
		 "%s: unable to retrieve filetime.",
		 function );

		return( -1 );
	}
	internal_elements->mode = LIBCDATETIME_ELEMENTS_MODE_DATE_TIME_IN_UTC;

	return( 1 );
}

#elif defined( WINAPI )

/* TODO */
#error WINAPI set current time in UTC function for Windows NT4 or earlier NOT implemented yet

#elif defined( HAVE_TIME ) && ( defined( HAVE_GMTIME ) || defined( HAVE_GMTIME_R ) )

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

	if( time(
	     &( internal_elements->time ) ) == (time_t) -1 )
	{
		libcerror_system_set_error(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 errno,
		 "%s: unable to retrieve time.",
		 function );

		return( -1 );
	}
	if( libcdatetime_internal_elements_set_from_time_utc(
             internal_elements,
	     &( internal_elements->time ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set time elements from time.",
		 function );

		return( -1 );
	}
	internal_elements->mode = LIBCDATETIME_ELEMENTS_MODE_DATE_TIME_IN_UTC;

	return( 1 );
}

#else
#error Missing get current time in UTC function
#endif

#if defined( WINAPI ) && ( WINVER >= 0x0500 )

/* Sets the date and time elements to the current (system) date and time in localtime
 * This function uses the WINAPI function for Windows 2000 or later
 * Returns 1 if successful or -1 on error
 */
int libcdatetime_elements_set_current_time_localtime(
     libcdatetime_elements_t *elements,
     libcerror_error_t **error )
{
	libcdatetime_internal_elements_t *internal_elements = NULL;
	static char *function                               = "libcdatetime_elements_set_current_time_localtime";
	DWORD error_code                                    = 0;

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

	GetLocalTime(
	 &( internal_elements->systemtime ) );

	if( SystemTimeToFileTime(
	     &( internal_elements->systemtime ),
	     &( internal_elements->filetime ) ) == 0 )
	{
		error_code = GetLastError();

		libcerror_system_set_error(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 errno,
		 "%s: unable to retrieve filetime.",
		 function );

		return( -1 );
	}
	internal_elements->mode = LIBCDATETIME_ELEMENTS_MODE_DATE_TIME_IN_LOCALTIME;

	return( 1 );
}

#elif defined( WINAPI )

/* TODO */
#error WINAPI set current time in localtime function for Windows NT4 or earlier NOT implemented yet

#elif defined( HAVE_TIME ) && ( defined( HAVE_LOCALTIME ) || defined( HAVE_LOCALTIME_R ) )

/* Sets the date and time elements to the current (system) date and time in localtime
 * This function uses the POSIX time function or equivalent
 * Returns 1 if successful or -1 on error
 */
int libcdatetime_elements_set_current_time_localtime(
     libcdatetime_elements_t *elements,
     libcerror_error_t **error )
{
	libcdatetime_internal_elements_t *internal_elements = NULL;
	static char *function                               = "libcdatetime_elements_set_current_time_localtime";

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

	if( time(
	     &( internal_elements->time ) ) == (time_t) -1 )
	{
		libcerror_system_set_error(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 errno,
		 "%s: unable to retrieve time.",
		 function );

		return( -1 );
	}
	if( libcdatetime_internal_elements_set_from_time_localtime(
             internal_elements,
	     &( internal_elements->time ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set time elements from time.",
		 function );

		return( -1 );
	}
	internal_elements->mode = LIBCDATETIME_ELEMENTS_MODE_DATE_TIME_IN_LOCALTIME;

	return( 1 );
}

#else
#error Missing get current time in localtime function
#endif

#if defined( WINAPI ) && ( WINVER >= 0x0500 )

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
	libcdatetime_internal_elements_t *internal_first_elements  = NULL;
	libcdatetime_internal_elements_t *internal_second_elements = NULL;
	static char *function                                      = "libcdatetime_elements_get_delta_in_seconds";
	int64_t time_delta                                         = 0;

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
	if( internal_first_elements->mode != internal_second_elements->mode )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid second elements - mismatch in mode value.",
		 function );

		return( -1 );
	}
	time_delta = (int64_t) internal_first_elements->filetime.dwHighDateTime - (int64_t) internal_second_elements->filetime.dwHighDateTime;

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

	time_delta += (int64_t) internal_first_elements->filetime.dwLowDateTime - (int64_t) internal_second_elements->filetime.dwLowDateTime;

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

#if defined( WINAPI ) && ( WINVER >= 0x0500 )

/* Sets the time elements from the delta in seconds
 * Returns 1 if successful or -1 on error
 */
int libcdatetime_elements_set_from_delta_in_seconds(
     libcdatetime_elements_t *elements,
     int64_t number_of_seconds,
     libcerror_error_t **error )
{
	libcdatetime_internal_elements_t *internal_elements = NULL;
	static char *function                               = "libcdatetime_elements_set_from_delta_in_seconds";

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

	if( number_of_seconds < 0 )
	{
/* TODO mark duration as negative ? */
		number_of_seconds *= -1;
	}
	internal_elements->filetime.dwHighDateTime = (DWORD) ( ( number_of_seconds >> 32 ) & 0xffffffffUL );
	internal_elements->filetime.dwLowDateTime  = (DWORD) ( number_of_seconds & 0xffffffffUL );

	if( libcdatetime_internal_elements_set_from_filetime_utc(
             internal_elements,
	     &( internal_elements->filetime ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set time elements from filetime.",
		 function );

		return( -1 );
	}
	internal_elements->mode = LIBCDATETIME_ELEMENTS_MODE_DURATION;

	return( 1 );
}

#elif defined( WINAPI )

/* TODO */
#error WINAPI set from delta in seconds function for Windows NT4 or earlier NOT implemented yet

#else

/* Sets the time elements from the delta in seconds
 * Returns 1 if successful or -1 on error
 */
int libcdatetime_elements_set_from_delta_in_seconds(
     libcdatetime_elements_t *elements,
     int64_t number_of_seconds,
     libcerror_error_t **error )
{
	libcdatetime_internal_elements_t *internal_elements = NULL;
	static char *function                               = "libcdatetime_elements_set_from_delta_in_seconds";

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

/* TODO check bounds of number_of_seconds for time_t cast */
	if( number_of_seconds < 0 )
	{
/* TODO mark duration as negative ? */
		number_of_seconds *= -1;
	}
	internal_elements->time = (time_t) number_of_seconds;

	if( libcdatetime_internal_elements_set_from_time_utc(
             internal_elements,
	     &( internal_elements->time ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set time elements from time.",
		 function );

		return( -1 );
	}
	internal_elements->mode = LIBCDATETIME_ELEMENTS_MODE_DURATION;

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
int libcdatetime_elements_copy_to_string(
     libcdatetime_elements_t *elements,
     uint8_t *string,
     size_t string_size,
     uint32_t string_format_flags,
     libcerror_error_t **error )
{
	static char *function = "libcdatetime_elements_copy_to_string";
	size_t string_index   = 0;

	if( libcdatetime_elements_copy_to_string_with_index(
	     elements,
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
		 "%s: unable to copy elements to string.",
		 function );

		return( -1 );
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
	uint8_t *month_string        = NULL;
	static char *function        = "libcdatetime_elements_copy_to_string_with_index";
	size_t internal_string_index = 0;
	uint32_t string_format_type  = 0;
	uint32_t supported_flags     = 0;
	uint16_t micro_seconds       = 0;
	uint16_t milli_seconds       = 0;
	uint16_t nano_seconds        = 0;
	uint16_t year                = 0;
	uint8_t day_of_month         = 0;
	uint8_t hours                = 0;
	uint8_t minutes              = 0;
	uint8_t month                = 0;
	uint8_t seconds              = 0;

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
		/* The libcdatetime_elements_get_date_value function returns sane values.
		 */
		if( libcdatetime_elements_get_date_values(
		     elements,
		     &year,
		     &month,
		     &day_of_month,
		     error ) != 1 )
		{
			libcerror_system_set_error(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 errno,
			 "%s: unable to retrieve date values.",
			 function );

			return( -1 );
		}
		if( year > 9999 )
		{
			return( 0 );
		}
	}
	if( ( string_format_flags & LIBCDATETIME_STRING_FORMAT_FLAG_TIME ) != 0 )
	{
		/* The libcdatetime_elements_get_time_value function returns sane values.
		 */
		if( libcdatetime_elements_get_time_values(
		     elements,
		     &hours,
		     &minutes,
		     &seconds,
		     error ) != 1 )
		{
			libcerror_system_set_error(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 errno,
			 "%s: unable to retrieve time values.",
			 function );

			return( -1 );
		}
		if( ( ( string_format_flags & LIBCDATETIME_STRING_FORMAT_FLAG_TIME_MILLI_SECONDS ) != 0 )
		 || ( ( string_format_flags & LIBCDATETIME_STRING_FORMAT_FLAG_TIME_MICRO_SECONDS ) != 0 )
		 || ( ( string_format_flags & LIBCDATETIME_STRING_FORMAT_FLAG_TIME_NANO_SECONDS ) != 0 ) )
		{
			if( libcdatetime_elements_get_milli_seconds(
			     elements,
			     &milli_seconds,
			     error ) != 1 )
			{
				libcerror_system_set_error(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 errno,
				 "%s: unable to retrieve milli seconds.",
				 function );

				return( -1 );
			}
			if( milli_seconds > 999 )
			{
				return( 0 );
			}
		}
		if( ( ( string_format_flags & LIBCDATETIME_STRING_FORMAT_FLAG_TIME_MICRO_SECONDS ) != 0 )
		 || ( ( string_format_flags & LIBCDATETIME_STRING_FORMAT_FLAG_TIME_NANO_SECONDS ) != 0 ) )
		{
			if( libcdatetime_elements_get_micro_seconds(
			     elements,
			     &micro_seconds,
			     error ) != 1 )
			{
				libcerror_system_set_error(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 errno,
				 "%s: unable to retrieve micro seconds.",
				 function );

				return( -1 );
			}
			if( micro_seconds > 999 )
			{
				return( 0 );
			}
		}
		if( ( string_format_flags & LIBCDATETIME_STRING_FORMAT_FLAG_TIME_NANO_SECONDS ) != 0 )
		{
			if( libcdatetime_elements_get_nano_seconds(
			     elements,
			     &nano_seconds,
			     error ) != 1 )
			{
				libcerror_system_set_error(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 errno,
				 "%s: unable to retrieve nano seconds.",
				 function );

				return( -1 );
			}
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
					month_string = (uint8_t *) "Jan";
					break;
				case 2:
					month_string = (uint8_t *) "Feb";
					break;
				case 3:
					month_string = (uint8_t *) "Mar";
					break;
				case 4:
					month_string = (uint8_t *) "Apr";
					break;
				case 5:
					month_string = (uint8_t *) "May";
					break;
				case 6:
					month_string = (uint8_t *) "Jun";
					break;
				case 7:
					month_string = (uint8_t *) "Jul";
					break;
				case 8:
					month_string = (uint8_t *) "Aug";
					break;
				case 9:
					month_string = (uint8_t *) "Sep";
					break;
				case 10:
					month_string = (uint8_t *) "Oct";
					break;
				case 11:
					month_string = (uint8_t *) "Nov";
					break;
				case 12:
					month_string = (uint8_t *) "Dec";
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

			string[ internal_string_index++ ] = (uint8_t) ' ';

			string[ internal_string_index++ ] = (uint8_t) '0' + (uint8_t) ( day_of_month / 10 );
			string[ internal_string_index++ ] = (uint8_t) '0' + (uint8_t) ( day_of_month % 10 );

			string[ internal_string_index++ ] = (uint8_t) ',';
			string[ internal_string_index++ ] = (uint8_t) ' ';

			string[ internal_string_index++ ] = (uint8_t) '0' + (uint8_t) ( year / 1000 );
			year                             %= 1000;
			string[ internal_string_index++ ] = (uint8_t) '0' + (uint8_t) ( year / 100 );
			year                             %= 100;
			string[ internal_string_index++ ] = (uint8_t) '0' + (uint8_t) ( year / 10 );
			year                             %= 10;
			string[ internal_string_index++ ] = (uint8_t) '0' + (uint8_t) year;

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
				string[ internal_string_index++ ] = (uint8_t) ' ';
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
			string[ internal_string_index++ ] = (uint8_t) '0' + (uint8_t) ( year / 1000 );
			year                             %= 1000;
			string[ internal_string_index++ ] = (uint8_t) '0' + (uint8_t) ( year / 100 );
			year                             %= 100;
			string[ internal_string_index++ ] = (uint8_t) '0' + (uint8_t) ( year / 10 );
			year                             %= 10;
			string[ internal_string_index++ ] = (uint8_t) '0' + (uint8_t) year;

			string[ internal_string_index++ ] = (uint8_t) '-';

			string[ internal_string_index++ ] = (uint8_t) '0' + (uint8_t) ( month / 10 );
			string[ internal_string_index++ ] = (uint8_t) '0' + (uint8_t) ( month % 10 );

			string[ internal_string_index++ ] = (uint8_t) '-';

			string[ internal_string_index++ ] = (uint8_t) '0' + (uint8_t) ( day_of_month / 10 );
			string[ internal_string_index++ ] = (uint8_t) '0' + (uint8_t) ( day_of_month % 10 );

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
		string[ internal_string_index++ ] = (uint8_t) '0' + (uint8_t) ( hours / 10 );
		string[ internal_string_index++ ] = (uint8_t) '0' + (uint8_t) ( hours % 10 );

		string[ internal_string_index++ ] = (uint8_t) ':';

		string[ internal_string_index++ ] = (uint8_t) '0' + (uint8_t) ( minutes / 10 );
		string[ internal_string_index++ ] = (uint8_t) '0' + (uint8_t) ( minutes % 10 );

		string[ internal_string_index++ ] = (uint8_t) ':';

		string[ internal_string_index++ ] = (uint8_t) '0' + (uint8_t) ( seconds / 10 );
		string[ internal_string_index++ ] = (uint8_t) '0' + (uint8_t) ( seconds % 10 );

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
			string[ internal_string_index++ ] = (uint8_t) '.';

			string[ internal_string_index + 2 ] = (uint8_t) '0' + (uint8_t) ( milli_seconds % 10 );
			milli_seconds                      /= 10;

			string[ internal_string_index + 1 ] = (uint8_t) '0' + (uint8_t) ( milli_seconds % 10 );
			milli_seconds                      /= 10;

			string[ internal_string_index ] = (uint8_t) '0' + (uint8_t) ( milli_seconds % 10 );
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
			string[ internal_string_index + 2 ] = (uint8_t) '0' + (uint8_t) ( micro_seconds % 10 );
			micro_seconds                      /= 10;

			string[ internal_string_index + 1 ] = (uint8_t) '0' + (uint8_t) ( micro_seconds % 10 );
			micro_seconds                      /= 10;

			string[ internal_string_index ] = (uint8_t) '0' + (uint8_t) ( micro_seconds % 10 );
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
			string[ internal_string_index + 2 ] = (uint8_t) '0' + (uint8_t) ( nano_seconds % 10 );
			nano_seconds                       /= 10;

			string[ internal_string_index + 1 ] = (uint8_t) '0' + (uint8_t) ( nano_seconds % 10 );
			nano_seconds                       /= 10;

			string[ internal_string_index ] = (uint8_t) '0' + (uint8_t) ( nano_seconds % 10 );
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
			string[ internal_string_index++ ] = (uint8_t) ' ';
			string[ internal_string_index++ ] = (uint8_t) 'U';
			string[ internal_string_index++ ] = (uint8_t) 'T';
			string[ internal_string_index++ ] = (uint8_t) 'C';
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
			string[ internal_string_index++ ] = (uint8_t) 'Z';
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

