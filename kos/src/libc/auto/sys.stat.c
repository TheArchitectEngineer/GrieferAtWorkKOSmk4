/* HASH CRC-32:0x1cf44f93 */
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
#ifndef GUARD_LIBC_AUTO_SYS_STAT_C
#define GUARD_LIBC_AUTO_SYS_STAT_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../user/sys.stat.h"

DECL_BEGIN

#ifndef __KERNEL__
#include <asm/os/stat.h>
/* >> mkfifo(2) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.modify") ATTR_IN(1) int
NOTHROW_RPC(LIBDCALL libd_mkfifo)(char const *fifoname,
                                  mode_t mode) {
	return libd_mknod(fifoname, mode | __S_IFIFO, 0);
}
#include <asm/os/stat.h>
/* >> mkfifo(2) */
INTERN ATTR_SECTION(".text.crt.fs.modify") ATTR_IN(1) int
NOTHROW_RPC(LIBCCALL libc_mkfifo)(char const *fifoname,
                                  mode_t mode) {
	return libc_mknod(fifoname, mode | __S_IFIFO, 0);
}
#include <asm/os/stat.h>
/* >> mkfifoat(2) */
INTERN ATTR_OPTIMIZE_SIZE ATTR_SECTION(".text.crt.dos.fs.modify") ATTR_IN(2) int
NOTHROW_RPC(LIBDCALL libd_mkfifoat)(fd_t dirfd,
                                    char const *fifoname,
                                    mode_t mode) {
	return libd_mknodat(dirfd, fifoname, mode | __S_IFIFO, 0);
}
#include <asm/os/stat.h>
/* >> mkfifoat(2) */
INTERN ATTR_SECTION(".text.crt.fs.modify") ATTR_IN(2) int
NOTHROW_RPC(LIBCCALL libc_mkfifoat)(fd_t dirfd,
                                    char const *fifoname,
                                    mode_t mode) {
	return libc_mknodat(dirfd, fifoname, mode | __S_IFIFO, 0);
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(DOS$mkfifo,libd_mkfifo,ATTR_IN(1),int,NOTHROW_RPC,LIBDCALL,(char const *fifoname, mode_t mode),(fifoname,mode));
DEFINE_PUBLIC_ALIAS_P(mkfifo,libc_mkfifo,ATTR_IN(1),int,NOTHROW_RPC,LIBCCALL,(char const *fifoname, mode_t mode),(fifoname,mode));
DEFINE_PUBLIC_ALIAS_P(DOS$mkfifoat,libd_mkfifoat,ATTR_IN(2),int,NOTHROW_RPC,LIBDCALL,(fd_t dirfd, char const *fifoname, mode_t mode),(dirfd,fifoname,mode));
DEFINE_PUBLIC_ALIAS_P(mkfifoat,libc_mkfifoat,ATTR_IN(2),int,NOTHROW_RPC,LIBCCALL,(fd_t dirfd, char const *fifoname, mode_t mode),(dirfd,fifoname,mode));
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_SYS_STAT_C */
