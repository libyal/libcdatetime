/*
 * Timestamp functions
 *
 * Copyright (C) 2006-2015, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBCDATETIME_INTERNAL_TIMESTAMP_H )
#define _LIBCDATETIME_INTERNAL_TIMESTAMP_H

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

typedef struct libcdatetime_internal_timestamp libcdatetime_internal_timestamp_t;

struct libcdatetime_internal_timestamp
{
#if defined( WINAPI ) && ( WINVER >= 0x0500 )
	/* The filetime timestamp
	 */
	FILETIME filetime;

#elif defined( WINAPI )

/* TODO */
#error WINAPI timestamp type for Windows NT4 or earlier NOT implemented yet

#else
	/* The time
	 */
	time_t time;
#endif
};

LIBCDATETIME_EXTERN \
int libcdatetime_timestamp_initialize(
     libcdatetime_timestamp_t **timestamp,
     libcerror_error_t **error );

LIBCDATETIME_EXTERN \
int libcdatetime_timestamp_free(
     libcdatetime_timestamp_t **timestamp,
     libcerror_error_t **error );

LIBCDATETIME_EXTERN \
int libcdatetime_timestamp_copy(
     libcdatetime_timestamp_t *destination_timestamp,
     const libcdatetime_timestamp_t *source_timestamp,
     libcerror_error_t **error );

LIBCDATETIME_EXTERN \
int libcdatetime_timestamp_set_current_time(
     libcdatetime_timestamp_t *timestamp,
     libcerror_error_t **error );

LIBCDATETIME_EXTERN \
int libcdatetime_timestamp_get_delta_in_seconds(
     libcdatetime_timestamp_t *first_timestamp,
     libcdatetime_timestamp_t *second_timestamp,
     int64_t *number_of_seconds,
     libcerror_error_t **error );

LIBCDATETIME_EXTERN \
int libcdatetime_timestamp_get_string_size(
     libcdatetime_timestamp_t *timestamp,
     size_t *string_size,
     uint32_t string_format_flags,
     libcerror_error_t **error );

LIBCDATETIME_EXTERN \
int libcdatetime_timestamp_copy_to_string(
     libcdatetime_timestamp_t *timestamp,
     uint8_t *string,
     size_t string_size,
     uint32_t string_format_flags,
     libcerror_error_t **error );

LIBCDATETIME_EXTERN \
int libcdatetime_timestamp_copy_to_string_with_index(
     libcdatetime_timestamp_t *timestamp,
     uint8_t *string,
     size_t string_size,
     size_t *string_index,
     uint32_t string_format_flags,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

