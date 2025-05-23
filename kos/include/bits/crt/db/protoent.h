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
/*!replace_with_include <netdb.h>*/
#ifndef _BITS_CRT_DB_PROTOENT_H
#define _BITS_CRT_DB_PROTOENT_H 1

#include <__stdinc.h>

#ifdef __CC__
__DECL_BEGIN

/* Description of data base entry for a single service. */
struct protoent {
	/* XXX: It's unclear if p_name can be NULL! */
	char                   *p_name;    /* [0..1] Official protocol name. */
	/* XXX: It's unclear if p_aliases can be NULL! (or is {NULL} when empty) */
	char                  **p_aliases; /* [0..1][0..n] Alias list. */
	__STDC_INT32_AS_SSIZE_T p_proto;   /* Protocol number. */
};

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_DB_PROTOENT_H */
