/* HASH CRC-32:0x61cacd4d */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
 *                                                                            *
 * This software is provided 'as-is', without any express or implied          *
 * warranty. In no event will the authors be held liable for any damages      *
 * arising from the use of this software.                                     *
 *                                                                            *
 * Permission is granted to anyone to use this software for any purpose,      *
 * including commercial applications, and to alter it and redistribute it     *
 * freely, subject to the following restrictions:                             *
 *                                                                            *
 * 1. The origin of this software must not be misrepresented; you must not    *
 *    claim that you wrote the original software. If you use this software    *
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_LOCALE_H
#define GUARD_LIBC_AUTO_LOCALE_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <locale.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> setlocale(3)
 * Get or set the current locale
 * @param: category: One of `LC_*'
 * @param: locale:   Name of the locale (e.g. "C")
 *                   When `NULL', don't change the locale.
 * @return: * :      The current locale set for `category'
 * @return: NULL:    Error */
INTDEF ATTR_IN_OPT(2) char *NOTHROW_NCX(LIBDCALL libd_setlocale)(int category, char const *locale);
/* >> newlocale(3)
 * @param: category_mask: Set of `LC_*_MASK' */
INTDEF ATTR_IN_OPT(2) locale_t NOTHROW_NCX(LIBDCALL libd_newlocale)(int category_mask, char const *locale, locale_t base);
/* >> duplocale(3)
 * Duplicate the given locale `dataset' */
INTDEF locale_t NOTHROW_NCX(LIBDCALL libd_duplocale)(locale_t dataset);
/* >> freelocale(3) */
INTDEF void NOTHROW_NCX(LIBDCALL libd_freelocale)(locale_t dataset);
/* >> uselocale(3)
 * Set the calling thread's current default locale to `dataset'
 * @param: dataset: NULL:             Don't change the calling thread's locale
 * @param: dataset: LC_GLOBAL_LOCALE: Use the global locale (s.a. `setlocale(3)')
 * @param: dataset: * :               The new locale to set
 * @return: NULL:             Error
 * @return: LC_GLOBAL_LOCALE: The calling thread uses the global locale (default)
 * @return: * :               The currently used locale */
INTDEF locale_t NOTHROW_NCX(LIBDCALL libd_uselocale)(locale_t dataset);
INTDEF int NOTHROW_NCX(LIBDCALL libd__configthreadlocale)(int flag);
INTDEF ATTR_IN_OPT(2) locale_t NOTHROW_NCX(LIBDCALL libd__create_locale)(int category, char const *locale);
INTDEF void NOTHROW_NCX(LIBDCALL libd__free_locale)(locale_t locale);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF WUNUSED char *NOTHROW_NCX(LIBCCALL libc__Getdays)(void);
INTDEF WUNUSED char16_t *NOTHROW_NCX(LIBDCALL libd__W_Getdays)(void);
INTDEF WUNUSED char32_t *NOTHROW_NCX(LIBKCALL libc__W_Getdays)(void);
INTDEF WUNUSED char *NOTHROW_NCX(LIBCCALL libc__Getmonths)(void);
INTDEF WUNUSED char16_t *NOTHROW_NCX(LIBDCALL libd__W_Getmonths)(void);
INTDEF WUNUSED char32_t *NOTHROW_NCX(LIBKCALL libc__W_Getmonths)(void);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(3) ATTR_IN(4) ATTR_OUTS(1, 2) size_t NOTHROW_NCX(LIBDCALL libd__Strftime)(char *buf, size_t bufsize, char const *format, struct tm const *tms, void *lc_time_arg);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_LOCALE_H */
