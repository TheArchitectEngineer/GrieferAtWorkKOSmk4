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
/*!replace_with_include <bits/os/iovec.h>*/
#ifndef _BITS_OS_GENERIC_IOVEC_H
#define _BITS_OS_GENERIC_IOVEC_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#define __OFFSET_IOVEC_BASE 0
#define __OFFSET_IOVEC_LEN  __SIZEOF_POINTER__
#define __SIZEOF_IOVEC      (__SIZEOF_POINTER__ + __SIZEOF_SIZE_T__)
#define __ALIGNOFOF_IOVEC   __SIZEOF_POINTER__

#ifdef __CC__
__DECL_BEGIN

struct iovec /*[PREFIX(iov_)]*/ {
	void         *iov_base; /* Pointer to data. */
	__SIZE_TYPE__ iov_len;  /* Length of data. */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_OS_GENERIC_IOVEC_H */
