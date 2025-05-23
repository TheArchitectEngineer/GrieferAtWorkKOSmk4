/* HASH CRC-32:0x4aa4bf0e */
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
#ifndef __local_qsort_defined
#define __local_qsort_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_qsort_r_defined
#define __local___localdep_qsort_r_defined
#ifdef __CRT_HAVE_qsort_r
__CREDIRECT_VOID(__ATTR_INOUT_OPT(1) __ATTR_NONNULL((4)),__NOTHROW_CB_NCX,__localdep_qsort_r,(void *__pbase, __SIZE_TYPE__ __item_count, __SIZE_TYPE__ __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b, void *__arg), void *__arg),qsort_r,(__pbase,__item_count,__item_size,__compar,__arg))
#elif defined(__CRT_HAVE__quicksort)
__CREDIRECT_VOID(__ATTR_INOUT_OPT(1) __ATTR_NONNULL((4)),__NOTHROW_CB_NCX,__localdep_qsort_r,(void *__pbase, __SIZE_TYPE__ __item_count, __SIZE_TYPE__ __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b, void *__arg), void *__arg),_quicksort,(__pbase,__item_count,__item_size,__compar,__arg))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/qsort_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_qsort_r __LIBC_LOCAL_NAME(qsort_r)
#endif /* !... */
#endif /* !__local___localdep_qsort_r_defined */
__NAMESPACE_LOCAL_END
#ifndef __LIBCCALL_CALLER_CLEANUP
#ifndef ____invoke_compare_helper_defined
__NAMESPACE_LOCAL_BEGIN
#define ____invoke_compare_helper_defined
__LOCAL_LIBC(__invoke_compare_helper) int
(__LIBCCALL __invoke_compare_helper)(void const *__a, void const *__b, void *__arg) {
	return (*(int (__LIBCCALL *)(void const *, void const *))__arg)(__a, __b);
}
__NAMESPACE_LOCAL_END
#endif /* !____invoke_compare_helper_defined */
#endif /* !__LIBCCALL_CALLER_CLEANUP */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(qsort) __ATTR_INOUT_OPT(1) __ATTR_NONNULL((4)) void
__NOTHROW_CB_NCX(__LIBCCALL __LIBC_LOCAL_NAME(qsort))(void *__pbase, __SIZE_TYPE__ __item_count, __SIZE_TYPE__ __item_size, int (__LIBCCALL *__compar)(void const *__a, void const *__b)) {
#ifdef __LIBCCALL_CALLER_CLEANUP
	(__NAMESPACE_LOCAL_SYM __localdep_qsort_r)(__pbase, __item_count, __item_size,
	        (int (__LIBCCALL *)(void const *, void const *, void *))(void *)__compar,
	        __NULLPTR);
#else /* __LIBCCALL_CALLER_CLEANUP */
	(__NAMESPACE_LOCAL_SYM __localdep_qsort_r)(__pbase, __item_count, __item_size,
	        &__NAMESPACE_LOCAL_SYM __invoke_compare_helper,
	        (void *)__compar);
#endif /* !__LIBCCALL_CALLER_CLEANUP */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_qsort_defined
#define __local___localdep_qsort_defined
#define __localdep_qsort __LIBC_LOCAL_NAME(qsort)
#endif /* !__local___localdep_qsort_defined */
#endif /* !__local_qsort_defined */
