/* HASH CRC-32:0xf08f4f7a */
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
#ifndef GUARD_LIBC_AUTO_NETINET_IN_H
#define GUARD_LIBC_AUTO_NETINET_IN_H 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <netinet/in.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF ATTR_CONST uint32_t NOTHROW_NCX(LIBCCALL libc_ntohl)(uint32_t netlong);
INTDEF ATTR_CONST uint16_t NOTHROW_NCX(LIBCCALL libc_ntohs)(uint16_t netshort);
#define libc_htonl libc_ntohl
#define libc_htons libc_ntohs
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_NETINET_IN_H */
