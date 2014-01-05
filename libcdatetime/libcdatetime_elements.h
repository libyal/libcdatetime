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

#if !defined( _LIBCDATETIME_INTERNAL_ELEMENTS_H )
#define _LIBCDATETIME_INTERNAL_ELEMENTS_H

#include <common.h>
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

#include "libcdatetime_extern.h"
#include "libcdatetime_libcerror.h"
#include "libcdatetime_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

enum LIBCDATETIME_ELEMENTS_MODES
{
	LIBCDATETIME_ELEMENTS_MODE_DATE_TIME_IN_UTC,
	LIBCDATETIME_ELEMENTS_MODE_DATE_TIME_IN_LOCALTIME,
	LIBCDATETIME_ELEMENTS_MODE_DURATION,
};

typedef struct libcdatetime_internal_elements libcdatetime_internal_elements_t;

struct libcdatetime_internal_elements
{
#if defined( WINAPI ) && ( WINVER >= 0x0500 )
	/* The filetime
	 */
	FILETIME filetime;

	/* The systemtime
	 */
	SYSTEMTIME systemtime;

#elif defined( WINAPI )

/* TODO */
#error WINAPI date and time elements type for Windows NT4 or earlier NOT implemented yet

#else
	/* The time
	 */
	time_t time;

	/* The struct tm
	 */
	struct tm tm;
#endif

	/* Value to indicate how the time elements are used
	 * e.g. to store a date time in UCT or localtime or a duration
	 */
	uint8_t mode;
};

LIBCDATETIME_EXTERN \
int libcdatetime_elements_initialize(
     libcdatetime_elements_t **elements,
     libcerror_error_t **error );

LIBCDATETIME_EXTERN \
int libcdatetime_elements_free(
     libcdatetime_elements_t **elements,
     libcerror_error_t **error );

LIBCDATETIME_EXTERN \
int libcdatetime_elements_copy(
     libcdatetime_elements_t *destination_elements,
     const libcdatetime_elements_t *source_elements,
     libcerror_error_t **error );

LIBCDATETIME_EXTERN \
int libcdatetime_elements_get_year(
     libcdatetime_elements_t *elements,
     uint16_t *year,
     libcerror_error_t **error );

LIBCDATETIME_EXTERN \
int libcdatetime_elements_get_day_of_year(
     libcdatetime_elements_t *elements,
     uint16_t *day_of_year,
     libcerror_error_t **error );

LIBCDATETIME_EXTERN \
int libcdatetime_elements_get_month(
     libcdatetime_elements_t *elements,
     uint8_t *month,
     libcerror_error_t **error );

LIBCDATETIME_EXTERN \
int libcdatetime_elements_get_day_of_month(
     libcdatetime_elements_t *elements,
     uint8_t *day_of_month,
     libcerror_error_t **error );

LIBCDATETIME_EXTERN \
int libcdatetime_elements_get_date_values(
     libcdatetime_elements_t *elements,
     uint16_t *year,
     uint8_t *month,
     uint8_t *day_of_month,
     libcerror_error_t **error );

LIBCDATETIME_EXTERN \
int libcdatetime_elements_get_hours(
     libcdatetime_elements_t *elements,
     uint8_t *hours,
     libcerror_error_t **error );

LIBCDATETIME_EXTERN \
int libcdatetime_elements_get_minutes(
     libcdatetime_elements_t *elements,
     uint8_t *minutes,
     libcerror_error_t **error );

LIBCDATETIME_EXTERN \
int libcdatetime_elements_get_seconds(
     libcdatetime_elements_t *elements,
     uint8_t *seconds,
     libcerror_error_t **error );

LIBCDATETIME_EXTERN \
int libcdatetime_elements_get_milli_seconds(
     libcdatetime_elements_t *elements,
     uint16_t *milli_seconds,
     libcerror_error_t **error );

LIBCDATETIME_EXTERN \
int libcdatetime_elements_get_micro_seconds(
     libcdatetime_elements_t *elements,
     uint16_t *micro_seconds,
     libcerror_error_t **error );

LIBCDATETIME_EXTERN \
int libcdatetime_elements_get_nano_seconds(
     libcdatetime_elements_t *elements,
     uint16_t *nano_seconds,
     libcerror_error_t **error );

LIBCDATETIME_EXTERN \
int libcdatetime_elements_get_time_values(
     libcdatetime_elements_t *elements,
     uint8_t *hours,
     uint8_t *minutes,
     uint8_t *secons,
     libcerror_error_t **error );

#if defined( WINAPI ) && ( WINVER >= 0x0500 )
int libcdatetime_internal_elements_set_from_filetime_utc(
     libcdatetime_internal_elements_t *internal_elements,
     FILETIME *filetime,
     libcerror_error_t **error );
#endif

#if !defined( WINAPI ) && defined( HAVE_TIME ) && ( defined( HAVE_GMTIME ) || defined( HAVE_GMTIME_R ) )
int libcdatetime_internal_elements_set_from_time_utc(
     libcdatetime_internal_elements_t *internal_elements,
     time_t *time,
     libcerror_error_t **error );
#endif

#if !defined( WINAPI ) && defined( HAVE_TIME ) && ( defined( HAVE_LOCALTIME ) || defined( HAVE_LOCALTIME_R ) )
int libcdatetime_internal_elements_set_from_time_localtime(
     libcdatetime_internal_elements_t *internal_elements,
     time_t *time,
     libcerror_error_t **error );
#endif

LIBCDATETIME_EXTERN \
int libcdatetime_elements_set_current_time_utc(
     libcdatetime_elements_t *elements,
     libcerror_error_t **error );

LIBCDATETIME_EXTERN \
int libcdatetime_elements_set_current_time_localtime(
     libcdatetime_elements_t *elements,
     libcerror_error_t **error );

LIBCDATETIME_EXTERN \
int libcdatetime_elements_get_delta_in_seconds(
     libcdatetime_elements_t *first_elements,
     libcdatetime_elements_t *second_elements,
     int64_t *number_of_seconds,
     libcerror_error_t **error );

LIBCDATETIME_EXTERN \
int libcdatetime_elements_set_from_delta_in_seconds(
     libcdatetime_elements_t *elements,
     int64_t number_of_seconds,
     libcerror_error_t **error );

LIBCDATETIME_EXTERN \
int libcdatetime_elements_get_string_size(
     libcdatetime_elements_t *elements,
     size_t *string_size,
     uint32_t string_format_flags,
     libcerror_error_t **error );

LIBCDATETIME_EXTERN \
int libcdatetime_elements_copy_to_string(
     libcdatetime_elements_t *elements,
     uint8_t *string,
     size_t string_size,
     uint32_t string_format_flags,
     libcerror_error_t **error );

LIBCDATETIME_EXTERN \
int libcdatetime_elements_copy_to_string_with_index(
     libcdatetime_elements_t *elements,
     uint8_t *string,
     size_t string_size,
     size_t *string_index,
     uint32_t string_format_flags,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

