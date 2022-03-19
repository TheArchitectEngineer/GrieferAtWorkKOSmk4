/* HASH CRC-32:0x740c6808 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: Cygwin        (/newlib/libc/include/wordexp.h) */
/* (#) Portability: FreeBSD       (/include/wordexp.h) */
/* (#) Portability: GNU C Library (/posix/wordexp.h) */
/* (#) Portability: NetBSD        (/include/wordexp.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/wordexp.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/wordexp.h) */
/* (#) Portability: libc6         (/include/wordexp.h) */
/* (#) Portability: musl libc     (/include/wordexp.h) */
/* (#) Portability: uClibc        (/include/wordexp.h) */
#ifndef _WORDEXP_H
#define _WORDEXP_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/types.h>
#include <bits/crt/wordexp.h>

/* Flags for `wordexp(3)' */
#if !defined(WRDE_DOOFFS) && defined(__WRDE_DOOFFS)
#define WRDE_DOOFFS  __WRDE_DOOFFS /* [valid_if(!WRDE_APPEND)] Insert `IN:we_offs' leading NULL entries before `we_wordv'.
                                    * _NOT_  counted in `we_wordc'. This flag is  ignored if `WRDE_APPEND' is also passed. */
#endif /* !WRDE_DOOFFS && __WRDE_DOOFFS */
#if !defined(WRDE_APPEND) && defined(__WRDE_APPEND)
#define WRDE_APPEND  __WRDE_APPEND /* Same as `WRDE_REUSE', but append additional entries, rather than override existing ones. */
#endif /* !WRDE_APPEND && __WRDE_APPEND */
#if !defined(WRDE_NOCMD) && defined(__WRDE_NOCMD)
#define WRDE_NOCMD   __WRDE_NOCMD  /* Don't do command substitution as per "$(echo hi)" or "`echo hi`" */
#endif /* !WRDE_NOCMD && __WRDE_NOCMD */
#if !defined(WRDE_REUSE) && defined(__WRDE_REUSE)
#define WRDE_REUSE   __WRDE_REUSE  /* The given `wordexp_t *self' is still filled from a preceding call, and `wordfree(3)' wasn't called. */
#endif /* !WRDE_REUSE && __WRDE_REUSE */
#if !defined(WRDE_SHOWERR) && defined(__WRDE_SHOWERR)
#define WRDE_SHOWERR __WRDE_SHOWERR /* Do not redirect STDERR_FILENO to `/dev/null' (normally, this is done to hide error messages) */
#endif /* !WRDE_SHOWERR && __WRDE_SHOWERR */
#if !defined(WRDE_UNDEF) && defined(__WRDE_UNDEF)
#define WRDE_UNDEF   __WRDE_UNDEF   /* Return `WRDE_BADVAL' if "$FOO" is used and `getenv("FOO") == NULL' (else, NULL environ variables simply expand to "") */
#endif /* !WRDE_UNDEF && __WRDE_UNDEF */

/* Return values (aside from `0') for `wordexp(3)' */
#if !defined(WRDE_NOSYS) && defined(__WRDE_NOSYS)
#define WRDE_NOSYS   __WRDE_NOSYS   /* System isn't supported */
#endif /* !WRDE_NOSYS && __WRDE_NOSYS */
#if !defined(WRDE_NOSPACE) && defined(__WRDE_NOSPACE)
#define WRDE_NOSPACE __WRDE_NOSPACE /* ENOMEM */
#endif /* !WRDE_NOSPACE && __WRDE_NOSPACE */
#if !defined(WRDE_BADCHAR) && defined(__WRDE_BADCHAR)
#define WRDE_BADCHAR __WRDE_BADCHAR /* Illegal character encountered (one of "\n|&;<>(){}") */
#endif /* !WRDE_BADCHAR && __WRDE_BADCHAR */
#if !defined(WRDE_BADVAL) && defined(__WRDE_BADVAL)
#define WRDE_BADVAL  __WRDE_BADVAL  /* `WRDE_UNDEF' was given and an undefined environment variable was used. */
#endif /* !WRDE_BADVAL && __WRDE_BADVAL */
#if !defined(WRDE_CMDSUB) && defined(__WRDE_CMDSUB)
#define WRDE_CMDSUB  __WRDE_CMDSUB  /* Tried to use "$(echo hi)" or "`echo hi`" when `WRDE_NOCMD' was given. */
#endif /* !WRDE_CMDSUB && __WRDE_CMDSUB */
#if !defined(WRDE_SYNTAX) && defined(__WRDE_SYNTAX)
#define WRDE_SYNTAX  __WRDE_SYNTAX  /* Syntax error (e.g. unmatched '"' or '(') */
#endif /* !WRDE_SYNTAX && __WRDE_SYNTAX */
#ifndef WRDE_ERRNO
#ifdef __WRDE_ERRNO
#define WRDE_ERRNO __WRDE_ERRNO   /* Error can be found in `errno(1)' */
#elif defined(__WRDE_NOSPACE)
#define WRDE_ERRNO __WRDE_NOSPACE /* Error can be found in `errno(1)' */
#endif /* !WRDE_SYNTAX && __WRDE_SYNTAX */
#endif /* !WRDE_ERRNO */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined
typedef __size_t size_t;
#endif /* !__size_t_defined */

typedef struct __wordexp_struct wordexp_t;

/* >> wordexp(3)
 * Do shell-like expansion of `string'
 * @param: string: The string to expand
 * @param: self:   The word-expansion controller (and result container)
 * @param: flags:  Expansion flags (set of `WRDE_*' from <wordexp.h>)
 * @return: 0 : Success
 * @return: * : Error (return value is one of `WRDE_*' from <wordexp.h>) */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,wordexp,(char const *__restrict __string, wordexp_t *__restrict __self, __STDC_INT_AS_UINT_T __flags),(__string,__self,__flags))
#ifdef __CRT_HAVE_wordfree
/* >> wordfree(3)
 * Free dynamic allocations made by `wordexp(3)' */
__CDECLARE_VOID(,__NOTHROW_NCX,wordfree,(wordexp_t *__self),(__self))
#elif defined(__CRT_HAVE_free) || defined(__CRT_HAVE_cfree) || defined(__CRT_HAVE___libc_free)
#include <libc/local/wordexp/wordfree.h>
/* >> wordfree(3)
 * Free dynamic allocations made by `wordexp(3)' */
__NAMESPACE_LOCAL_USING_OR_IMPL(wordfree, __FORCELOCAL __ATTR_ARTIFICIAL void __NOTHROW_NCX(__LIBCCALL wordfree)(wordexp_t *__self) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wordfree))(__self); })
#endif /* ... */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_WORDEXP_H */
