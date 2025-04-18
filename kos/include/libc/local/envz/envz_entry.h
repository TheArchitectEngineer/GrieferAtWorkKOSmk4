/* HASH CRC-32:0x3a345757 */
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
#ifndef __local_envz_entry_defined
#define __local_envz_entry_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_bcmpc_defined
#define __local___localdep_bcmpc_defined
#ifdef __CRT_HAVE_bcmpc
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_bcmpc,(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),bcmpc,(__s1,__s2,__elem_count,__elem_size))
#elif defined(__CRT_HAVE_memcmpc)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,__localdep_bcmpc,(void const *__s1, void const *__s2, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memcmpc,(__s1,__s2,__elem_count,__elem_size))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcmpc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_bcmpc __LIBC_LOCAL_NAME(memcmpc)
#endif /* !... */
#endif /* !__local___localdep_bcmpc_defined */
#ifndef __local___localdep_strend_defined
#define __local___localdep_strend_defined
#ifdef __CRT_HAVE_strend
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strend,(char const *__restrict __str),strend,(__str))
#else /* __CRT_HAVE_strend */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strend.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strend __LIBC_LOCAL_NAME(strend)
#endif /* !__CRT_HAVE_strend */
#endif /* !__local___localdep_strend_defined */
#ifndef __local___localdep_stroff_defined
#define __local___localdep_stroff_defined
#ifdef __CRT_HAVE_stroff
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_stroff,(char const *__restrict __haystack, int __needle),stroff,(__haystack,__needle))
#else /* __CRT_HAVE_stroff */
__NAMESPACE_LOCAL_END
#include <libc/local/string/stroff.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_stroff __LIBC_LOCAL_NAME(stroff)
#endif /* !__CRT_HAVE_stroff */
#endif /* !__local___localdep_stroff_defined */
__LOCAL_LIBC(envz_entry) __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(3) __ATTR_INS(1, 2) __ATTR_NONNULL((1)) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(envz_entry))(char const *__restrict __envz, __SIZE_TYPE__ __envz_len, char const *__restrict __name) {
	__SIZE_TYPE__ __namelen;
	char *__envz_end = (char *)(__envz + __envz_len);
	__namelen = (__NAMESPACE_LOCAL_SYM __localdep_stroff)(__name, '=');
	while (__envz < __envz_end) {
		if ((__NAMESPACE_LOCAL_SYM __localdep_bcmpc)(__envz, __name, __namelen, sizeof(char)) == 0 &&
		    (__envz[__namelen] == '\0' || __envz[__namelen] == '='))
			return (char *)__envz; /* Found it! */
		__envz = (__NAMESPACE_LOCAL_SYM __localdep_strend)(__envz) + 1;
	}
	return __NULLPTR;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_envz_entry_defined
#define __local___localdep_envz_entry_defined
#define __localdep_envz_entry __LIBC_LOCAL_NAME(envz_entry)
#endif /* !__local___localdep_envz_entry_defined */
#endif /* !__local_envz_entry_defined */
