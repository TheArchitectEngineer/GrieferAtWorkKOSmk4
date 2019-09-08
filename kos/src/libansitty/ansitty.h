/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBANSITTY_ANSITTY_H
#define GUARD_LIBANSITTY_ANSITTY_H 1

#include "api.h"

#include <hybrid/compiler.h>

#include <kos/types.h>

#include <libansitty/ansitty.h>

DECL_BEGIN

/* Initialize the given ANSI TTY
 * After calling this function, the caller is still responsible
 * to initialize at the very least `self->at_ops.ato_putc'. */
INTDEF NONNULL((1)) void CC
libansitty_init(struct ansitty *__restrict self,
                struct ansitty_operators const *__restrict ops);

/* Output a single utf-8 character to the given TTY */
INTDEF NONNULL((1)) void CC
libansitty_putc(struct ansitty *__restrict self, /*utf-8*/ char ch);

/* Output a single unicode character to the given TTY */
INTDEF NONNULL((1)) void CC
libansitty_putuni(struct ansitty *__restrict self, char32_t ch);

/* pformatprinter-compatible prototype for printing to an ANSI TTY
 * @param: arg: The `struct ansitty *' to which to print.
 * @return: * : Always re-return `(ssize_t)datalen' */
INTDEF NONNULL((1)) ssize_t __LIBCCALL
libansitty_printer(void *arg, char const *data, size_t datalen);

/* Translate a given unicode input character `ch' (which should originate form
 * the keyboard) into the sequence of bytes mandated by the code page that is
 * currently being used by the ansitty.
 * @return: * : The number of produced bytes (<= ANSITTY_TRANSLATE_BUFSIZE)
 * @return: 0 : The character cannot be represented in the current CP, and
 *              should be discarded. */
INTDEF NONNULL((1)) size_t CC
libansitty_translate(struct ansitty *__restrict self,
                     char *buf, char32_t ch);


DECL_END

#endif /* !GUARD_LIBANSITTY_ANSITTY_H */
