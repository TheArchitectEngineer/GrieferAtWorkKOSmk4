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
/*!replace_with_include <conio.h>*/
#ifndef __LOCAL_stdtty
#include <__crt.h>
#ifndef __LOCAL_stdtty
__DECL_BEGIN
#ifdef stdtty
#define __LOCAL_stdtty stdtty
#elif defined(__CRT_HAVE_stdtty)
#ifdef __NO_COMPILER_SREDIRECT
__CSDECLARE(,__FILE *,stdtty)
#define stdtty         stdtty
#define __LOCAL_stdtty stdtty
#else /* __NO_COMPILER_SREDIRECT */
__CSREDIRECT(,__FILE *,__LOCAL_stdtty,stdtty)
#define __LOCAL_stdtty __LOCAL_stdtty
#endif /* !__NO_COMPILER_SREDIRECT */
#endif /* ... */
__DECL_END
#endif /* !__LOCAL_stdtty */
#endif /* !__LOCAL_stdtty */
