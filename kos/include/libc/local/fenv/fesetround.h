/* HASH CRC-32:0x23ca143f */
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
#ifndef __local_fesetround_defined
#define __local_fesetround_defined 1
#include <__crt.h>
#include <bits/crt/fenv-inline.h>
__NAMESPACE_LOCAL_BEGIN
/* Set the current rounding direction
 * @param: rounding_direction: One of...
 *             ... `FE_TONEAREST':  round()
 *             ... `FE_DOWNWARD':   floor()
 *             ... `FE_UPWARD':     ceil()
 *             ... `FE_TOWARDZERO': trunc() */
__LOCAL_LIBC(fesetround) int
__NOTHROW(__LIBCCALL __LIBC_LOCAL_NAME(fesetround))(int __rounding_direction) {
	return __inline_fesetround(__rounding_direction);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_fesetround_defined
#define __local___localdep_fesetround_defined 1
#define __localdep_fesetround __LIBC_LOCAL_NAME(fesetround)
#endif /* !__local___localdep_fesetround_defined */
#endif /* !__local_fesetround_defined */
