/* HASH CRC-32:0xc7804665 */
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
#ifndef __local_sigisemptyset_defined
#define __local_sigisemptyset_defined 1
#include <bits/sigset.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(sigisemptyset) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(sigisemptyset))(struct __sigset_struct const *__set) {
#line 305 "kos/src/libc/magic/signal.c"
	__SIZE_TYPE__ __i;
	for (__i = 0; __i < sizeof(struct __sigset_struct) / sizeof(__ULONGPTR_TYPE__); ++__i)
		if (__set->__val[__i])
			return 0;
	return 1;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_sigisemptyset_defined */
