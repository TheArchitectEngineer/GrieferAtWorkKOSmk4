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
#ifndef _NT_EXCEPT_H
#define _NT_EXCEPT_H 1

#include "__stdinc.h"
/**/

#include "types.h"
/**/

#include <hybrid/typecore.h>

/* Thread Information Block (mainly for SEH) */

#ifdef __CC__
__DECL_BEGIN


struct _CONTEXT;
struct _EXCEPTION_RECORD;
struct _EXCEPTION_POINTERS;
typedef int EXCEPTION_DISPOSITION;
#define EXCEPTION_CONTINUE_SEARCH 0

typedef EXCEPTION_DISPOSITION NTAPI
EXCEPTION_ROUTINE(struct _EXCEPTION_RECORD *ExceptionRecord,
                  PVOID EstablisherFrame,
                  struct _CONTEXT *ContextRecord,
                  PVOID DispatcherContext);
#ifndef __PEXCEPTION_ROUTINE_DEFINED
#define __PEXCEPTION_ROUTINE_DEFINED
typedef EXCEPTION_ROUTINE *PEXCEPTION_ROUTINE;
#endif /* !__PEXCEPTION_ROUTINE_DEFINED */

typedef struct _EXCEPTION_REGISTRATION_RECORD {
	__C89_NAMELESS union {
		struct _EXCEPTION_REGISTRATION_RECORD *Next;
		struct _EXCEPTION_REGISTRATION_RECORD *prev;
	};
	__C89_NAMELESS union {
		PEXCEPTION_ROUTINE Handler;
		PEXCEPTION_ROUTINE handler;
	};
} EXCEPTION_REGISTRATION_RECORD;
typedef EXCEPTION_REGISTRATION_RECORD *PEXCEPTION_REGISTRATION_RECORD;
typedef EXCEPTION_REGISTRATION_RECORD EXCEPTION_REGISTRATION;
typedef PEXCEPTION_REGISTRATION_RECORD PEXCEPTION_REGISTRATION;

__DECL_END
#endif /* __CC__ */

#endif /* !_NT_EXCEPT_H */
