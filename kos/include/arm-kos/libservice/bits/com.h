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
#ifndef _ARM_KOS_LIBSERVICE_BITS_COM_H
#define _ARM_KOS_LIBSERVICE_BITS_COM_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#ifdef __CC__
__DECL_BEGIN

union service_com_retval {
	__UINT64_TYPE__ scr_64b; /* 64-bit return value */
	struct {
		__UINT32_TYPE__ scr_r0; /* Value for `r0' */
		__UINT32_TYPE__ scr_r1; /* Value for `r1' */
	};
};

#define SERVICE_COM_RETVAL_INIT(value) { (__UINT64_TYPE__)(value) }

__DECL_END
#endif /* __CC__ */


#endif /* !_ARM_KOS_LIBSERVICE_BITS_COM_H */
