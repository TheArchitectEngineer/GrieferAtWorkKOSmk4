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
#ifndef _BITS_CXX_REMOVE_POINTER_H
#define _BITS_CXX_REMOVE_POINTER_H 1

#include <__stdcxx.h>

#include "remove_cv.h"

__CXXDECL_BEGIN
__NAMESPACE_INT_BEGIN
template<class __T, class __TStripped> struct __remove_pointer_helper { typedef __T type; };
template<class __T, class __TStripped> struct __remove_pointer_helper<__T, __TStripped *> { typedef __TStripped type; };
__NAMESPACE_INT_END
__NAMESPACE_STD_BEGIN
template<class __T> struct remove_pointer: public __NAMESPACE_INT_SYM __remove_pointer_helper<__T, typename remove_cv<__T>::type> {};
__NAMESPACE_STD_END
__CXXDECL_END

#endif /* !_BITS_CXX_REMOVE_POINTER_H */
