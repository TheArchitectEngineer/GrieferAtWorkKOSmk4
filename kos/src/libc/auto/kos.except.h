/* HASH CRC-32:0xba925055 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_KOS_EXCEPT_H
#define GUARD_LIBC_AUTO_KOS_EXCEPT_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <kos/except.h>

DECL_BEGIN

/* Transform the given exception into a posix errno value */
INTDEF ATTR_PURE WUNUSED NONNULL((1)) errno_t NOTHROW_NCX(LIBKCALL libc_error_as_errno)(struct exception_data const *__restrict self);
/* Transform the given exception into a posix signal.
 * If doing this is possible, fill in `*result' and return `true'.
 * Otherwise, `*result' is left in an undefined state, and `false' is returned. */
INTDEF WUNUSED NONNULL((1, 2)) bool NOTHROW_NCX(LIBKCALL libc_error_as_signal)(struct exception_data const *__restrict self, struct __siginfo_struct *__restrict result);
/* Return the name of the given error, or `NULL` if unknown.
 * This name is the same as the `E_*` identifier.
 * E.g.: `error_name(ERROR_CODEOF(E_BADALLOC))` -> "E_BADALLOC" */
INTDEF ATTR_CONST WUNUSED char const *NOTHROW(LIBKCALL libc_error_name)(error_code_t code);

DECL_END

#endif /* !GUARD_LIBC_AUTO_KOS_EXCEPT_H */
