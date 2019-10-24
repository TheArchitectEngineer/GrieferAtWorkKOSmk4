/* HASH CRC-32:0x6d0fe8b0 */
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
#ifndef __local_rawmemxlenq_defined
#define __local_rawmemxlenq_defined 1
/* Dependency: "rawmemxchrq" from "string" */
#ifndef ____localdep_rawmemxchrq_defined
#define ____localdep_rawmemxchrq_defined 1
#if defined(__CRT_HAVE_rawmemxchrq)
/* Same as `rawmemchrq', but search for non-matching locations. */
__CREDIRECT(__ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)),__UINT64_TYPE__ *,__NOTHROW_NCX,__localdep_rawmemxchrq,(void const *__restrict __haystack, __UINT64_TYPE__ __qword),rawmemxchrq,(__haystack,__qword))
#else /* LIBC: rawmemxchrq */
#include <local/string/rawmemxchrq.h>
/* Same as `rawmemchrq', but search for non-matching locations. */
#define __localdep_rawmemxchrq (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(rawmemxchrq))
#endif /* rawmemxchrq... */
#endif /* !____localdep_rawmemxchrq_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `rawmemlenq', but search for non-matching locations. */
__LOCAL_LIBC(rawmemxlenq) __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(rawmemxlenq))(void const *__restrict __haystack,
                                                         __UINT64_TYPE__ __qword) {
#line 2052 "kos/src/libc/magic/string.c"
	return (__SIZE_TYPE__)(__localdep_rawmemxchrq(__haystack, __qword) - (__UINT64_TYPE__ *)__haystack);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_rawmemxlenq_defined */
