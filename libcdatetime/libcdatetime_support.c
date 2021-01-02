/*
 * Support functions
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
#include <types.h>

#include "libcdatetime_definitions.h"
#include "libcdatetime_libcerror.h"
#include "libcdatetime_support.h"

#if !defined( LIBCDATETIME_ATTRIBUTE_FALLTHROUGH )
#if defined( __GNUC__ ) && __GNUC__ >= 7
#define LIBCDATETIME_ATTRIBUTE_FALLTHROUGH	__attribute__ ((fallthrough))
#else
#define LIBCDATETIME_ATTRIBUTE_FALLTHROUGH
#endif
#endif

#if !defined( HAVE_LOCAL_LIBCDATETIME )

/* Returns the library version as a string
 */
const char *libcdatetime_get_version(
             void )
{
	return( (const char *) LIBCDATETIME_VERSION_STRING );
}

#endif /* !defined( HAVE_LOCAL_LIBCDATETIME ) */

/* Determines if the year is a leap year
 * Returns 1 if a leay year or 0 if not
 */
int libcdatetime_is_leap_year(
     uint16_t year )
{
	if( ( ( year % 4 ) == 0 )
	 && ( ( year % 100 ) != 0 ) )
	{
		return( 1 );
	}
	if( ( year % 400 ) == 0 )
	{
		return( 1 );
	}
	return( 0 );
}

/* Calculates the days in a month
 * Returns 1 if successful or -1 on error
 */
int libcdatetime_get_days_in_month(
     uint8_t *days_in_month,
     uint16_t year,
     uint8_t month,
     libcerror_error_t **error )
{
	static char *function = "libcdatetime_get_days_in_month";

	if( days_in_month == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid days in month.",
		 function );

		return( -1 );
	}
	/* Valid values for the month value are 1 through 12.
	 */
	if( ( month == 0 )
	 || ( month > 12 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid month value out of bounds.",
		 function );

		return( -1 );
	}
	switch( month )
	{
		case LIBCDATETIME_MONTH_JANUARY:
		case LIBCDATETIME_MONTH_MARCH:
		case LIBCDATETIME_MONTH_MAY:
		case LIBCDATETIME_MONTH_JULY:
		case LIBCDATETIME_MONTH_AUGUST:
		case LIBCDATETIME_MONTH_OCTOBER:
		case LIBCDATETIME_MONTH_DECEMBER:
			*days_in_month = 31;
			break;

		case LIBCDATETIME_MONTH_APRIL:
		case LIBCDATETIME_MONTH_JUNE:
		case LIBCDATETIME_MONTH_SEPTEMBER:
		case LIBCDATETIME_MONTH_NOVEMBER:
			*days_in_month = 30;
			break;

		case LIBCDATETIME_MONTH_FEBRUARY:
			if( libcdatetime_is_leap_year(
			     year ) != 0 )
			{
				*days_in_month = 29;
			}
			else
			{
				*days_in_month = 28;
			}
			break;
	}
	return( 1 );
}

/* Calculates the day of year
 * Returns 1 if successful or -1 on error
 */
int libcdatetime_get_day_of_year(
     uint16_t *day_of_year,
     uint16_t year,
     uint8_t month,
     uint8_t day_of_month,
     libcerror_error_t **error )
{
	static char *function     = "libcdatetime_get_day_of_year";
	uint16_t safe_day_of_year = 0;
	uint8_t days_in_month     = 0;

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
	if( libcdatetime_get_days_in_month(
	     &days_in_month,
	     year,
	     month,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve days in month.",
		 function );

		return( -1 );
	}
	if( ( day_of_month == 0 )
	 || ( day_of_month > days_in_month ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid day of month value out of bounds.",
		 function );

		return( -1 );
	}
	safe_day_of_year = 0;

	switch( month )
	{
		case LIBCDATETIME_MONTH_DECEMBER:
			safe_day_of_year += 30;

		LIBCDATETIME_ATTRIBUTE_FALLTHROUGH;
		case LIBCDATETIME_MONTH_NOVEMBER:
			safe_day_of_year += 31;

		LIBCDATETIME_ATTRIBUTE_FALLTHROUGH;
		case LIBCDATETIME_MONTH_OCTOBER:
			safe_day_of_year += 30;

		LIBCDATETIME_ATTRIBUTE_FALLTHROUGH;
		case LIBCDATETIME_MONTH_SEPTEMBER:
			safe_day_of_year += 31;

		LIBCDATETIME_ATTRIBUTE_FALLTHROUGH;
		case LIBCDATETIME_MONTH_AUGUST:
			safe_day_of_year += 31;

		LIBCDATETIME_ATTRIBUTE_FALLTHROUGH;
		case LIBCDATETIME_MONTH_JULY:
			safe_day_of_year += 30;

		LIBCDATETIME_ATTRIBUTE_FALLTHROUGH;
		case LIBCDATETIME_MONTH_JUNE:
			safe_day_of_year += 31;

		LIBCDATETIME_ATTRIBUTE_FALLTHROUGH;
		case LIBCDATETIME_MONTH_MAY:
			safe_day_of_year += 30;

		LIBCDATETIME_ATTRIBUTE_FALLTHROUGH;
		case LIBCDATETIME_MONTH_APRIL:
			safe_day_of_year += 31;

		LIBCDATETIME_ATTRIBUTE_FALLTHROUGH;
		case LIBCDATETIME_MONTH_MARCH:
			if( libcdatetime_is_leap_year(
			     year ) != 0 )
			{
				safe_day_of_year += 29;
			}
			else
			{
				safe_day_of_year += 28;
			}

		LIBCDATETIME_ATTRIBUTE_FALLTHROUGH;
		case LIBCDATETIME_MONTH_FEBRUARY:
			safe_day_of_year += 31;

		LIBCDATETIME_ATTRIBUTE_FALLTHROUGH;
		default:
			safe_day_of_year += day_of_month - 1;
	}
	*day_of_year = safe_day_of_year;

	return( 1 );
}

