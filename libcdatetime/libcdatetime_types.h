/*
 * The internal type definitions
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

#if !defined( _LIBCDATETIME_INTERNAL_TYPES_H )
#define _LIBCDATETIME_INTERNAL_TYPES_H

#include <common.h>
#include <types.h>

/* Define HAVE_LOCAL_LIBCDATETIME for local use of libcdatetime
 * The definitions in <libcdatetime/types.h> are copied here
 * for local use of libcdatetime
 */
#if defined( HAVE_LOCAL_LIBCDATETIME )

/* The following type definitions hide internal data structures
 */
#if defined( HAVE_DEBUG_OUTPUT ) && !defined( WINAPI )
typedef struct libcdatetime_elements {}		libcdatetime_elements_t;
typedef struct libcdatetime_timestamp {}	libcdatetime_timestamp_t;

#else
typedef intptr_t libcdatetime_elements_t;
typedef intptr_t libcdatetime_timestamp_t;

#endif /* defined( HAVE_DEBUG_OUTPUT ) && !defined( WINAPI ) */

#endif /* defined( HAVE_LOCAL_LIBCDATETIME ) */

#endif /* !defined( _LIBCDATETIME_INTERNAL_TYPES_H ) */

