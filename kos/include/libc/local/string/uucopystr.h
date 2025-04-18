/* HASH CRC-32:0xe20fba8f */
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
#ifndef __local_uucopystr_defined
#define __local_uucopystr_defined
#include <__crt.h>
#if defined(__KOS__) && defined(__cplusplus) && defined(__CRT_HAVE_except_nesting_begin) && defined(__CRT_HAVE_except_nesting_end)
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_except_as_errno_defined
#define __local___localdep_except_as_errno_defined
#ifdef __CRT_HAVE_except_as_errno
__NAMESPACE_LOCAL_END
#include <bits/types.h>
#include <kos/bits/exception_data.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_CREDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1),__errno_t,__NOTHROW_NCX,__LIBKCALL,__localdep_except_as_errno,(struct exception_data const *__restrict __self),except_as_errno,(__self))
#else /* __CRT_HAVE_except_as_errno */
__NAMESPACE_LOCAL_END
#include <libc/local/kos.except/except_as_errno.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_except_as_errno __LIBC_LOCAL_NAME(except_as_errno)
#endif /* !__CRT_HAVE_except_as_errno */
#endif /* !__local___localdep_except_as_errno_defined */
#ifndef __local___localdep_except_data_defined
#define __local___localdep_except_data_defined
#ifdef __CRT_HAVE_except_data
__NAMESPACE_LOCAL_END
#include <kos/bits/exception_data.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_CREDIRECT(__LIBC,__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,struct exception_data *,__NOTHROW,__LIBKCALL,__localdep_except_data,(void),except_data,())
#else /* __CRT_HAVE_except_data */
__NAMESPACE_LOCAL_END
#include <kos/bits/fastexcept.h>
__NAMESPACE_LOCAL_BEGIN
#ifdef __arch_except_data
__NAMESPACE_LOCAL_END
#include <libc/local/kos.except/except_data.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_except_data __LIBC_LOCAL_NAME(except_data)
#else /* __arch_except_data */
#undef __local___localdep_except_data_defined
#endif /* !__arch_except_data */
#endif /* !__CRT_HAVE_except_data */
#endif /* !__local___localdep_except_data_defined */
__NAMESPACE_LOCAL_END
#include <kos/except.h>
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(uucopystr) __ATTR_IN_OPT(1) __ATTR_OUT_OPT(2) __STDC_INT_AS_SSIZE_T
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(uucopystr))(void const *__restrict __src, void *__restrict __dst, __SIZE_TYPE__ __maxlen) {
	__SIZE_TYPE__ __result = 0;
	NESTED_TRY {
		__BYTE_TYPE__ const *__s_ptr = (__BYTE_TYPE__ const *)__src;
		__BYTE_TYPE__ *__d_ptr = (__BYTE_TYPE__ *)__dst;
		for (;;) {
			char __ch;
			if __unlikely(__maxlen == 0) {
#ifdef __ENAMETOOLONG
				return __libc_seterrno(__ENAMETOOLONG);
#else /* __ENAMETOOLONG */
				return __libc_seterrno(1);
#endif /* !__ENAMETOOLONG */
			}
			--__maxlen;
			__COMPILER_BARRIER();
			__ch = *__s_ptr++;
			*__d_ptr++ = __ch;
			__COMPILER_BARRIER();
			++__result;
			if (__ch == '\0')
				break;
		}
	} EXCEPT {
#if defined(__CRT_HAVE_except_data) || defined(__arch_except_data)
		return __libc_seterrno((__NAMESPACE_LOCAL_SYM __localdep_except_as_errno)((__NAMESPACE_LOCAL_SYM __localdep_except_data)()));
#elif defined(__EFAULT)
		return __libc_seterrno(__EFAULT);
#else /* ... */
		return __libc_seterrno(1);
#endif /* !... */
	}
	return (__STDC_INT_AS_SSIZE_T)__result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_uucopystr_defined
#define __local___localdep_uucopystr_defined
#define __localdep_uucopystr __LIBC_LOCAL_NAME(uucopystr)
#endif /* !__local___localdep_uucopystr_defined */
#else /* __KOS__ && __cplusplus && __CRT_HAVE_except_nesting_begin && __CRT_HAVE_except_nesting_end */
#undef __local_uucopystr_defined
#endif /* !__KOS__ || !__cplusplus || !__CRT_HAVE_except_nesting_begin || !__CRT_HAVE_except_nesting_end */
#endif /* !__local_uucopystr_defined */
