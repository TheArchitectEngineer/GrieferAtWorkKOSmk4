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
#ifndef _BITS_SIGNALFD_H
#define _BITS_SIGNALFD_H 1

#include <__stdinc.h>

__DECL_BEGIN

/* Flags for signalfd. */
/*[[[enum]]]*/
#ifdef __CC__
enum {
	SFD_NONBLOCK = 0x00800,
	SFD_CLOEXEC  = 0x80000
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#define SFD_NONBLOCK SFD_NONBLOCK
#define SFD_CLOEXEC  SFD_CLOEXEC
#else /* __COMPILER_PREFERR_ENUMS */
#define SFD_NONBLOCK 0x00800
#define SFD_CLOEXEC  0x80000
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/

__DECL_END

#endif /* !_BITS_SIGNALFD_H */
