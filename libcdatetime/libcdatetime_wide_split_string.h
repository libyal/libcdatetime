/*
 * Split wide string functions
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

#if !defined( _LIBCDATETIME_INTERNAL_WIDE_SPLIT_STRING_H )
#define _LIBCDATETIME_INTERNAL_WIDE_SPLIT_STRING_H

#include <common.h>
#include <types.h>

#include "libcdatetime_extern.h"
#include "libcdatetime_libcerror.h"
#include "libcdatetime_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

#if defined( HAVE_WIDE_CHARACTER_TYPE )

typedef struct libcdatetime_internal_wide_split_string libcdatetime_internal_wide_split_string_t;

struct libcdatetime_internal_wide_split_string
{
	/* The number of string segments
	 */
	int number_of_segments;

	/* The string
	 */
	wchar_t *string;

	/* The string size
	 */
	size_t string_size;

	/* The segments
	 */
	wchar_t **segments;

	/* The segment sizes
	 */
	size_t *segment_sizes;
};

int libcdatetime_wide_split_string_initialize(
     libcdatetime_wide_split_string_t **split_string,
     const wchar_t *string,
     size_t string_size,
     int number_of_segments,
     libcerror_error_t **error );

int libcdatetime_wide_split_string_free(
     libcdatetime_wide_split_string_t **split_string,
     libcerror_error_t **error );

int libcdatetime_wide_split_string_get_string(
     libcdatetime_wide_split_string_t *split_string,
     wchar_t **string,
     size_t *string_size,
     libcerror_error_t **error );

int libcdatetime_wide_split_string_get_number_of_segments(
     libcdatetime_wide_split_string_t *split_string,
     int *number_of_segments,
     libcerror_error_t **error );

int libcdatetime_wide_split_string_get_segment_by_index(
     libcdatetime_wide_split_string_t *split_string,
     int segment_index,
     wchar_t **string_segment,
     size_t *string_segment_size,
     libcerror_error_t **error );

int libcdatetime_wide_split_string_set_segment_by_index(
     libcdatetime_wide_split_string_t *split_string,
     int segment_index,
     wchar_t *string_segment,
     size_t string_segment_size,
     libcerror_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( __cplusplus )
}
#endif

#endif

