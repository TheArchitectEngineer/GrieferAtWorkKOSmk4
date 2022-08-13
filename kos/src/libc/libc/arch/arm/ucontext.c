/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_LIBC_ARCH_ARM_UCONTEXT_C
#define GUARD_LIBC_LIBC_ARCH_ARM_UCONTEXT_C 1

#include "../../../api.h"
/**/

#include <kos/types.h>

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ucontext.h>
/**/

DECL_BEGIN

INTERN ATTR_SECTION(".text.crt.cpu.ucontext") NONNULL((1, 2)) void
NOTHROW_NCX(VLIBCCALL libc_makecontext)(ucontext_t *ucp,
                                        void (LIBKCALL *func)(void),
                                        __STDC_INT_AS_SIZE_T argc,
                                        ...) {
	CRT_UNIMPLEMENTEDF("[arm]::makecontext(%p, %p, %Iu)", ucp, func, argc);
}

DEFINE_PUBLIC_ALIAS(makecontext, libc_makecontext);

DECL_END

#endif /* GUARD_LIBC_LIBC_ARCH_ARM_UCONTEXT_C */
