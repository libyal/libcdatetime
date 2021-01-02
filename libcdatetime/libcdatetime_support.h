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

#if !defined( _LIBCDATETIME_SUPPORT_H )
#define _LIBCDATETIME_SUPPORT_H

#include <common.h>
#include <types.h>

#include "libcdatetime_extern.h"
#include "libcdatetime_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

#if !defined( HAVE_LOCAL_LIBCDATETIME )

LIBCDATETIME_EXTERN \
const char *libcdatetime_get_version(
             void );

#endif /* !defined( HAVE_LOCAL_LIBCDATETIME ) */

int libcdatetime_is_leap_year(
     uint16_t year );

int libcdatetime_get_days_in_month(
     uint8_t *days_in_month,
     uint16_t year,
     uint8_t month,
     libcerror_error_t **error );

int libcdatetime_get_day_of_year(
     uint16_t *day_of_year,
     uint16_t year,
     uint8_t month,
     uint8_t day_of_month,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBCDATETIME_SUPPORT_H ) */

