/* HASH CRC-32:0x8621443b */
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
#ifndef __local__mbsnset_l_defined
#define __local__mbsnset_l_defined
#include <__crt.h>
#if defined(__CRT_HAVE__ismbblead_l) || defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep__ismbblead_l_defined
#define __local___localdep__ismbblead_l_defined
#ifdef __CRT_HAVE__ismbblead_l
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep__ismbblead_l,(unsigned int __ch, __locale_t __locale),_ismbblead_l,(__ch,__locale))
#elif defined(__CRT_HAVE__mbctype) || defined(__CRT_HAVE___p__mbctype)
__NAMESPACE_LOCAL_END
#include <libc/local/mbctype/_ismbblead_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep__ismbblead_l __LIBC_LOCAL_NAME(_ismbblead_l)
#else /* ... */
#undef __local___localdep__ismbblead_l_defined
#endif /* !... */
#endif /* !__local___localdep__ismbblead_l_defined */
#ifndef __local___localdep_strnset_defined
#define __local___localdep_strnset_defined
#ifdef __CRT_HAVE_strnset
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INOUTS(1, 3) __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_strnset,(char *__restrict __str, int __ch, __SIZE_TYPE__ __maxlen),strnset,(__str,__ch,__maxlen))
#elif defined(__CRT_HAVE__strnset)
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_INOUTS(1, 3) __ATTR_NONNULL((1)),char *,__NOTHROW_NCX,__localdep_strnset,(char *__restrict __str, int __ch, __SIZE_TYPE__ __maxlen),_strnset,(__str,__ch,__maxlen))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strnset.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strnset __LIBC_LOCAL_NAME(strnset)
#endif /* !... */
#endif /* !__local___localdep_strnset_defined */
__LOCAL_LIBC(_mbsnset_l) __ATTR_RETNONNULL __ATTR_INOUT(1) unsigned char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_mbsnset_l))(unsigned char *__buf, unsigned int __ch, __SIZE_TYPE__ __max_chars, __locale_t __locale) {
	unsigned char *__iter, __lob, __hib;
	__lob = (__ch & 0xff);
	__hib = (__ch & 0xff00) >> 8;
	if (!__hib || !(__NAMESPACE_LOCAL_SYM __localdep__ismbblead_l)(__lob, __locale))
		return (unsigned char *)(__NAMESPACE_LOCAL_SYM __localdep_strnset)((char *)__buf, (int)__lob, __max_chars);
	for (__iter = __buf; __max_chars && *__iter; --__max_chars) {
		*__iter++ = __lob;
		if (*__iter == 0) {
			/* Undocumented, but disassembly shows that this is also what DOS does. */
			__iter[-1] = ' ';
			break;
		}
		*__iter++ = __hib;
	}
	return __buf;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__mbsnset_l_defined
#define __local___localdep__mbsnset_l_defined
#define __localdep__mbsnset_l __LIBC_LOCAL_NAME(_mbsnset_l)
#endif /* !__local___localdep__mbsnset_l_defined */
#else /* __CRT_HAVE__ismbblead_l || __CRT_HAVE__mbctype || __CRT_HAVE___p__mbctype */
#undef __local__mbsnset_l_defined
#endif /* !__CRT_HAVE__ismbblead_l && !__CRT_HAVE__mbctype && !__CRT_HAVE___p__mbctype */
#endif /* !__local__mbsnset_l_defined */
