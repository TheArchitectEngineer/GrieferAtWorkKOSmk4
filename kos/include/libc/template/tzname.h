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
/*!replace_with_include <time.h>*/
#ifndef __LOCAL_tzname
#include <__crt.h>
#ifndef __LOCAL_tzname
__DECL_BEGIN
#ifdef tzname
#define __LOCAL_tzname tzname
#elif defined(_tzname)
#define __LOCAL_tzname _tzname
#elif defined(__tzname)
#define __LOCAL_tzname __tzname
#elif defined(__CRT_HAVE_tzname)
#ifdef __NO_COMPILER_SREDIRECT
__CSDECLARE2(,char *tzname[2],tzname)
#define tzname         tzname
#define __LOCAL_tzname tzname
#else /* __NO_COMPILER_SREDIRECT */
__CSREDIRECT2(,char *__LOCAL_tzname[2],__LOCAL_tzname,tzname)
#define __LOCAL_tzname __LOCAL_tzname
#endif /* !__NO_COMPILER_SREDIRECT */
#elif defined(__CRT_HAVE__tzname)
#ifdef __NO_COMPILER_SREDIRECT
__CSDECLARE2(,char *_tzname[2],_tzname)
#define _tzname        _tzname
#define __LOCAL_tzname _tzname
#else /* __NO_COMPILER_SREDIRECT */
__CSREDIRECT2(,char *__LOCAL_tzname[2],__LOCAL_tzname,_tzname)
#define __LOCAL_tzname __LOCAL_tzname
#endif /* !__NO_COMPILER_SREDIRECT */
#elif defined(__CRT_HAVE___tzname)
#ifdef __NO_COMPILER_SREDIRECT
__CSDECLARE2(,char *__tzname[2],__tzname)
#define __tzname       __tzname
#define __LOCAL_tzname __tzname
#else /* __NO_COMPILER_SREDIRECT */
__CSREDIRECT2(,char *__LOCAL_tzname[2],__LOCAL_tzname,__tzname)
#define __LOCAL_tzname __LOCAL_tzname
#endif /* !__NO_COMPILER_SREDIRECT */
#elif defined(____p__tzname_defined)
#define __LOCAL_tzname __p__tzname()
#elif defined(__CRT_HAVE___p__tzname)
#define ____p__tzname_defined
__CDECLARE(__ATTR_WUNUSED __ATTR_CONST __ATTR_RETNONNULL,char **,__NOTHROW,__p__tzname,(void),())
#define __LOCAL_tzname __p__tzname()
#endif /* ... */
__DECL_END
#endif /* !__LOCAL_tzname */
#endif /* !__LOCAL_tzname */
