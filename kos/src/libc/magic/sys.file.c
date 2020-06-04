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

%[define_replacement(fd_t = __fd_t)]

%{
#include <fcntl.h>
#include <bits/types.h>

#ifndef SEEK_SET
#   define SEEK_SET  0 /* Seek from beginning of file.  */
#   define SEEK_CUR  1 /* Seek from current position.  */
#   define SEEK_END  2 /* Seek from end of file.  */
#if defined(__USE_GNU) && (defined(__CRT_KOS) || defined(__CRT_GLC))
#   define SEEK_DATA 3 /* Seek to next data.  */
#   define SEEK_HOLE 4 /* Seek to next hole.  */
#endif /* __USE_GNU && (__CRT_KOS || __CRT_GLC) */
#endif

#ifndef L_SET
#define L_SET  SEEK_SET /* Seek from beginning of file. */
#define L_CURR SEEK_CUR /* Seek from current position. */
#define L_INCR SEEK_CUR /* Seek from current position. */
#define L_XTND SEEK_END /* Seek from end of file. */
#endif /* !L_SET */

#ifndef LOCK_SH
#define LOCK_SH        1 /* Shared lock. */
#define LOCK_EX        2 /* Exclusive lock. */
#define LOCK_NB        4 /* Or'd with one of the above to prevent blocking. */
#define LOCK_UN        8 /* Remove lock. */
#define __LOCK_ATOMIC 16 /* Atomic update.  */
#endif /* !LOCK_SH */

#ifdef __CC__
__SYSDECL_BEGIN

}

%/* Apply or remove an advisory lock, according to OPERATION, on the file FD refers to.  */
[[cp]] flock:($fd_t fd, int operation) -> int;

%{

__SYSDECL_END
#endif /* __CC__ */

}