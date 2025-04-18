/* HASH CRC-32:0x539c6703 */
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
#ifndef GUARD_LIBC_AUTO_FNMATCH_C
#define GUARD_LIBC_AUTO_FNMATCH_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "fnmatch.h"
#include "../user/ctype.h"

DECL_BEGIN

#ifndef __KERNEL__
/* >> fnmatch(3)
 * Match the given `name' against `pattern', returning
 * `0'  if  they match,  and  `FNM_NOMATCH' otherwise.
 * @param: match_flags:   Set of `FNM_*'
 * @return: 0           : `name' is matched by `pattern'
 * @return: FNM_NOMATCH : `name' is not matched by `pattern' */
INTERN ATTR_SECTION(".text.crt.string.match") ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2) int
NOTHROW_NCX(LIBCCALL libc_fnmatch)(char const *pattern,
                                   char const *name,
                                   __STDC_INT_AS_UINT_T match_flags) {
	char card_post;
	/* TODO: Support for `FNM_NOESCAPE' */
	/* TODO: Support for `FNM_LEADING_DIR' */
	/* TODO: Support for `FNM_EXTMATCH' */
	for (;;) {
		if (!*name) {
			/* End of name (if the pattern is empty, or only contains '*', we have a match) */
			while (*pattern == '*')
				++pattern;
			if (!*pattern)
				return 0; /* Pattern ends with '*' (matches everything) */
			goto nomatch;
		}
		if (!*pattern)
			goto nomatch; /* Pattern end doesn't match */
		if (*pattern == '*') {
			/* Skip leading asterisks */
			do {
				++pattern;
			} while (*pattern == '*');
			if ((card_post = *pattern++) == '\0')
				return 0; /* Pattern ends with '*' (matches everything) */
			if (card_post == '?' || card_post == '[')
				goto next; /* Match any --> already found */
			for (;;) {
				char ch = *name++;
				if (ch == card_post ||
				    ((match_flags & 0x10) &&
				     libc_tolower(ch) == libc_tolower(card_post))) {
					/* Recursively check if the rest of the name and pattern match */
					if (!libc_fnmatch(pattern, name, match_flags))
						return 0;
				} else if (!ch) {
					goto nomatch; /* Wildcard suffix not found */
				} else if (ch == '/') {
					if ((match_flags & 0x01))
						goto nomatch;
					if ((match_flags & 0x04) &&
					    name[0] == '.' && card_post != '.')
						goto nomatch;
				}
			}
		}
		if (*pattern == '?') {
			if (*name == '/') {
				if (match_flags & 0x01)
					goto nomatch;
				if ((match_flags & 0x04) &&
				    name[1] == '.' && pattern[1] != '.')
					goto nomatch;
			}
			goto next; /* This will consume the '?' */
		} else if (*pattern == '[') {
			bool did_match = false;
			++pattern;
			do {
				if (!*pattern)
					goto nomatch;
				if (pattern[1] == '-') {
					char lo = pattern[0];
					char hi = pattern[2];
					pattern += 3;
					if ((unsigned char)*name >= (unsigned char)lo &&
					    (unsigned char)*name <= (unsigned char)hi)
						did_match = true;
				} else {
					if (*pattern == *name)
						did_match = true;
					++pattern;
				}
			} while (*pattern != ']');
			if (!did_match)
				goto nomatch;
			goto next; /* This will consume the trailing ']' */
		} else if (*pattern == *name) {
next:
			++name;
			++pattern;
			continue; /* single character match */
		}
		break; /* mismatch */
	}
nomatch:
	return 1;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(fnmatch,libc_fnmatch,ATTR_PURE WUNUSED ATTR_IN(1) ATTR_IN(2),int,NOTHROW_NCX,LIBCCALL,(char const *pattern, char const *name, __STDC_INT_AS_UINT_T match_flags),(pattern,name,match_flags));
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_FNMATCH_C */
