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
/*!replace_with_include <bits/os/ucred.h>*/
#ifndef _BITS_OS_KOS_UCRED_H
#define _BITS_OS_KOS_UCRED_H 1

#include <__stdinc.h>

#include <bits/types.h>

#ifdef __CC__
__DECL_BEGIN

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("pid")
#pragma push_macro("uid")
#pragma push_macro("gid")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef pid
#undef uid
#undef gid

/* User visible structure for SCM_CREDENTIALS message */
struct ucred {
	__pid_t pid; /* PID of sending process. */
	__uid_t uid; /* UID of sending process. */
	__gid_t gid; /* GID of sending process. */
};

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("gid")
#pragma pop_macro("uid")
#pragma pop_macro("pid")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_OS_KOS_UCRED_H */
