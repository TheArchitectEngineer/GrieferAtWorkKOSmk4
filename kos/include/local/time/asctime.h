/* HASH CRC-32:0xd12d9a18 */
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
#ifndef __local_asctime_defined
#define __local_asctime_defined 1
#ifndef __LIBC_CTIME_BUFFER_DEFINED
#define __LIBC_CTIME_BUFFER_DEFINED 1
__NAMESPACE_LOCAL_BEGIN
#ifndef __NO_ATTR_WEAK
__INTERN __ATTR_UNUSED __ATTR_WEAK char __ctime_buf[26] = {0};
#elif !defined(__NO_ATTR_SELECTANY)
__INTERN __ATTR_UNUSED __ATTR_SELECTANY char __ctime_buf[26] = {0};
#else
__PRIVATE __ATTR_UNUSED char __ctime_buf[26] = {0};
#endif
__NAMESPACE_LOCAL_END
#endif /* !__LIBC_CTIME_BUFFER_DEFINED */
/* Dependency: "asctime_r" from "time" */
#ifndef ____localdep_asctime_r_defined
#define ____localdep_asctime_r_defined 1
#ifdef __CRT_HAVE_asctime_r
/* Return in BUF a string of the form "Day Mon dd hh:mm:ss yyyy\n"
 * that is the representation of TP in this format */
__CREDIRECT(__ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,__localdep_asctime_r,(__STRUCT_TM const *__restrict __tp, char __buf[26]),asctime_r,(__tp,__buf))
#else /* LIBC: asctime_r */
#include <local/time/asctime_r.h>
/* Return in BUF a string of the form "Day Mon dd hh:mm:ss yyyy\n"
 * that is the representation of TP in this format */
#define __localdep_asctime_r (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(asctime_r))
#endif /* asctime_r... */
#endif /* !____localdep_asctime_r_defined */

__NAMESPACE_LOCAL_BEGIN
/* Return a string of the form "Day Mon dd hh:mm:ss yyyy\n"
 * that is the representation of TP in this format */
__LOCAL_LIBC(asctime) __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(asctime))(struct __NAMESPACE_STD_SYM tm const *__tp) {
#line 590 "kos/src/libc/magic/time.c"
	return __localdep_asctime_r(__tp, __NAMESPACE_LOCAL_SYM __ctime_buf);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_asctime_defined */
