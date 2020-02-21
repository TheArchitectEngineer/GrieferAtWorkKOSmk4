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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_CRED_H
#define GUARD_KERNEL_INCLUDE_SCHED_CRED_H 1

#include <kernel/compiler.h>
#include <kernel/types.h>
#include <sched/arch/cred.h>

/* Credential checking. */

DECL_BEGIN

#ifdef __CC__

/* TODO */
#define cred_getuid()    0
#define cred_getgid()    0
#define cred_geteuid()   0
#define cred_getegid()   0
#define cred_getsuid()   0
#define cred_getsgid()   0
#define cred_setuid(v)  (void)0
#define cred_setgid(v)  (void)0
#define cred_seteuid(v) (void)0
#define cred_setegid(v) (void)0
#define cred_setsuid(v) (void)0
#define cred_setsgid(v) (void)0

#define cred_isgroupmember(gid) 1


/* Credential assertion (throw an error if the caller doesn't have the required credential) */
struct vm;

#define cred_has_sys_admin() 1
#define cred_allow_ctty_stealing() cred_has_sys_admin()

/* Caller can directly access hardware I/O. */
FUNDEF void KCALL
cred_require_hwio(void)
		THROWS(E_INSUFFICIENT_RIGHTS);
FUNDEF void KCALL
cred_require_hwio_r(port_t from, port_t num)
		THROWS(E_INSUFFICIENT_RIGHTS);

/* Caller can mount/umount filesystems. */
#define cred_require_mount() (void)0

/* Caller can read from `target_vm' */
#define cred_require_vmread(target_vm) (void)0

/* Caller can write to `target_vm' */
#define cred_require_vmwrite(target_vm) (void)0

/* `CAP_SYS_RESOURCE' */
#define cred_require_resource() (void)0

/* `CAP_SYS_ADMIN' */
#define cred_require_sysadmin() (void)0

/* Caller is allowed to change DOS drive roots */
#define cred_require_driveroot() (void)0

/* Caller is allowed to trigger arbitrary debug traps */
#define cred_require_debugtrap() (void)0

/* Caller is allowed to use `MAP_UNINITIALIZED' */
#define cred_require_mmap_uninitialized() (void)0

/* TODO: Go through all system calls already defined and add credential checks where necessary. */
/* TODO: Add credential checks for individual ksysctl() and hop() commands */

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_CRED_H */
