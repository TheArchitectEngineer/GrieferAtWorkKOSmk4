/* HASH CRC-32:0x4fd4ddee */
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
#ifndef GUARD_LIBC_AUTO_SYS_VTIMES_H
#define GUARD_LIBC_AUTO_SYS_VTIMES_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <sys/vtimes.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> vtimes(3)
 * Return  timing information about the calling process
 * (in `*current'), or its children (in `*child'). This
 * is an old function which  you should no longer  use,
 * and  is implemented as a wrapper for `getrusage(2)'.
 *
 * @param: current: When non-NULL, fill with timings for the calling process. (s.a. `RUSAGE_SELF')
 * @param: child:   When non-NULL, fill with timings for child processes. (s.a. `RUSAGE_CHILDREN')
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
INTDEF int NOTHROW_NCX(LIBDCALL libd_vtimes)(struct vtimes *current, struct vtimes *child);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> vtimes(3)
 * Return  timing information about the calling process
 * (in `*current'), or its children (in `*child'). This
 * is an old function which  you should no longer  use,
 * and  is implemented as a wrapper for `getrusage(2)'.
 *
 * @param: current: When non-NULL, fill with timings for the calling process. (s.a. `RUSAGE_SELF')
 * @param: child:   When non-NULL, fill with timings for child processes. (s.a. `RUSAGE_CHILDREN')
 * @return: 0:  Success
 * @return: -1: Error (s.a. `errno') */
INTDEF int NOTHROW_NCX(LIBCCALL libc_vtimes)(struct vtimes *current, struct vtimes *child);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_SYS_VTIMES_H */
