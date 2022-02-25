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
#ifndef GUARD_LIBC_USER_MATH_C
#define GUARD_LIBC_USER_MATH_C 1

#include "../api.h"
/**/

#include <limits.h>
#include <stdint.h>

#include "math.h"

DECL_BEGIN








/*[[[head:libc_tanh,hash:CRC-32=0x168c3e]]]*/
/* Hyperbolic tangent of `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_tanh)(double x)
/*[[[body:libc_tanh]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTEDF("tanh(%f)", x); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_tanh]]]*/





/*[[[head:libc_log10,hash:CRC-32=0xf4920ff2]]]*/
/* Base-ten logarithm of `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_log10)(double x)
/*[[[body:libc_log10]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTEDF("log10(%f)", x); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_log10]]]*/



/*[[[head:libc_exp2,hash:CRC-32=0xb4abe3cc]]]*/
/* Compute base-2 exponential of `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_exp2)(double x)
/*[[[body:libc_exp2]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTEDF("exp2(%f)", x); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_exp2]]]*/

/*[[[head:libc_log2,hash:CRC-32=0xb32e7b4d]]]*/
/* Compute base-2 logarithm of `x' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_log2)(double x)
/*[[[body:libc_log2]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTEDF("log2(%f)", x); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_log2]]]*/

/*[[[head:libc_hypot,hash:CRC-32=0x287788c0]]]*/
/* Return `sqrt(x*x + y*y)' */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_hypot)(double x,
                             double y)
/*[[[body:libc_hypot]]]*/
/*AUTO*/{
	(void)x;
	(void)y;
	CRT_UNIMPLEMENTEDF("hypot(%f, %f)", x, y); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_hypot]]]*/

/*[[[head:libc_erf,hash:CRC-32=0xb0818d9b]]]*/
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_erf)(double x)
/*[[[body:libc_erf]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTEDF("erf(%f)", x); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_erf]]]*/

/*[[[head:libc_erfc,hash:CRC-32=0x18a21f35]]]*/
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_erfc)(double x)
/*[[[body:libc_erfc]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTEDF("erfc(%f)", x); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_erfc]]]*/

/*[[[head:libc_lgamma,hash:CRC-32=0xa75014b3]]]*/
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_lgamma)(double x)
/*[[[body:libc_lgamma]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTEDF("lgamma(%f)", x); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_lgamma]]]*/

/*[[[head:libc_tgamma,hash:CRC-32=0xc880fc24]]]*/
/* True gamma function */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_tgamma)(double x)
/*[[[body:libc_tgamma]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTEDF("tgamma(%f)", x); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_tgamma]]]*/

/*[[[head:libc_remquo,hash:CRC-32=0x33f77d4a]]]*/
/* Compute remainder of `x' and `y' and put in `*pquo' a value with
 * sign of x/y and magnitude  congruent `mod 2^n' to the  magnitude
 * of the integral quotient x/y, with n >= 3 */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED NONNULL((3)) double
NOTHROW(LIBCCALL libc_remquo)(double x,
                              double y,
                              int *pquo)
/*[[[body:libc_remquo]]]*/
/*AUTO*/{
	(void)x;
	(void)y;
	(void)pquo;
	CRT_UNIMPLEMENTEDF("remquo(%f, %f, %p)", x, y, pquo); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_remquo]]]*/


/*[[[head:libc_exp10,hash:CRC-32=0x81e7bc56]]]*/
/* A function missing in all standards: compute exponent to base ten */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_exp10)(double x)
/*[[[body:libc_exp10]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTEDF("exp10(%f)", x); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_exp10]]]*/

/*[[[head:libc_j0,hash:CRC-32=0xe72a9130]]]*/
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_j0)(double x)
/*[[[body:libc_j0]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTEDF("j0(%f)", x); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_j0]]]*/

/*[[[head:libc_j1,hash:CRC-32=0x3abc48b5]]]*/
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_j1)(double x)
/*[[[body:libc_j1]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTEDF("j1(%f)", x); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_j1]]]*/

/*[[[head:libc_jn,hash:CRC-32=0xd8adecab]]]*/
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_jn)(int n,
                          double x)
/*[[[body:libc_jn]]]*/
/*AUTO*/{
	(void)n;
	(void)x;
	CRT_UNIMPLEMENTEDF("jn(%x, %f)", n, x); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_jn]]]*/

/*[[[head:libc_y0,hash:CRC-32=0xfdf98887]]]*/
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_y0)(double x)
/*[[[body:libc_y0]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTEDF("y0(%f)", x); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_y0]]]*/

/*[[[head:libc_y1,hash:CRC-32=0x206f5102]]]*/
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_y1)(double x)
/*[[[body:libc_y1]]]*/
/*AUTO*/{
	(void)x;
	CRT_UNIMPLEMENTEDF("y1(%f)", x); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_y1]]]*/

/*[[[head:libc_yn,hash:CRC-32=0x42035811]]]*/
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW(LIBCCALL libc_yn)(int n,
                          double x)
/*[[[body:libc_yn]]]*/
/*AUTO*/{
	(void)n;
	(void)x;
	CRT_UNIMPLEMENTEDF("yn(%x, %f)", n, x); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_yn]]]*/

/*[[[head:libc_lgamma_r,hash:CRC-32=0x804e0019]]]*/
/* Reentrant version of lgamma. This function uses the global variable
 * `signgam'. The reentrant version instead takes a pointer and stores
 * the value through it */
INTERN ATTR_SECTION(".text.crt.math.math") WUNUSED double
NOTHROW_NCX(LIBCCALL libc_lgamma_r)(double x,
                                    int *signgamp)
/*[[[body:libc_lgamma_r]]]*/
/*AUTO*/{
	(void)x;
	(void)signgamp;
	CRT_UNIMPLEMENTEDF("lgamma_r(%f, %p)", x, signgamp); /* TODO */
	libc_seterrno(ENOSYS);
	return 0;
}
/*[[[end:libc_lgamma_r]]]*/





/*[[[start:exports,hash:CRC-32=0x8b46b35f]]]*/
DEFINE_PUBLIC_ALIAS(__tanh, libc_tanh);
DEFINE_PUBLIC_ALIAS(tanh, libc_tanh);
DEFINE_PUBLIC_ALIAS(__log10, libc_log10);
DEFINE_PUBLIC_ALIAS(log10, libc_log10);
DEFINE_PUBLIC_ALIAS(__exp2, libc_exp2);
DEFINE_PUBLIC_ALIAS(exp2, libc_exp2);
DEFINE_PUBLIC_ALIAS(__log2, libc_log2);
DEFINE_PUBLIC_ALIAS(log2, libc_log2);
DEFINE_PUBLIC_ALIAS(__hypot, libc_hypot);
DEFINE_PUBLIC_ALIAS(hypot, libc_hypot);
DEFINE_PUBLIC_ALIAS(__erf, libc_erf);
DEFINE_PUBLIC_ALIAS(erf, libc_erf);
DEFINE_PUBLIC_ALIAS(__erfc, libc_erfc);
DEFINE_PUBLIC_ALIAS(erfc, libc_erfc);
DEFINE_PUBLIC_ALIAS(gamma, libc_lgamma);
DEFINE_PUBLIC_ALIAS(__lgamma, libc_lgamma);
DEFINE_PUBLIC_ALIAS(__gamma, libc_lgamma);
DEFINE_PUBLIC_ALIAS(lgamma, libc_lgamma);
DEFINE_PUBLIC_ALIAS(__tgamma, libc_tgamma);
DEFINE_PUBLIC_ALIAS(tgamma, libc_tgamma);
DEFINE_PUBLIC_ALIAS(__remquo, libc_remquo);
DEFINE_PUBLIC_ALIAS(remquo, libc_remquo);
DEFINE_PUBLIC_ALIAS(__exp10, libc_exp10);
DEFINE_PUBLIC_ALIAS(exp10, libc_exp10);
DEFINE_PUBLIC_ALIAS(__j0, libc_j0);
DEFINE_PUBLIC_ALIAS(j0, libc_j0);
DEFINE_PUBLIC_ALIAS(__j1, libc_j1);
DEFINE_PUBLIC_ALIAS(j1, libc_j1);
DEFINE_PUBLIC_ALIAS(__jn, libc_jn);
DEFINE_PUBLIC_ALIAS(jn, libc_jn);
DEFINE_PUBLIC_ALIAS(__y0, libc_y0);
DEFINE_PUBLIC_ALIAS(y0, libc_y0);
DEFINE_PUBLIC_ALIAS(__y1, libc_y1);
DEFINE_PUBLIC_ALIAS(y1, libc_y1);
DEFINE_PUBLIC_ALIAS(__yn, libc_yn);
DEFINE_PUBLIC_ALIAS(yn, libc_yn);
DEFINE_PUBLIC_ALIAS(__lgamma_r, libc_lgamma_r);
DEFINE_PUBLIC_ALIAS(lgamma_r, libc_lgamma_r);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_MATH_C */
