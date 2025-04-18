/* HASH CRC-32:0x1a8227e8 */
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
#ifndef __local_concat_copy2_defined
#define __local_concat_copy2_defined
#include <__crt.h>
#include <libc/template/libiberty_concat_ptr.h>
#ifdef __LOCAL_libiberty_concat_ptr
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_concat_vcopy_defined
#define __local___localdep_concat_vcopy_defined
__NAMESPACE_LOCAL_END
#include <libc/local/libiberty/concat_vcopy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_concat_vcopy __LIBC_LOCAL_NAME(concat_vcopy)
#endif /* !__local___localdep_concat_vcopy_defined */
__LOCAL_LIBC(concat_copy2) __ATTR_IN_OPT(1) char *
__NOTHROW_NCX(__VLIBCCALL __LIBC_LOCAL_NAME(concat_copy2))(char const *__first, ...) {
	char *__result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __first);
	__result = (__NAMESPACE_LOCAL_SYM __localdep_concat_vcopy)(__LOCAL_libiberty_concat_ptr, __first, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_concat_copy2_defined
#define __local___localdep_concat_copy2_defined
#define __localdep_concat_copy2 __LIBC_LOCAL_NAME(concat_copy2)
#endif /* !__local___localdep_concat_copy2_defined */
#else /* __LOCAL_libiberty_concat_ptr */
#undef __local_concat_copy2_defined
#endif /* !__LOCAL_libiberty_concat_ptr */
#endif /* !__local_concat_copy2_defined */
