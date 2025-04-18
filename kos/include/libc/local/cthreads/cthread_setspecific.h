/* HASH CRC-32:0xa175973c */
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
#ifndef __local_cthread_setspecific_defined
#define __local_cthread_setspecific_defined
#include <__crt.h>
#if defined(__CRT_HAVE_pthread_setspecific) || defined(__CRT_HAVE_thr_setspecific) || defined(__CRT_HAVE___pthread_setspecific)
#include <bits/crt/pthreadtypes.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_pthread_setspecific_defined
#define __local___localdep_pthread_setspecific_defined
#ifdef __CRT_HAVE_pthread_setspecific
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_ACCESS_NONE(2),__errno_t,__NOTHROW_NCX,__localdep_pthread_setspecific,(__pthread_key_t __key, void const *__pointer),pthread_setspecific,(__key,__pointer))
#elif defined(__CRT_HAVE_thr_setspecific)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_ACCESS_NONE(2),__errno_t,__NOTHROW_NCX,__localdep_pthread_setspecific,(__pthread_key_t __key, void const *__pointer),thr_setspecific,(__key,__pointer))
#elif defined(__CRT_HAVE___pthread_setspecific)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_ACCESS_NONE(2),__errno_t,__NOTHROW_NCX,__localdep_pthread_setspecific,(__pthread_key_t __key, void const *__pointer),__pthread_setspecific,(__key,__pointer))
#else /* ... */
#undef __local___localdep_pthread_setspecific_defined
#endif /* !... */
#endif /* !__local___localdep_pthread_setspecific_defined */
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(cthread_setspecific) __ATTR_ACCESS_NONE(2) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(cthread_setspecific))(__pthread_key_t __key, void *___value) {
	__errno_t __error = (__NAMESPACE_LOCAL_SYM __localdep_pthread_setspecific)((__pthread_key_t)__key, ___value);
	return __error == 0 ? 0 : -1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_cthread_setspecific_defined
#define __local___localdep_cthread_setspecific_defined
#define __localdep_cthread_setspecific __LIBC_LOCAL_NAME(cthread_setspecific)
#endif /* !__local___localdep_cthread_setspecific_defined */
#else /* __CRT_HAVE_pthread_setspecific || __CRT_HAVE_thr_setspecific || __CRT_HAVE___pthread_setspecific */
#undef __local_cthread_setspecific_defined
#endif /* !__CRT_HAVE_pthread_setspecific && !__CRT_HAVE_thr_setspecific && !__CRT_HAVE___pthread_setspecific */
#endif /* !__local_cthread_setspecific_defined */
