/* HASH CRC-32:0xf4d42bb1 */
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
#ifndef __local_re_compile_fastmap_defined
#define __local_re_compile_fastmap_defined
#include <__crt.h>
#include <bits/crt/regex.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(re_compile_fastmap) __ATTR_INOUT(1) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(re_compile_fastmap))(struct re_pattern_buffer *__self) {
	(void)__self;
	__COMPILER_IMPURE();
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_re_compile_fastmap_defined
#define __local___localdep_re_compile_fastmap_defined
#define __localdep_re_compile_fastmap __LIBC_LOCAL_NAME(re_compile_fastmap)
#endif /* !__local___localdep_re_compile_fastmap_defined */
#endif /* !__local_re_compile_fastmap_defined */
