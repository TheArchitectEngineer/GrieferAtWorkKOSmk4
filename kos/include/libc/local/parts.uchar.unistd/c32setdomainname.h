/* HASH CRC-32:0x4c89f206 */
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
#ifndef __local_c32setdomainname_defined
#define __local_c32setdomainname_defined
#include <__crt.h>
#if (defined(__CRT_HAVE_setdomainname) || defined(__CRT_HAVE___setdomainname) || defined(__CRT_HAVE___libc_setdomainname)) && ((defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)) || defined(__CRT_HAVE_KOS$convert_wcstombsn) || defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc))
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_convert_c32tombsn_defined
#define __local___localdep_convert_c32tombsn_defined
#if defined(__CRT_HAVE_convert_wcstombsn) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_MALLOC __ATTR_WUNUSED,char *,__NOTHROW_NCX,__localdep_convert_c32tombsn,(__CHAR32_TYPE__ const *__restrict __str, __SIZE_TYPE__ __len, __SIZE_TYPE__ *__preslen),convert_wcstombsn,(__str,__len,__preslen))
#elif defined(__CRT_HAVE_KOS$convert_wcstombsn)
__CREDIRECT_KOS(__ATTR_MALLOC __ATTR_WUNUSED,char *,__NOTHROW_NCX,__localdep_convert_c32tombsn,(__CHAR32_TYPE__ const *__restrict __str, __SIZE_TYPE__ __len, __SIZE_TYPE__ *__preslen),convert_wcstombsn,(__str,__len,__preslen))
#elif (defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)) && __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/uchar/convert_wcstombsn.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_convert_c32tombsn __NAMESPACE_LOCAL_TYPEHAX(char *(__LIBKCALL*)(__CHAR32_TYPE__ const *__restrict,__SIZE_TYPE__,__SIZE_TYPE__ *),char *(__LIBKCALL&)(__CHAR32_TYPE__ const *__restrict,__SIZE_TYPE__,__SIZE_TYPE__ *),convert_wcstombsn)
#elif defined(__CRT_HAVE_format_aprintf_printer) || defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
__NAMESPACE_LOCAL_END
#include <libc/local/uchar/convert_c32tombsn.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_convert_c32tombsn __LIBC_LOCAL_NAME(convert_c32tombsn)
#else /* ... */
#undef __local___localdep_convert_c32tombsn_defined
#endif /* !... */
#endif /* !__local___localdep_convert_c32tombsn_defined */
#ifndef __local___localdep_free_defined
#define __local___localdep_free_defined
#if __has_builtin(__builtin_free) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_free)
__CEIREDIRECT(,void,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,{ __builtin_free(__mallptr); })
#elif defined(__CRT_HAVE_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),free,(__mallptr))
#elif defined(__CRT_HAVE_cfree)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),cfree,(__mallptr))
#elif defined(__CRT_HAVE___libc_free)
__CREDIRECT_VOID(,__NOTHROW_NCX,__localdep_free,(void *__mallptr),__libc_free,(__mallptr))
#else /* ... */
#undef __local___localdep_free_defined
#endif /* !... */
#endif /* !__local___localdep_free_defined */
#ifndef __local___localdep_setdomainname_defined
#define __local___localdep_setdomainname_defined
#ifdef __CRT_HAVE_setdomainname
__CREDIRECT(__ATTR_ACCESS_ROS(1, 2),int,__NOTHROW_NCX,__localdep_setdomainname,(char const *__name, __SIZE_TYPE__ __len),setdomainname,(__name,__len))
#elif defined(__CRT_HAVE___setdomainname)
__CREDIRECT(__ATTR_ACCESS_ROS(1, 2),int,__NOTHROW_NCX,__localdep_setdomainname,(char const *__name, __SIZE_TYPE__ __len),__setdomainname,(__name,__len))
#elif defined(__CRT_HAVE___libc_setdomainname)
__CREDIRECT(__ATTR_ACCESS_ROS(1, 2),int,__NOTHROW_NCX,__localdep_setdomainname,(char const *__name, __SIZE_TYPE__ __len),__libc_setdomainname,(__name,__len))
#else /* ... */
#undef __local___localdep_setdomainname_defined
#endif /* !... */
#endif /* !__local___localdep_setdomainname_defined */
__LOCAL_LIBC(c32setdomainname) __ATTR_NONNULL((1)) int
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(c32setdomainname))(__CHAR32_TYPE__ const *__name, __SIZE_TYPE__ __len) {
	int __result;
	char *__utf8_name;
	__SIZE_TYPE__ __utf8_len;
	__utf8_name = (__NAMESPACE_LOCAL_SYM __localdep_convert_c32tombsn)(__name, __len, &__utf8_len);
	if __unlikely(!__utf8_name)
		return -1;
	__result = (__NAMESPACE_LOCAL_SYM __localdep_setdomainname)(__utf8_name, __utf8_len);
#if defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
	(__NAMESPACE_LOCAL_SYM __localdep_free)(__utf8_name);
#endif /* __CRT_HAVE_free || __CRT_HAVE_cfree || __CRT_HAVE___libc_free */
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32setdomainname_defined
#define __local___localdep_c32setdomainname_defined
#define __localdep_c32setdomainname __LIBC_LOCAL_NAME(c32setdomainname)
#endif /* !__local___localdep_c32setdomainname_defined */
#else /* (__CRT_HAVE_setdomainname || __CRT_HAVE___setdomainname || __CRT_HAVE___libc_setdomainname) && ((__CRT_HAVE_convert_wcstombsn && __SIZEOF_WCHAR_T__ == 4 && __LIBCCALL_IS_LIBKCALL) || __CRT_HAVE_KOS$convert_wcstombsn || __CRT_HAVE_format_aprintf_printer || __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc) */
#undef __local_c32setdomainname_defined
#endif /* (!__CRT_HAVE_setdomainname && !__CRT_HAVE___setdomainname && !__CRT_HAVE___libc_setdomainname) || ((!__CRT_HAVE_convert_wcstombsn || __SIZEOF_WCHAR_T__ != 4 || !__LIBCCALL_IS_LIBKCALL) && !__CRT_HAVE_KOS$convert_wcstombsn && !__CRT_HAVE_format_aprintf_printer && !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc) */
#endif /* !__local_c32setdomainname_defined */
