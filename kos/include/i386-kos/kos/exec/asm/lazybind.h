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
/*!replace_with_include <kos/exec/lazybind.h>*/
#ifndef _I386_KOS_KOS_EXEC_ASM_LAZYBIND_H
#define _I386_KOS_KOS_EXEC_ASM_LAZYBIND_H 1

#include <__stdinc.h>
#include <hybrid/host.h>

#ifdef __x86_64__
#include "lazybind64.h"
#else /* __x86_64__ */
#include "lazybind32.h"
#endif /* !__x86_64__ */


/* >> (PRIVATE|INTERN|PUBLIC)_LAZYBIND(SYMBOL name, void *getaddr(void))
 * Define  a self-modifying  function that lazily  invokes `getaddr()', then  uses that function's
 * return  value as a text location to jump to, permanently re-writing itself such that any future
 * calls to `name' will always be forwarded to the initially returned address, without `getaddr()'
 * having to be called ever again. */
#ifdef __x86_64__
#define PRIVATE_LAZYBIND(name, getaddr) __X86_64_DO_LAZYBIND(name, getaddr,; .local name)
#define INTERN_LAZYBIND(name, getaddr)  __X86_64_DO_LAZYBIND(name, getaddr,; .global name; .hidden name)
#define PUBLIC_LAZYBIND(name, getaddr)  __X86_64_DO_LAZYBIND(name, getaddr,; .global name)
#else /* __x86_64__ */
#define PRIVATE_LAZYBIND(name, getaddr) __I386_DO_LAZYBIND(name, getaddr,; .local name)
#define INTERN_LAZYBIND(name, getaddr)  __I386_DO_LAZYBIND(name, getaddr,; .global name; .hidden name)
#define PUBLIC_LAZYBIND(name, getaddr)  __I386_DO_LAZYBIND(name, getaddr,; .global name)
#endif /* !__x86_64__ */

#endif /* !_I386_KOS_KOS_EXEC_ASM_LAZYBIND_H */
