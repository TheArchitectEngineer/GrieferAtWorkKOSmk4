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
#ifndef _I386_KOS_BIT_SIGVAL64_H
#define _I386_KOS_BIT_SIGVAL64_H 1

#include <__stdinc.h>

#include <hybrid/__pointer.h>
#include <hybrid/host.h>
#include <hybrid/typecore.h>

__SYSDECL_BEGIN

#ifdef __x86_64__
#ifndef __sigval_t_defined
#define __sigval_t_defined 1
#define __SIZEOF_SIGVAL  __SIZEOF_SIGVAL64
#define __ALIGNOF_SIGVAL __ALIGNOF_SIGVAL64
#define __sigval_defined 1
#define sigval64        sigval
#define sigval64_t      sigval_t
#endif /* !__sigval_t_defined */
#endif /* __x86_64__ */


#define __SIZEOF_SIGVAL64 8
#define __ALIGNOF_SIGVAL64 __ALIGNOF_INT64__
#ifdef __CC__
/* Type for data associated with a signal. */
typedef union sigval64 /*[PREFIX(sival_)]*/ {
	__INT64_TYPE__       sival_int;
	__HYBRID_PTR64(void) sival_ptr;
} sigval64_t;
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_I386_KOS_BIT_SIGVAL64_H */
