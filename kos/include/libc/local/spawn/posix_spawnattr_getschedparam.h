/* HASH CRC-32:0xebc0879a */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_posix_spawnattr_getschedparam_defined
#define __local_posix_spawnattr_getschedparam_defined 1
#include <__crt.h>
#include <asm/crt/posix_spawn.h>
#ifdef __POSIX_SPAWN_USE_KOS
#include <bits/crt/posix_spawn.h>
#include <bits/os/sched.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_memcpy_defined
#define __local___localdep_memcpy_defined 1
#ifdef __CRT_HAVE_memcpy
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),void *,__NOTHROW_NCX,__localdep_memcpy,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_bytes),memcpy,(__dst,__src,__n_bytes))
#else /* __CRT_HAVE_memcpy */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcpy.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memcpy __LIBC_LOCAL_NAME(memcpy)
#endif /* !__CRT_HAVE_memcpy */
#endif /* !__local___localdep_memcpy_defined */
__LOCAL_LIBC(posix_spawnattr_getschedparam) __ATTR_NONNULL((1, 2)) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(posix_spawnattr_getschedparam))(struct __posix_spawnattr const *__restrict __attr, struct sched_param *__restrict __schedparam) {
	(__NAMESPACE_LOCAL_SYM __localdep_memcpy)(__schedparam, &__attr->__sp, sizeof(struct sched_param));
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_posix_spawnattr_getschedparam_defined
#define __local___localdep_posix_spawnattr_getschedparam_defined 1
#define __localdep_posix_spawnattr_getschedparam __LIBC_LOCAL_NAME(posix_spawnattr_getschedparam)
#endif /* !__local___localdep_posix_spawnattr_getschedparam_defined */
#else /* __POSIX_SPAWN_USE_KOS */
#undef __local_posix_spawnattr_getschedparam_defined
#endif /* !__POSIX_SPAWN_USE_KOS */
#endif /* !__local_posix_spawnattr_getschedparam_defined */
