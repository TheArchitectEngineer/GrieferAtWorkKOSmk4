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
/*!included_by <pthread.h>*/
#ifndef _BITS_CRT_PTHREADTYPESIZES_H
#define _BITS_CRT_PTHREADTYPESIZES_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#if __SIZEOF_POINTER__ == 8
#define __SIZEOF_PTHREAD_ATTR_T        56
#define __SIZEOF_PTHREAD_MUTEX_T       40
#define __SIZEOF_PTHREAD_MUTEXATTR_T   4
#define __SIZEOF_PTHREAD_COND_T        48
#define __SIZEOF_PTHREAD_CONDATTR_T    4
#define __SIZEOF_PTHREAD_RWLOCK_T      56
#define __SIZEOF_PTHREAD_RWLOCKATTR_T  8
#define __SIZEOF_PTHREAD_BARRIER_T     32
#define __SIZEOF_PTHREAD_BARRIERATTR_T 4
#else /* __SIZEOF_POINTER__ == 8 */
#define __SIZEOF_PTHREAD_ATTR_T        32
#define __SIZEOF_PTHREAD_MUTEX_T       24
#define __SIZEOF_PTHREAD_MUTEXATTR_T   4
#define __SIZEOF_PTHREAD_COND_T        48
#define __SIZEOF_PTHREAD_CONDATTR_T    4
#define __SIZEOF_PTHREAD_RWLOCK_T      32
#define __SIZEOF_PTHREAD_RWLOCKATTR_T  8
#define __SIZEOF_PTHREAD_BARRIER_T     20
#define __SIZEOF_PTHREAD_BARRIERATTR_T 4
#endif /* __SIZEOF_POINTER__ != 8 */

#define __SIZEOF_PTHREAD_T          __SIZEOF_POINTER__
#define __SIZEOF_PTHREAD_KEY_T      4
#define __SIZEOF_PTHREAD_ONCE_T     4
#define __SIZEOF_PTHREAD_SPINLOCK_T 4

#endif /* !_BITS_CRT_PTHREADTYPESIZES_H */
