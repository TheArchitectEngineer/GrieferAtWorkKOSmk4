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
/*!replace_with_include <asm/os/eventfd.h>*/
#ifndef _ASM_OS_KOS_EVENTFD_H
#define _ASM_OS_KOS_EVENTFD_H 1

#include <__stdinc.h>

/************************************************************************/
/* KOS/LINUX                                                            */
/************************************************************************/

/* Flags for `eventfd()'. */
#define __EFD_SEMAPHORE 0x0000001 /* Create a semaphore */
#define __EFD_NONBLOCK  0x0000800 /* Set the IO_NONBLOCK flag */
#define __EFD_CLOEXEC   0x0080000 /* Set the IO_CLOEXEC flag */
#ifdef __KOS__
#define __EFD_CLOFORK   0x1000000 /* Set the IO_CLOFORK flag */
#endif /* __KOS__ */

#endif /* !_ASM_OS_KOS_EVENTFD_H */
