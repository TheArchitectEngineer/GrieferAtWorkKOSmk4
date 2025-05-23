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
%(c_prefix){
/* (>) Standard: ISO C89 (ANSI X3.159-1989) */
/* (>) Standard: POSIX.1 (Issue 1, IEEE Std 1003.1-1988) */
/* (#) Portability: Cygwin        (/newlib/libc/include/math.h) */
/* (#) Portability: DJGPP         (/include/math.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/math.h) */
/* (#) Portability: GNU C Library (/math/math.h) */
/* (#) Portability: GNU Hurd      (/usr/include/math.h) */
/* (#) Portability: MSVC          (/include/math.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/math.h) */
/* (#) Portability: NetBSD        (/include/math.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/math.h) */
/* (#) Portability: OpenBSD       (/include/math.h) */
/* (#) Portability: OpenSolaris   (/usr/src/lib/libbc/inc/include/math.h) */
/* (#) Portability: Windows Kits  (/ucrt/math.h) */
/* (#) Portability: avr-libc      (/include/math.h) */
/* (#) Portability: diet libc     (/include/math.h) */
/* (#) Portability: libc4/5       (/include/math.h) */
/* (#) Portability: libc6         (/include/math.h) */
/* (#) Portability: musl libc     (/include/math.h) */
/* (#) Portability: uClibc        (/include/math.h) */
}

%[define_ccompat_header("cmath")]
%[default:section(".text.crt{|.dos}.math.math")]

%[define_double_replacement(__LIBM_MATHFUN = __LIBM_MATHFUNF, __LIBM_MATHFUNL)]
%[define_double_replacement(__LIBM_MATHFUNI = __LIBM_MATHFUNIF, __LIBM_MATHFUNIL)]
%[define_double_replacement(__LIBM_MATHFUN2 = __LIBM_MATHFUN2F, __LIBM_MATHFUN2L)]
%[define_double_replacement(__LIBM_MATHFUNI2 = __LIBM_MATHFUNI2F, __LIBM_MATHFUNI2L)]
%[define_double_replacement(__LIBM_MATHFUN1I = __LIBM_MATHFUN1IF, __LIBM_MATHFUN1IL)]
%[define_double_replacement(__LIBM_MATHFUN2I = __LIBM_MATHFUN2IF, __LIBM_MATHFUN2IL)]
%[define_double_replacement(__LIBM_MATHFUN3I = __LIBM_MATHFUN3IF, __LIBM_MATHFUN3IL)]
%[define_double_replacement(__LIBM_MATHFUNIM = __LIBM_MATHFUNIMF, __LIBM_MATHFUNIML)]
%[define_double_replacement(__LIBM_MATHFUN0 = __LIBM_MATHFUN0F, __LIBM_MATHFUN0L)]
%[define_double_replacement(__LIBM_MATHFUNX = __LIBM_MATHFUNXF, __LIBM_MATHFUNXL)]
%[define_double_replacement(__LIBM_MATHFUN_T = __LIBM_MATHFUNF_T, __LIBM_MATHFUNL_T)]
%[define_double_replacement(__kernel_standard = __kernel_standard_f, __kernel_standard_l)]
%[define_double2float_replacement(__IEEE754_FLOAT_TYPE_IS_DOUBLE__ = __IEEE754_FLOAT_TYPE_IS_FLOAT__)]
%[define_double2float_replacement(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ = __IEEE754_DOUBLE_TYPE_IS_FLOAT__)]
%[define_double2float_replacement(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ = __IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)]
%[define_double2ldouble_replacement(__IEEE754_FLOAT_TYPE_IS_DOUBLE__ = __IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)]
%[define_double2ldouble_replacement(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__ = __IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__)]
%[define_double2ldouble_replacement(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__ = __IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)]
%[define_double_replacement(__DECL_SIMD_cos = __DECL_SIMD_cosf, __DECL_SIMD_cosl)]
%[define_double_replacement(__DECL_SIMD_sin = __DECL_SIMD_sinf, __DECL_SIMD_sinl)]
%[define_double_replacement(__DECL_SIMD_sincos = __DECL_SIMD_sincosf, __DECL_SIMD_sincosl)]
%[define_double_replacement(__DECL_SIMD_log = __DECL_SIMD_logf, __DECL_SIMD_logl)]
%[define_double_replacement(__DECL_SIMD_exp = __DECL_SIMD_expf, __DECL_SIMD_expl)]
%[define_double_replacement(__DECL_SIMD_pow = __DECL_SIMD_powf, __DECL_SIMD_powl)]
%[define_double_replacement(HUGE_VAL = HUGE_VALF, HUGE_VALL)]
%[define_double_replacement(__HUGE_VAL = __HUGE_VALF, __HUGE_VALL)]
%[define_double_replacement(__INFINITY = __INFINITYF, __INFINITYL)]
%[define_double_replacement(__NAN = __NANF, __NANL)]

%[define_double_replacement(__LIBM_KMATHERR_ACOS = __LIBM_KMATHERRF_ACOS, __LIBM_KMATHERRL_ACOS)]
%[define_double_replacement(__LIBM_KMATHERR_ASIN = __LIBM_KMATHERRF_ASIN, __LIBM_KMATHERRL_ASIN)]
%[define_double_replacement(__LIBM_KMATHERR_ATAN2 = __LIBM_KMATHERRF_ATAN2, __LIBM_KMATHERRL_ATAN2)]
%[define_double_replacement(__LIBM_KMATHERR_HYPOT = __LIBM_KMATHERRF_HYPOT, __LIBM_KMATHERRL_HYPOT)]
%[define_double_replacement(__LIBM_KMATHERR_COSH = __LIBM_KMATHERRF_COSH, __LIBM_KMATHERRL_COSH)]
%[define_double_replacement(__LIBM_KMATHERR_EXP_OVERFLOW = __LIBM_KMATHERRF_EXP_OVERFLOW, __LIBM_KMATHERRL_EXP_OVERFLOW)]
%[define_double_replacement(__LIBM_KMATHERR_EXP_UNDERFLOW = __LIBM_KMATHERRF_EXP_UNDERFLOW, __LIBM_KMATHERRL_EXP_UNDERFLOW)]
%[define_double_replacement(__LIBM_KMATHERR_Y0_ZERO = __LIBM_KMATHERRF_Y0_ZERO, __LIBM_KMATHERRL_Y0_ZERO)]
%[define_double_replacement(__LIBM_KMATHERR_Y0_MINUS = __LIBM_KMATHERRF_Y0_MINUS, __LIBM_KMATHERRL_Y0_MINUS)]
%[define_double_replacement(__LIBM_KMATHERR_Y1_ZERO = __LIBM_KMATHERRF_Y1_ZERO, __LIBM_KMATHERRL_Y1_ZERO)]
%[define_double_replacement(__LIBM_KMATHERR_Y1_MINUS = __LIBM_KMATHERRF_Y1_MINUS, __LIBM_KMATHERRL_Y1_MINUS)]
%[define_double_replacement(__LIBM_KMATHERR_YN_ZERO = __LIBM_KMATHERRF_YN_ZERO, __LIBM_KMATHERRL_YN_ZERO)]
%[define_double_replacement(__LIBM_KMATHERR_YN_MINUS = __LIBM_KMATHERRF_YN_MINUS, __LIBM_KMATHERRL_YN_MINUS)]
%[define_double_replacement(__LIBM_KMATHERR_LGAMMA_OVERFLOW = __LIBM_KMATHERRF_LGAMMA_OVERFLOW, __LIBM_KMATHERRL_LGAMMA_OVERFLOW)]
%[define_double_replacement(__LIBM_KMATHERR_LGAMMA_MINUS = __LIBM_KMATHERRF_LGAMMA_MINUS, __LIBM_KMATHERRL_LGAMMA_MINUS)]
%[define_double_replacement(__LIBM_KMATHERR_LOG_ZERO = __LIBM_KMATHERRF_LOG_ZERO, __LIBM_KMATHERRL_LOG_ZERO)]
%[define_double_replacement(__LIBM_KMATHERR_LOG_MINUS = __LIBM_KMATHERRF_LOG_MINUS, __LIBM_KMATHERRL_LOG_MINUS)]
%[define_double_replacement(__LIBM_KMATHERR_LOG10_ZERO = __LIBM_KMATHERRF_LOG10_ZERO, __LIBM_KMATHERRL_LOG10_ZERO)]
%[define_double_replacement(__LIBM_KMATHERR_LOG10_MINUS = __LIBM_KMATHERRF_LOG10_MINUS, __LIBM_KMATHERRL_LOG10_MINUS)]
%[define_double_replacement(__LIBM_KMATHERR_POW_ZERO = __LIBM_KMATHERRF_POW_ZERO, __LIBM_KMATHERRL_POW_ZERO)]
%[define_double_replacement(__LIBM_KMATHERR_POW_OVERFLOW = __LIBM_KMATHERRF_POW_OVERFLOW, __LIBM_KMATHERRL_POW_OVERFLOW)]
%[define_double_replacement(__LIBM_KMATHERR_POW_UNDERFLOW = __LIBM_KMATHERRF_POW_UNDERFLOW, __LIBM_KMATHERRL_POW_UNDERFLOW)]
%[define_double_replacement(__LIBM_KMATHERR_POW_MINUS = __LIBM_KMATHERRF_POW_MINUS, __LIBM_KMATHERRL_POW_MINUS)]
%[define_double_replacement(__LIBM_KMATHERR_POW_NONINT = __LIBM_KMATHERRF_POW_NONINT, __LIBM_KMATHERRL_POW_NONINT)]
%[define_double_replacement(__LIBM_KMATHERR_SINH = __LIBM_KMATHERRF_SINH, __LIBM_KMATHERRL_SINH)]
%[define_double_replacement(__LIBM_KMATHERR_SQRT = __LIBM_KMATHERRF_SQRT, __LIBM_KMATHERRL_SQRT)]
%[define_double_replacement(__LIBM_KMATHERR_FMOD = __LIBM_KMATHERRF_FMOD, __LIBM_KMATHERRL_FMOD)]
%[define_double_replacement(__LIBM_KMATHERR_REMAINDER = __LIBM_KMATHERRF_REMAINDER, __LIBM_KMATHERRL_REMAINDER)]
%[define_double_replacement(__LIBM_KMATHERR_ACOSH = __LIBM_KMATHERRF_ACOSH, __LIBM_KMATHERRL_ACOSH)]
%[define_double_replacement(__LIBM_KMATHERR_ATANH_PLUSONE = __LIBM_KMATHERRF_ATANH_PLUSONE, __LIBM_KMATHERRL_ATANH_PLUSONE)]
%[define_double_replacement(__LIBM_KMATHERR_ATANH_ONE = __LIBM_KMATHERRF_ATANH_ONE, __LIBM_KMATHERRL_ATANH_ONE)]
%[define_double_replacement(__LIBM_KMATHERR_SCALB_OVERFLOW = __LIBM_KMATHERRF_SCALB_OVERFLOW, __LIBM_KMATHERRL_SCALB_OVERFLOW)]
%[define_double_replacement(__LIBM_KMATHERR_SCALB_UNDERFLOW = __LIBM_KMATHERRF_SCALB_UNDERFLOW, __LIBM_KMATHERRL_SCALB_UNDERFLOW)]
%[define_double_replacement(__LIBM_KMATHERR_J0_TLOSS = __LIBM_KMATHERRF_J0_TLOSS, __LIBM_KMATHERRL_J0_TLOSS)]
%[define_double_replacement(__LIBM_KMATHERR_Y0_TLOSS = __LIBM_KMATHERRF_Y0_TLOSS, __LIBM_KMATHERRL_Y0_TLOSS)]
%[define_double_replacement(__LIBM_KMATHERR_J1_TLOSS = __LIBM_KMATHERRF_J1_TLOSS, __LIBM_KMATHERRL_J1_TLOSS)]
%[define_double_replacement(__LIBM_KMATHERR_Y1_TLOSS = __LIBM_KMATHERRF_Y1_TLOSS, __LIBM_KMATHERRL_Y1_TLOSS)]
%[define_double_replacement(__LIBM_KMATHERR_JN_TLOSS = __LIBM_KMATHERRF_JN_TLOSS, __LIBM_KMATHERRL_JN_TLOSS)]
%[define_double_replacement(__LIBM_KMATHERR_YN_TLOSS = __LIBM_KMATHERRF_YN_TLOSS, __LIBM_KMATHERRL_YN_TLOSS)]
%[define_double_replacement(__LIBM_KMATHERR_TGAMMA_OVERFLOW = __LIBM_KMATHERRF_TGAMMA_OVERFLOW, __LIBM_KMATHERRL_TGAMMA_OVERFLOW)]
%[define_double_replacement(__LIBM_KMATHERR_TGAMMA_MINUS = __LIBM_KMATHERRF_TGAMMA_MINUS, __LIBM_KMATHERRL_TGAMMA_MINUS)]
%[define_double_replacement(__LIBM_KMATHERR_POW_NAN = __LIBM_KMATHERRF_POW_NAN, __LIBM_KMATHERRL_POW_NAN)]
%[define_double_replacement(__LIBM_KMATHERR_POW_ZEROMINUS = __LIBM_KMATHERRF_POW_ZEROMINUS, __LIBM_KMATHERRL_POW_ZEROMINUS)]
%[define_double_replacement(__LIBM_KMATHERR_EXP2_OVERFLOW = __LIBM_KMATHERRF_EXP2_OVERFLOW, __LIBM_KMATHERRL_EXP2_OVERFLOW)]
%[define_double_replacement(__LIBM_KMATHERR_EXP2_UNDERFLOW = __LIBM_KMATHERRF_EXP2_UNDERFLOW, __LIBM_KMATHERRL_EXP2_UNDERFLOW)]
%[define_double_replacement(__LIBM_KMATHERR_EXP10_OVERFLOW = __LIBM_KMATHERRF_EXP10_OVERFLOW, __LIBM_KMATHERRL_EXP10_OVERFLOW)]
%[define_double_replacement(__LIBM_KMATHERR_EXP10_UNDERFLOW = __LIBM_KMATHERRF_EXP10_UNDERFLOW, __LIBM_KMATHERRL_EXP10_UNDERFLOW)]
%[define_double_replacement(__LIBM_KMATHERR_LOG2_ZERO = __LIBM_KMATHERRF_LOG2_ZERO, __LIBM_KMATHERRL_LOG2_ZERO)]
%[define_double_replacement(__LIBM_KMATHERR_LOG2_MINUS = __LIBM_KMATHERRF_LOG2_MINUS, __LIBM_KMATHERRL_LOG2_MINUS)]
%[define_double_replacement(__LIBM_KMATHERR_TGAMMA_ZERO = __LIBM_KMATHERRF_TGAMMA_ZERO, __LIBM_KMATHERRL_TGAMMA_ZERO)]
%[define_double_replacement(__LIBM_KMATHERR_COS_INF = __LIBM_KMATHERRF_COS_INF, __LIBM_KMATHERRL_COS_INF)]
%[define_double_replacement(__LIBM_KMATHERR_SIN_INF = __LIBM_KMATHERRF_SIN_INF, __LIBM_KMATHERRL_SIN_INF)]
%[define_double_replacement(__LIBM_KMATHERR_TAN_INF = __LIBM_KMATHERRF_TAN_INF, __LIBM_KMATHERRL_TAN_INF)]
%[define_double_replacement(__LIBM_KMATHERR_SCALB_INVALID = __LIBM_KMATHERRF_SCALB_INVALID, __LIBM_KMATHERRL_SCALB_INVALID)]
%[define_double_replacement(__LIBM_KMATHERR_TGAMMA_UNDERFLOW = __LIBM_KMATHERRF_TGAMMA_UNDERFLOW, __LIBM_KMATHERRL_TGAMMA_UNDERFLOW)]
%[define_double_replacement(__LIBM_KMATHERR_ILOGB = __LIBM_KMATHERRF_ILOGB, __LIBM_KMATHERRL_ILOGB)]
%[define_double_replacement(__LIBM_KMATHERR_EXPM1_OVERFLOW = __LIBM_KMATHERRF_EXPM1_OVERFLOW, __LIBM_KMATHERRL_EXPM1_OVERFLOW)]
%[define_double_replacement(__LIBM_KMATHERR_EXPM1_UNDERFLOW = __LIBM_KMATHERRF_EXPM1_UNDERFLOW, __LIBM_KMATHERRL_EXPM1_UNDERFLOW)]

%[define(M_E        = 2.7182818284590452354)]  /* e */
%[define(M_LOG2E    = 1.4426950408889634074)]  /* log_2 e */
%[define(M_LOG10E   = 0.43429448190325182765)] /* log_10 e */
%[define(M_LN2      = 0.69314718055994530942)] /* log_e 2 */
%[define(M_LN10     = 2.30258509299404568402)] /* log_e 10 */
%[define(M_PI       = 3.14159265358979323846)] /* pi */
%[define(M_PI_2     = 1.57079632679489661923)] /* pi/2 */
%[define(M_PI_4     = 0.78539816339744830962)] /* pi/4 */
%[define(M_1_PI     = 0.31830988618379067154)] /* 1/pi */
%[define(M_2_PI     = 0.63661977236758134308)] /* 2/pi */
%[define(M_2_SQRTPI = 1.12837916709551257390)] /* 2/sqrt(pi) */
%[define(M_SQRT2    = 1.41421356237309504880)] /* sqrt(2) */
%[define(M_SQRT1_2  = 0.70710678118654752440)] /* 1/sqrt(2) */
%[define(M_El       = 2.718281828459045235360287471352662498L)] /* e */
%[define(M_LOG2El   = 1.442695040888963407359924681001892137L)] /* log_2 e */
%[define(M_LOG10El  = 0.434294481903251827651128918916605082L)] /* log_10 e */
%[define(M_LN2l     = 0.693147180559945309417232121458176568L)] /* log_e 2 */
%[define(M_LN10l    = 2.302585092994045684017991454684364208L)] /* log_e 10 */
%[define(M_PIl      = 3.141592653589793238462643383279502884L)] /* pi */
%[define(M_PI_2l    = 1.570796326794896619231321691639751442L)] /* pi/2 */
%[define(M_PI_4l    = 0.785398163397448309615660845819875721L)] /* pi/4 */
%[define(M_1_PIl    = 0.318309886183790671537767526745028724L)] /* 1/pi */
%[define(M_2_PIl    = 0.636619772367581343075535053490057448L)] /* 2/pi */
%[define(M_2_SQRTPIl= 1.128379167095512573896158903121545172L)] /* 2/sqrt(pi) */
%[define(M_SQRT2l   = 1.414213562373095048801688724209698079L)] /* sqrt(2) */
%[define(M_SQRT1_2l = 0.707106781186547524400844362104849039L)] /* 1/sqrt(2) */


/* NOTE: These assumptions are correct for all currently targeted platforms,
 *       but  by making them we can get rid of a significant portion of libc
 *       code. If we ever target a platform where these aren't correct, then
 *       you should simply delete them from here! */
%[assume_defined_in_kos(__IEEE754_FLOAT_TYPE_IS_FLOAT__)]
%[assume_undefined_in_kos(__IEEE754_DOUBLE_TYPE_IS_FLOAT__)]
%[assume_undefined_in_kos(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)]
%[assume_undefined_in_kos(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)]
%[assume_defined_in_kos(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__)]
%[assume_undefined_in_kos(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)]
%[assume_undefined_in_kos(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)]
%[assume_undefined_in_kos(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__)]
%[assume_defined_in_kos(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)]
%[assume_defined_in_kos(__LIBM_MATHFUN, __LIBM_MATHFUNI, __LIBM_MATHFUN2, __LIBM_MATHFUNI2, __LIBM_MATHFUN1I, __LIBM_MATHFUN2I, __LIBM_MATHFUN3I, __LIBM_MATHFUNIM, __LIBM_MATHFUN0, __LIBM_MATHFUNX)]
%[assume_defined_in_kos(__LIBM_MATHFUNF, __LIBM_MATHFUNIF, __LIBM_MATHFUN2F, __LIBM_MATHFUNI2F, __LIBM_MATHFUN1IF, __LIBM_MATHFUN2IF, __LIBM_MATHFUN3IF, __LIBM_MATHFUNIMF, __LIBM_MATHFUN0F, __LIBM_MATHFUNXF)]
%[assume_defined_in_kos(__LIBM_MATHFUNL, __LIBM_MATHFUNIL, __LIBM_MATHFUN2L, __LIBM_MATHFUNI2L, __LIBM_MATHFUN1IL, __LIBM_MATHFUN2IL, __LIBM_MATHFUN3IL, __LIBM_MATHFUNIML, __LIBM_MATHFUN0L, __LIBM_MATHFUNXL)]
%[assume_defined_in_kos(__IEEE754_FLOAT_TYPE__)]
%[assume_defined_in_kos(__IEEE754_DOUBLE_TYPE__)]
//%[assume_defined_in_kos(__IEEE854_LONG_DOUBLE_TYPE__)] /* Not the case on ARM! (where `long double' is an alias for `double') */
/**/

%(auto_source){
#include "../libc/globals.h"
#include "../libc/dos-compat.h"

#ifdef __GNUC__
/* Disable strict-overflow warnings (there's a couple, but we _just_ _don't_ _care_)
 * The  reason we don't care is that all of those warnings are super-hard to get rid
 * of, and they all trigger  because of code that's not  even ours (i.e. is part  of
 * fdlibm) */
__pragma_GCC_diagnostic_ignored(Wstrict_overflow)
#endif /* __GNUC__ */

}

%(c, ccompat)#ifndef __NO_FPU
%[insert:prefix(
#include <features.h>
)]%{

}%[insert:prefix(
#include <hybrid/typecore.h>
)]%[insert:prefix(
#include <hybrid/floatcore.h>
)]%{

}%[insert:prefix(
#include <bits/math-constants.h>
)]%[insert:prefix(
#include <bits/crt/math-vector.h>
)]%{

}%[insert:prefix(
#include <ieee754.h>
)]%{

#ifdef __USE_ISOC99
#include <asm/crt/fp_type.h>  /* __FP_NAN, __FP_INFINITE, ... */
#include <libm/fcomp.h>
#endif /* __USE_ISOC99 */
#if defined(__USE_ISOC99) || defined(__USE_GNU) || defined(__STDC_WANT_IEC_60559_BFP_EXT__)
#include <bits/crt/mathdef.h> /* __FLT_EVAL_METHOD__, __FP_ILOGB0, __FP_ILOGBNAN */
#endif /* __USE_ISOC99 || __USE_GNU || __STDC_WANT_IEC_60559_BFP_EXT__ */

#ifdef __USE_MISC
#include <asm/crt/math-exception.h>
#include <asm/crt/math-libc_version.h>
#endif /* __USE_MISC */


/* Math constants (`_USE_MATH_DEFINES' is the DOS feature macro to expose these) */
#if defined(__USE_MISC) || defined(__USE_XOPEN) || defined(_USE_MATH_DEFINES)
#ifndef M_E
#define M_E        2.7182818284590452354  /* e */
#define M_LOG2E    1.4426950408889634074  /* log_2 e */
#define M_LOG10E   0.43429448190325182765 /* log_10 e */
#define M_LN2      0.69314718055994530942 /* log_e 2 */
#define M_LN10     2.30258509299404568402 /* log_e 10 */
#define M_PI       3.14159265358979323846 /* pi */
#define M_PI_2     1.57079632679489661923 /* pi/2 */
#define M_PI_4     0.78539816339744830962 /* pi/4 */
#define M_1_PI     0.31830988618379067154 /* 1/pi */
#define M_2_PI     0.63661977236758134308 /* 2/pi */
#define M_2_SQRTPI 1.12837916709551257390 /* 2/sqrt(pi) */
#define M_SQRT2    1.41421356237309504880 /* sqrt(2) */
#define M_SQRT1_2  0.70710678118654752440 /* 1/sqrt(2) */
#endif /* !M_E */
#endif /* __USE_MISC || __USE_XOPEN || _USE_MATH_DEFINES */

/* Math constants with long-double precision. */
#if defined(__USE_GNU) && defined(__COMPILER_HAVE_LONGDOUBLE)
#ifndef M_El
#define M_El        2.718281828459045235360287471352662498L /* e */
#define M_LOG2El    1.442695040888963407359924681001892137L /* log_2 e */
#define M_LOG10El   0.434294481903251827651128918916605082L /* log_10 e */
#define M_LN2l      0.693147180559945309417232121458176568L /* log_e 2 */
#define M_LN10l     2.302585092994045684017991454684364208L /* log_e 10 */
#define M_PIl       3.141592653589793238462643383279502884L /* pi */
#define M_PI_2l     1.570796326794896619231321691639751442L /* pi/2 */
#define M_PI_4l     0.785398163397448309615660845819875721L /* pi/4 */
#define M_1_PIl     0.318309886183790671537767526745028724L /* 1/pi */
#define M_2_PIl     0.636619772367581343075535053490057448L /* 2/pi */
#define M_2_SQRTPIl 1.128379167095512573896158903121545172L /* 2/sqrt(pi) */
#define M_SQRT2l    1.414213562373095048801688724209698079L /* sqrt(2) */
#define M_SQRT1_2l  0.707106781186547524400844362104849039L /* 1/sqrt(2) */
#endif /* !M_El */
#endif /* __USE_GNU && __COMPILER_HAVE_LONGDOUBLE */


#if !defined(HUGE_VAL) && defined(__HUGE_VAL)
#define HUGE_VAL __HUGE_VAL /* double HUGE_VAL; */
#endif /* !HUGE_VAL && __HUGE_VAL */

#ifdef __USE_ISOC99
#if !defined(HUGE_VALF) && defined(__HUGE_VALF)
#define HUGE_VALF __HUGE_VALF /* double HUGE_VALF; */
#endif /* !HUGE_VALF && __HUGE_VALF */

#if !defined(HUGE_VALL) && defined(__HUGE_VALL)
#define HUGE_VALL __HUGE_VALL /* double HUGE_VALL; */
#endif /* !HUGE_VALL && __HUGE_VALL */

#if !defined(INFINITY) && defined(__INFINITYF)
#define INFINITY __INFINITYF /* float INFINITY; */
#endif /* !INFINITY && __INFINITYF */

#if !defined(NAN) && defined(__NANF)
#define NAN __NANF /* float NAN; */
#endif /* !NAN && __NANF */

/* This value is returned by `ilogb(0)'. */
#ifdef __FP_ILOGB0
#define FP_ILOGB0 __FP_ILOGB0 /* int FP_ILOGB0; */
#endif /* __FP_ILOGB0 */

/* This value is returned by `ilogb(NAN)'. */
#ifdef __FP_ILOGBNAN
#define FP_ILOGBNAN __FP_ILOGBNAN /* int FP_ILOGBNAN; */
#endif /* __FP_ILOGBNAN */

/* Define if fma(x, y, z) is at least as ~fast~ as `x * y + z' */
#ifdef __FP_FAST_FMA
#define FP_FAST_FMA 1
#endif /* __FP_FAST_FMA */

/* Define if fmaf(x, y, z) is at least as ~fast~ as `x * y + z' */
#ifdef __FP_FAST_FMAF
#define FP_FAST_FMAF 1
#endif /* __FP_FAST_FMAF */

/* Define if fmal(x, y, z) is at least as ~fast~ as `x * y + z' */
#ifdef __FP_FAST_FMAL
#define FP_FAST_FMAL 1
#endif /* __FP_FAST_FMAL */

#endif /* __USE_ISOC99 */

#if defined(__USE_GNU) || defined(__STDC_WANT_IEC_60559_BFP_EXT__)
#if !defined(SNANF) && defined(__SNANF)
#define SNANF __SNANF
#endif /* !SNANF && __SNANF */
#if !defined(SNAN) && defined(__SNAN)
#define SNAN  __SNAN
#endif /* !SNAN && __SNAN */
#if !defined(SNANL) && defined(__SNANL)
#define SNANL __SNANL
#endif /* !SNANL && __SNANL */
/* TODO: Define `__FP_LOGB0_IS_MIN' in `<bits/crt/mathdef.h>' */
#ifdef __FP_LOGB0_IS_MIN
#define FP_LLOGB0 (-__LONG_MAX__ - 1)
#else /* __FP_LOGB0_IS_MIN */
#define FP_LLOGB0 (-__LONG_MAX__)
#endif /* !__FP_LOGB0_IS_MIN */
/* TODO: Define `__FP_LOGBNAN_IS_MIN' in `<bits/crt/mathdef.h>' */
#ifdef __FP_LOGBNAN_IS_MIN
#define FP_LLOGBNAN (-__LONG_MAX__ - 1)
#else /* __FP_LOGBNAN_IS_MIN */
#define FP_LLOGBNAN __LONG_MAX__
#endif /* !__FP_LOGBNAN_IS_MIN */

/* Possible values for `round' argument of `fromfp(3)' and friends. */
#define FP_INT_UPWARD            0
#define FP_INT_DOWNWARD          1
#define FP_INT_TOWARDZERO        2
#define FP_INT_TONEARESTFROMZERO 3
#define FP_INT_TONEAREST         4
#endif /* __USE_GNU || __STDC_WANT_IEC_60559_BFP_EXT__ */

#ifdef __CC__
__SYSDECL_BEGIN

}

%[insert:std]

@@>> acosf(3), acos(3), acosl(3)
@@Arc cosine of `x'
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__acos")]]
[[impl_include("<libm/fcomp.h>", "<libm/fabs.h>", "<libm/matherr.h>")]]
[[impl_include("<libm/nan.h>", "<libm/acos.h>", "<asm/crt/fenv.h>")]]
[[requires_include("<ieee754.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double acos(double x) {
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    __LIBM_MATHFUNI2(@isgreaterequal@, __LIBM_MATHFUN(@fabs@, x), 1.0)) {
@@pp_if $has_function(feraiseexcept) && defined(FE_INVALID)@@
		feraiseexcept(FE_INVALID); /* acos(|x|>1) */
@@pp_endif@@
		return __kernel_standard(x, x, __LIBM_MATHFUN1I(@nan@, ""), __LIBM_KMATHERR_ACOS);
	}
	return __LIBM_MATHFUN(@acos@, x);
}

@@>> asinf(3), asin(3), asinl(3)
@@Arc sine of `x'
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__asin")]]
[[impl_include("<libm/fcomp.h>", "<libm/fabs.h>", "<libm/matherr.h>")]]
[[impl_include("<libm/nan.h>", "<libm/asin.h>", "<asm/crt/fenv.h>")]]
[[requires_include("<ieee754.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double asin(double x) {
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    __LIBM_MATHFUNI2(@isgreaterequal@, __LIBM_MATHFUN(@fabs@, x), 1.0)) {
@@pp_if $has_function(feraiseexcept) && defined(FE_INVALID)@@
		feraiseexcept(FE_INVALID); /* asin(|x|>1) */
@@pp_endif@@
		return __kernel_standard(x, x, __LIBM_MATHFUN1I(@nan@, ""), __LIBM_KMATHERR_ASIN);
	}
	return __LIBM_MATHFUN(@asin@, x);
}

@@>> atanf(3), atan(3), atanl(3)
@@Arc tangent of `x'
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__atan")]]
[[impl_include("<libm/fcomp.h>", "<libm/fabs.h>", "<libm/matherr.h>")]]
[[impl_include("<libm/inf.h>", "<libm/atan.h>")]]
[[requires_include("<ieee754.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double atan(double x) {
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    __LIBM_MATHFUNI2(@isgreaterequal@, __LIBM_MATHFUN(@fabs@, x), 1.0)) {
		return __kernel_standard(x, x, __LIBM_MATHFUN0(@inf@),
		                         __LIBM_MATHFUN(@fabs@, x) > 1.0
		                         ? __LIBM_KMATHERR_ATANH_PLUSONE /* atanh(|x|>1) */
		                         : __LIBM_KMATHERR_ATANH_ONE);   /* atanh(|x|==1) */
	}
	return __LIBM_MATHFUN(@atan@, x);
}

@@>> atan2f(3), atan2(3), atan2l(3)
@@Arc tangent of `y / x'
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__atan2")]]
[[impl_include("<bits/math-constants.h>", "<libm/matherr.h>")]]
[[requires_include("<ieee754.h>"), impl_include("<libm/atan2.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double atan2(double y, double x){
	if (__LIBM_LIB_VERSION == __LIBM_SVID && x == 0.0 && y == 0.0)
		return __kernel_standard(y, x, __HUGE_VAL, __LIBM_KMATHERR_ATAN2); /* atan2(+-0,+-0) */
	return __LIBM_MATHFUN2(@atan2@, y, x);
}

@@>> cosf(3), cos(3), cosl(3)
@@Cosine of `x'
[[attribute("__DECL_SIMD_cos"), decl_include("<bits/crt/math-vector.h>")]]
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__cos")]]
[[impl_include("<libm/isnan.h>", "<libm/cos.h>", "<libm/matherr.h>")]]
[[requires_include("<ieee754.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double cos(double x) {
	double result = __LIBM_MATHFUN(@cos@, x);
	if (__LIBM_MATHFUNI(@isnan@, result) && !__LIBM_MATHFUNI(@isnan@, x))
		result = __kernel_standard(x, x, result, __LIBM_KMATHERR_COS_INF);
	return result;
}

@@>> sinf(3), sin(3), sinl(3)
@@Sine of `x'
[[attribute("__DECL_SIMD_sin"), decl_include("<bits/crt/math-vector.h>")]]
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__sin")]]
[[impl_include("<libm/isnan.h>", "<libm/sin.h>", "<libm/matherr.h>")]]
[[requires_include("<ieee754.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double sin(double x) {
	double result = __LIBM_MATHFUN(@sin@, x);
	if (__LIBM_MATHFUNI(@isnan@, result) && !__LIBM_MATHFUNI(@isnan@, x))
		result = __kernel_standard(x, x, result, __LIBM_KMATHERR_SIN_INF);
	return result;
}

@@>> tanf(3), tan(3), tanl(3)
@@Tangent of `x'
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__tan")]]
[[impl_include("<libm/isnan.h>", "<libm/isinf.h>", "<libm/tan.h>", "<libm/matherr.h>")]]
[[requires_include("<ieee754.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double tan(double x) {
	double result = __LIBM_MATHFUN(@tan@, x);
	if (__LIBM_MATHFUNI(@isnan@, result) && __LIBM_MATHFUNI(@isinf@, x))
		result = __kernel_standard(x, x, result, __LIBM_KMATHERR_TAN_INF);
	return result;
}


[[std, crtbuiltin, export_alias("__acosf")]] acosf(*) %{generate(double2float("acos"))}
[[std, crtbuiltin, export_alias("__asinf")]] asinf(*) %{generate(double2float("asin"))}
[[std, crtbuiltin, export_alias("__atanf")]] atanf(*) %{generate(double2float("atan"))}
[[std, crtbuiltin, export_alias("__atan2f")]] atan2f(*) %{generate(double2float("atan2"))}
[[std, crtbuiltin, export_alias("__cosf")]] cosf(*) %{generate(double2float("cos"))}
[[std, crtbuiltin, export_alias("__sinf")]] sinf(*) %{generate(double2float("sin"))}
[[std, crtbuiltin, export_alias("__tanf")]] tanf(*) %{generate(double2float("tan"))}

%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[[std, crtbuiltin, export_alias("__acosl"), ldouble_variant_of("acos", ...)]] acosl(*) %{generate(double2ldouble("acos"))}
[[std, crtbuiltin, export_alias("__asinl"), ldouble_variant_of("asin", ...)]] asinl(*) %{generate(double2ldouble("asin"))}
[[std, crtbuiltin, export_alias("__atanl"), ldouble_variant_of("atan", ...)]] atanl(*) %{generate(double2ldouble("atan"))}
[[std, crtbuiltin, export_alias("__atan2l"), ldouble_variant_of("atan2", ...)]] atan2l(*) %{generate(double2ldouble("atan2"))}
[[std, crtbuiltin, export_alias("__cosl"), ldouble_variant_of("cos", ...)]] cosl(*) %{generate(double2ldouble("cos"))}
[[std, crtbuiltin, export_alias("__sinl"), ldouble_variant_of("sin", ...)]] sinl(*) %{generate(double2ldouble("sin"))}
[[std, crtbuiltin, export_alias("__tanl"), ldouble_variant_of("tan", ...)]] tanl(*) %{generate(double2ldouble("tan"))}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */

%(std, c)
%(std, c)/* Hyperbolic functions. */

@@>> coshf(3), cosh(3), coshl(3)
@@Hyperbolic   cosine   of   `x'
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__cosh")]]
[[impl_include("<libm/finite.h>", "<libm/cosh.h>", "<libm/matherr.h>")]]
[[requires_include("<ieee754.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double cosh(double x) {
	double result = __LIBM_MATHFUN(@cosh@, x);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
		!__LIBM_MATHFUNI(@finite@, result) && __LIBM_MATHFUNI(@finite@, x))
		result = __kernel_standard(x, x, result, __LIBM_KMATHERR_COSH);
	return result;
}

@@>> sinhf(3), sinh(3), sinhl(3)
@@Hyperbolic sine of `x'
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__sinh")]]
[[impl_include("<libm/finite.h>", "<libm/sinh.h>", "<libm/matherr.h>")]]
[[requires_include("<ieee754.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double sinh(double x) {
	double result = __LIBM_MATHFUN(@sinh@, x);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
		!__LIBM_MATHFUNI(@finite@, result) && __LIBM_MATHFUNI(@finite@, x))
		result = __kernel_standard(x, x, result, __LIBM_KMATHERR_SINH);
	return result;
}

@@>> tanhf(3), tanh(3), tanhl(3)
@@Hyperbolic   tangent   of  `x'
[[std, const, wunused, nothrow, crtbuiltin, export_alias("__tanh")]]
[[impl_include("<libm/tanh.h>")]]
[[requires_include("<ieee754.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double tanh(double x) {
	return __LIBM_MATHFUN(@tanh@, x);
}

[[std, crtbuiltin, export_alias("__coshf")]] coshf(*) %{generate(double2float("cosh"))}
[[std, crtbuiltin, export_alias("__sinhf")]] sinhf(*) %{generate(double2float("sinh"))}
[[std, crtbuiltin, export_alias("__tanhf")]] tanhf(*) %{generate(double2float("tanh"))}
%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[[std, crtbuiltin, export_alias("__coshl"), ldouble_variant_of("cosh", ...)]] coshl(*) %{generate(double2ldouble("cosh"))}
[[std, crtbuiltin, export_alias("__sinhl"), ldouble_variant_of("sinh", ...)]] sinhl(*) %{generate(double2ldouble("sinh"))}
[[std, crtbuiltin, export_alias("__tanhl"), ldouble_variant_of("tanh", ...)]] tanhl(*) %{generate(double2ldouble("tanh"))}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */

%(std, c)
%(std, c, ccompat)#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)

@@>> acoshf(3), acosh(3), acoshl(3)
@@Hyperbolic  arc  cosine  of   `x'
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__acosh")]]
[[impl_include("<libm/fcomp.h>", "<libm/matherr.h>")]]
[[impl_include("<libm/nan.h>", "<libm/acosh.h>")]]
[[requires_include("<ieee754.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double acosh(double x) {
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
		__LIBM_MATHFUNI2(@isless@, x, 1.0)) /* acosh(x<1) */
		return __kernel_standard(x, x, __LIBM_MATHFUN1I(@nan@, ""), __LIBM_KMATHERR_ACOSH);
	return __LIBM_MATHFUN(@acosh@, x);
}

@@>> asinhf(3), asinh(3), asinhl(3)
@@Hyperbolic  arc   sine   of   `x'
[[std, const, wunused, nothrow, crtbuiltin, export_alias("__asinh")]]
[[impl_include("<libm/asinh.h>")]]
[[requires_include("<ieee754.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double asinh(double x) {
	return __LIBM_MATHFUN(@asinh@, x);
}

@@>> atanhf(3), atanh(3), atanhl(3)
@@Hyperbolic  arc  tangent  of  `x'
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__atanh")]]
[[impl_include("<libm/fcomp.h>", "<libm/fabs.h>")]]
[[impl_include("<bits/math-constants.h>", "<libm/matherr.h>")]]
[[impl_include("<libm/nan.h>", "<libm/atanh.h>")]]
[[requires_include("<ieee754.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double atanh(double x) {
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    __LIBM_MATHFUNI2(@isgreaterequal@, __LIBM_MATHFUN(@fabs@, x), 1.0))
		return __kernel_standard(x, x, __HUGE_VAL,
		                         __LIBM_MATHFUN(@fabs@, x) > 1.0 ? __LIBM_KMATHERR_ATANH_PLUSONE /* atanh(|x|>1) */
		                                                         : __LIBM_KMATHERR_ATANH_ONE);   /* atanh(|x|==1) */
	return __LIBM_MATHFUN(@atanh@, x);
}

[[std, crtbuiltin, export_alias("__acoshf")]] acoshf(*) %{generate(double2float("acosh"))}
[[std, crtbuiltin, export_alias("__asinhf")]] asinhf(*) %{generate(double2float("asinh"))}
[[std, crtbuiltin, export_alias("__atanhf")]] atanhf(*) %{generate(double2float("atanh"))}

%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[[std, crtbuiltin, export_alias("__acoshl"), ldouble_variant_of("acosh", ...)]] acoshl(*) %{generate(double2ldouble("acosh"))}
[[std, crtbuiltin, export_alias("__asinhl"), ldouble_variant_of("asinh", ...)]] asinhl(*) %{generate(double2ldouble("asinh"))}
[[std, crtbuiltin, export_alias("__atanhl"), ldouble_variant_of("atanh", ...)]] atanhl(*) %{generate(double2ldouble("atanh"))}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std, c, ccompat)#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */

%(std, c)
%(std, c)/* Exponential and logarithmic functions. */

@@>> expf(3), exp(3), expl(3)
@@Exponential function of `x'
[[attribute("__DECL_SIMD_exp"), decl_include("<bits/crt/math-vector.h>")]]
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__exp")]]
[[impl_include("<libm/signbit.h>", "<libm/finite.h>")]]
[[impl_include("<libm/matherr.h>", "<libm/exp.h>")]]
[[requires_include("<ieee754.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double exp(double x) {
	double result;
	result = __LIBM_MATHFUN(@exp@, x);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    (!__LIBM_MATHFUNI(@finite@, result) || result == 0.0) &&
	    __LIBM_MATHFUNI(@finite@, x)) {
		return __kernel_standard(x, x, result,
		                         __LIBM_MATHFUNI(@signbit@, x)
		                         ? __LIBM_KMATHERR_EXP_UNDERFLOW
		                         : __LIBM_KMATHERR_EXP_OVERFLOW);
	}
	return result;
}

@@>> frexpf(3), frexp(3), frexpl(3)
@@Break `value' into a normalized fraction and an integral power of 2
[[std, crtbuiltin, export_alias("__frexp")]]
[[requires_include("<ieee754.h>"), impl_include("<libm/frexp.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double frexp(double x, [[out]] int *pexponent) {
	return __LIBM_MATHFUN2I(@frexp@, x, pexponent);
}

@@>> ldexpf(3), ldexp(3), ldexpl(3)
@@`x' times (two to the `exponent' power)
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__ldexp")]]
[[impl_include("<libc/errno.h>", "<libm/finite.h>", "<libm/ldexp.h>")]]
[[requires_include("<ieee754.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double ldexp(double x, int exponent) {
	double result;
	result = __LIBM_MATHFUN2I(@ldexp@, x, exponent);
@@pp_ifdef ERANGE@@
	if unlikely(!__LIBM_MATHFUNI(@finite@, result) || result == 0.0)
		(void)libc_seterrno(ERANGE);
@@pp_endif@@
	return result;
}

@@>> logf(3), log(3), logl(3)
@@Natural  logarithm  of  `x'
[[attribute("__DECL_SIMD_log"), decl_include("<bits/crt/math-vector.h>")]]
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__log")]]
[[requires_include("<ieee754.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
[[impl_include("<asm/crt/fenv.h>", "<bits/math-constants.h>", "<libm/nan.h>")]]
[[impl_include("<libm/log.h>", "<libm/fcomp.h>", "<libm/matherr.h>")]]
double log(double x) {
	if (__LIBM_LIB_VERSION != __LIBM_IEEE && __LIBM_MATHFUNI2(@islessequal@, x, -1.0)) {
		if (x == -1.0) {
@@pp_if $has_function(feraiseexcept) && defined(FE_DIVBYZERO)@@
			feraiseexcept(FE_DIVBYZERO);
@@pp_endif@@
			return __kernel_standard(x, x, -__HUGE_VAL, __LIBM_KMATHERR_LOG_ZERO); /* log(0) */
		} else {
@@pp_if $has_function(feraiseexcept) && defined(FE_INVALID)@@
			feraiseexcept(FE_INVALID);
@@pp_endif@@
			return __kernel_standard(x, x, __LIBM_MATHFUN1I(@nan@, ""), __LIBM_KMATHERR_LOG_MINUS); /* log(x<0) */
		}
	}
	return __LIBM_MATHFUN(@log@, x);
}



@@>> log10f(3), log10(3), log10l(3)
@@Base-ten    logarithm    of   `x'
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__log10")]]
[[requires_include("<ieee754.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
[[impl_include("<asm/crt/fenv.h>", "<bits/math-constants.h>", "<libm/nan.h>")]]
[[impl_include("<libm/log10.h>", "<libm/fcomp.h>", "<libm/matherr.h>")]]
double log10(double x) {
	if (__LIBM_LIB_VERSION != __LIBM_IEEE && __LIBM_MATHFUNI2(@islessequal@, x, 0.0)) {
		if (x == 0.0) {
@@pp_if $has_function(feraiseexcept) && defined(FE_DIVBYZERO)@@
			feraiseexcept(FE_DIVBYZERO);
@@pp_endif@@
			return __kernel_standard(x, x, -__HUGE_VAL, __LIBM_KMATHERR_LOG10_ZERO); /* log10(0) */
		} else {
@@pp_if $has_function(feraiseexcept) && defined(FE_INVALID)@@
			feraiseexcept(FE_INVALID);
@@pp_endif@@
			return __kernel_standard(x, x, __LIBM_MATHFUN1I(@nan@, ""), __LIBM_KMATHERR_LOG10_MINUS); /* log10(x<0) */
		}
	}
	return __LIBM_MATHFUN(@log10@, x);
}

@@>> modff(3), modf(3), modfl(3)
@@Break `value' into integral and fractional parts
[[std, wunused, crtbuiltin, export_alias("__modf")]]
[[requires_include("<ieee754.h>"), impl_include("<libm/modf.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double modf(double x, [[out]] double *iptr) {
	return __LIBM_MATHFUN2I(@modf@, x, (__LIBM_MATHFUN_T *)iptr);
}


[[std, crtbuiltin, export_alias("__expf")]]   expf(*)   %{generate(double2float("exp"))}
[[std, crtbuiltin, export_alias("__frexpf")]] frexpf(*) %{generate(double2float("frexp"))}
[[std, crtbuiltin, export_alias("__ldexpf")]] ldexpf(*) %{generate(double2float("ldexp"))}
[[std, crtbuiltin, export_alias("__logf")]]   logf(*)   %{generate(double2float("log"))}
[[std, crtbuiltin, export_alias("__log10f")]] log10f(*) %{generate(double2float("log10"))}
[[std, crtbuiltin, export_alias("__modff")]]  modff(*)  %{generate(double2float("modf"))}

%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[[std, crtbuiltin, export_alias("__expl"), ldouble_variant_of("exp", ...)]]   expl(*)   %{generate(double2ldouble("exp"))}
[[std, crtbuiltin, export_alias("__frexpl"), ldouble_variant_of("frexp", ...)]] frexpl(*) %{generate(double2ldouble("frexp"))}
[[std, crtbuiltin, export_alias("__ldexpl"), ldouble_variant_of("ldexp", ...)]] ldexpl(*) %{generate(double2ldouble("ldexp"))}
[[std, crtbuiltin, export_alias("__logl"), ldouble_variant_of("log", ...)]]   logl(*)   %{generate(double2ldouble("log"))}
[[std, crtbuiltin, export_alias("__log10l"), ldouble_variant_of("log10", ...)]] log10l(*) %{generate(double2ldouble("log10"))}
[[std, crtbuiltin, export_alias("__modfl"), ldouble_variant_of("modf", ...)]]  modfl(*)  %{generate(double2ldouble("modf"))}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */

%(std, c)
%(std, c, ccompat)#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)

@@>> expm1f(3), expm1(3), expm1l(3)
@@Return `exp(x) - 1'
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__expm1")]]
[[impl_include("<libm/matherr.h>", "<libm/signbit.h>")]]
[[impl_include("<libm/finite.h>", "<libm/expm1.h>")]]
[[requires_include("<ieee754.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double expm1(double x) {
	double result;
	result = __LIBM_MATHFUN(@expm1@, x);
	if ((!__LIBM_MATHFUNI(@finite@, result) || result == -1.0) &&
	    __LIBM_MATHFUNI(@finite @, x) && __LIBM_LIB_VERSION != __LIBM_IEEE) {
		return __kernel_standard(x, x, result,
		                         __LIBM_MATHFUNI(@signbit@, x)
		                         ? __LIBM_KMATHERR_EXPM1_UNDERFLOW
		                         : __LIBM_KMATHERR_EXPM1_OVERFLOW);
	}
	return result;
}

@@>> log1pf(3), log1p(3), log1pl(3)
@@Return `log(1 + x)'
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__log1p")]]
[[requires_include("<ieee754.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
[[impl_include("<asm/crt/fenv.h>", "<bits/math-constants.h>", "<libm/nan.h>")]]
[[impl_include("<libm/log1p.h>", "<libm/fcomp.h>", "<libm/matherr.h>")]]
double log1p(double x) {
	if (__LIBM_MATHFUNI2(@islessequal@, x, -1.0) && __LIBM_LIB_VERSION != __LIBM_IEEE) {
		if (x == -1.0) {
@@pp_if $has_function(feraiseexcept) && defined(FE_DIVBYZERO)@@
			feraiseexcept(FE_DIVBYZERO);
@@pp_endif@@
			return __kernel_standard(x, x, -__HUGE_VAL, __LIBM_KMATHERR_LOG_ZERO); /* log(0) */
		} else {
@@pp_if $has_function(feraiseexcept) && defined(FE_INVALID)@@
			feraiseexcept(FE_INVALID);
@@pp_endif@@
			return __kernel_standard(x, x, __LIBM_MATHFUN1I(@nan@, ""), __LIBM_KMATHERR_LOG_MINUS); /* log(x<0) */
		}
	}
	return __LIBM_MATHFUN(@log1p@, x);
}

@@>> logbf(3), logb(3), logbl(3)
@@Return the base 2 signed integral exponent of `x'
[[std, const, wunused, nothrow, crtbuiltin]]
[[export_alias("__logb"), dos_only_export_alias("_logb")]]
[[requires_include("<ieee754.h>"), impl_include("<libm/logb.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double logb(double x) {
	return __LIBM_MATHFUN(@logb@, x);
}


[[std, crtbuiltin, export_alias("__expm1f")]] expm1f(*) %{generate(double2float("expm1"))}
[[std, crtbuiltin, export_alias("__log1pf")]] log1pf(*) %{generate(double2float("log1p"))}
[[std, crtbuiltin, export_alias("__logbf"), alias("_logbf")]]
/* For some reason, only exported on x86_64 (s.a. <crt-features/crt-dos.h>) */
[[if(defined(__x86_64__)), dos_only_export_as("_logbf")]]
logbf(*) %{generate(double2float("logb"))}
%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[[std, crtbuiltin, export_alias("__expm1l"), ldouble_variant_of("expm1", ...)]] expm1l(*) %{generate(double2ldouble("expm1"))}
[[std, crtbuiltin, export_alias("__log1pl"), ldouble_variant_of("log1p", ...)]] log1pl(*) %{generate(double2ldouble("log1p"))}
[[std, crtbuiltin, export_alias("__logbl"), ldouble_variant_of("logb", ...)]]  logbl(*)  %{generate(double2ldouble("logb"))}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std, c, ccompat)#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */

%(std, c)
%(std, c, ccompat)#ifdef __USE_ISOC99

@@>> exp2f(3), exp2(3), exp2l(3)
@@Compute base-2 exponential of `x'
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__exp2")]]
[[requires_include("<ieee754.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
[[impl_include("<libm/exp2.h>", "<libm/matherr.h>")]]
[[impl_include("<libm/finite.h>", "<libm/signbit.h>")]]
double exp2(double x) {
	double result = __LIBM_MATHFUN(@exp2@, x);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE && !__LIBM_MATHFUNI(@finite@, result) && __LIBM_MATHFUNI(@finite@, x)) {
		return __kernel_standard(x, x, result,
		                         __LIBM_MATHFUNI(@signbit@, x)
		                         ? __LIBM_KMATHERR_EXP2_UNDERFLOW
		                         : __LIBM_KMATHERR_EXP2_OVERFLOW);
	}
	return result;
}

@@>> log2f(3), log2(3), log2l(3)
@@Compute base-2 logarithm of `x'
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__log2")]]
[[requires_include("<ieee754.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
[[impl_include("<asm/crt/fenv.h>", "<bits/math-constants.h>", "<libm/nan.h>")]]
[[impl_include("<libm/log2.h>", "<libm/fcomp.h>", "<libm/matherr.h>")]]
double log2(double x) {
	if (__LIBM_LIB_VERSION != __LIBM_IEEE && __LIBM_MATHFUNI2(@islessequal@, x, 0.0)) {
		if (x == 0.0) {
@@pp_if $has_function(feraiseexcept) && defined(FE_DIVBYZERO)@@
			feraiseexcept(FE_DIVBYZERO);
@@pp_endif@@
			return __kernel_standard(x, x, -__HUGE_VAL,
			                         __LIBM_KMATHERR_LOG2_ZERO); /* log2(0) */
		} else {
@@pp_if $has_function(feraiseexcept) && defined(FE_INVALID)@@
			feraiseexcept(FE_INVALID);
@@pp_endif@@
			return __kernel_standard(x, x, __LIBM_MATHFUN1I(@nan@, ""),
			                         __LIBM_KMATHERR_LOG2_MINUS); /* log2(x<0) */
		}
	}
	return __LIBM_MATHFUN(@log2@, x);
}



[[std, crtbuiltin, export_alias("__exp2f")]] exp2f(*) %{generate(double2float("exp2"))}
[[std, crtbuiltin, export_alias("__log2f")]] log2f(*) %{generate(double2float("log2"))}
%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[[std, crtbuiltin, export_alias("__exp2l"), ldouble_variant_of("exp2", ...)]] exp2l(*) %{generate(double2ldouble("exp2"))}
[[std, crtbuiltin, export_alias("__log2l"), ldouble_variant_of("log2", ...)]] log2l(*) %{generate(double2ldouble("log2"))}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std, c, ccompat)#endif /* __USE_ISOC99 */

%(std, c)
%(std, c)/* Power functions. */

@@>> powf(3), pow(3), powl(3)
@@Return `x' to the `y' power
[[attribute("__DECL_SIMD_pow"), decl_include("<bits/crt/math-vector.h>")]]
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__pow")]]
[[requires_include("<ieee754.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
[[impl_include("<libm/finite.h>", "<libm/isnan.h>", "<libm/matherr.h>")]]
[[impl_include("<libm/pow.h>", "<libm/signbit.h>")]]
double pow(double x, double y) {
	double result;
	result = __LIBM_MATHFUN2(@pow@, x, y);
	/*
	 * ====================================================
	 * Copyright (C) 2004 by Sun Microsystems, Inc. All rights reserved.
	 *
	 * Permission  to use, copy, modify, and distribute this
	 * software is freely granted, provided that this notice
	 * is preserved.
	 * ====================================================
	 */
	if (!__LIBM_MATHFUNI(@finite@, result)) {
		if (__LIBM_MATHFUNI(@isnan@, y) && x == 1.0) {
			result = 1.0;
		} else if (__LIBM_LIB_VERSION != __LIBM_IEEE) {
			if (__LIBM_MATHFUNI(@isnan@, x)) {
				if (y == 0.0) /* pow(NaN,0.0) */
					return __kernel_standard(x, y, result, __LIBM_KMATHERR_POW_NAN);
			} else if (__LIBM_MATHFUNI(@finite@, x) && __LIBM_MATHFUNI(@finite@, y)) {
				if (__LIBM_MATHFUNI(@isnan@, result)) { /* pow neg**non-int */
					return __kernel_standard(x, y, result, __LIBM_KMATHERR_POW_NONINT);
				} else if (x == 0.0 && y < 0.0) {
					if (__LIBM_MATHFUNI(@signbit@, x) && __LIBM_MATHFUNI(@signbit@, result)) { /* pow(-0.0,negative) */
						return __kernel_standard(x, y, result, __LIBM_KMATHERR_POW_MINUS);
					} else { /* pow(+0.0,negative) */
						return __kernel_standard(x, y, result, __LIBM_KMATHERR_POW_ZEROMINUS);
					}
				} else {
					/* pow overflow */
					return __kernel_standard(x, y, result, __LIBM_KMATHERR_POW_OVERFLOW);
				}
			}
		}
	} else if (result == 0.0 &&
	           __LIBM_MATHFUNI(@finite@, x) &&
	           __LIBM_MATHFUNI(@finite@, y) &&
	           __LIBM_LIB_VERSION != __LIBM_IEEE) {
		if (x == 0.0) {
			if (y == 0.0) {
				/* pow(0.0, 0.0) */
				return __kernel_standard(x, y, result, __LIBM_KMATHERR_POW_ZERO);
			}
		} else {
			/* pow underflow */
			return __kernel_standard(x, y, result, __LIBM_KMATHERR_POW_UNDERFLOW);
		}
	}
	return result;
}


@@>> sqrtf(3), sqrt(3), sqrtl(3)
@@Return the square root of  `x'
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__sqrt")]]
[[impl_include("<libm/fcomp.h>", "<libm/nan.h>")]]
[[impl_include("<libm/matherr.h>", "<libm/sqrt.h>")]]
[[requires_include("<ieee754.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double sqrt(double x) {
	if (__LIBM_LIB_VERSION != __LIBM_IEEE && __LIBM_MATHFUNI2(@isless@, x, 0.0))
		return __kernel_standard(x, x, __LIBM_MATHFUN1I(@nan@, ""), __LIBM_KMATHERR_SQRT); /* sqrt(negative) */
	return __LIBM_MATHFUN(@sqrt@, x);
}

[[std, crtbuiltin, export_alias("__powf")]]  powf(*)  %{generate(double2float("pow"))}
[[std, crtbuiltin, export_alias("__sqrtf")]] sqrtf(*) %{generate(double2float("sqrt"))}
%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[[std, crtbuiltin, export_alias("__powl"), ldouble_variant_of("pow", ...)]]  powl(*)  %{generate(double2ldouble("pow"))}
[[std, crtbuiltin, export_alias("__sqrtl"), ldouble_variant_of("sqrt", ...)]] sqrtl(*) %{generate(double2ldouble("sqrt"))}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */

%(std, c)
%(std, c, ccompat)#if defined(__USE_XOPEN) || defined(__USE_ISOC99)

@@>> hypotf(3), hypot(3), hypotl(3)
@@Return `sqrt(x*x + y*y)'
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin]]
[[dos_only_export_alias("_hypot"), export_alias("__hypot")]]
[[impl_include("<libm/finite.h>", "<libm/matherr.h>")]]
[[requires_include("<ieee754.h>"), impl_include("<libm/hypot.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double hypot(double x, double y) {
	double result = __LIBM_MATHFUN2(@hypot@, y, x);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE && !__LIBM_MATHFUNI(@finite@, result) &&
	    __LIBM_MATHFUNI(@finite@, x) && __LIBM_MATHFUNI(@finite@, y))
		return __kernel_standard(x, y, result, __LIBM_KMATHERR_HYPOT); /* hypot overflow */
	return result;
}


[[std, crtbuiltin, dos_only_export_alias("_hypotf"), export_alias("__hypotf")]]
hypotf(*) %{generate(double2float("hypot"))}
%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[[std, crtbuiltin, export_alias("__hypotl"), ldouble_variant_of("hypot", ...)]] hypotl(*) %{generate(double2ldouble("hypot"))}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std, c, ccompat)#endif /* __USE_XOPEN || __USE_ISOC99 */


%(std, c)
%(std, c, ccompat)#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)

@@>> cbrtf(3), cbrt(3), cbrtl(3)
@@Return  the  cube root  of `x'
[[std, const, wunused, nothrow, crtbuiltin, export_alias("__cbrt")]]
[[requires_include("<ieee754.h>"), impl_include("<libm/cbrt.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double cbrt(double x) {
	return __LIBM_MATHFUN(@cbrt@, x);
}

[[std, crtbuiltin, export_alias("__cbrtf")]] cbrtf(*) %{generate(double2float("cbrt"))}
%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[[std, crtbuiltin, export_alias("__cbrtl"), ldouble_variant_of("cbrt", ...)]] cbrtl(*) %{generate(double2ldouble("cbrt"))}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std, c, ccompat)#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */

%(std, c)
%(std, c)/* Nearest integer, absolute value, and remainder functions. */

@@>> ceilf(3), ceil(3), ceill(3)
@@Smallest integral value not less than `x'
[[std, const, wunused, nothrow, crtbuiltin, export_alias("__ceil")]]
[[impl_include("<hybrid/typecore.h>"), impl_include("<libm/ceil.h>")]]
double ceil(double x) {
@@pp_ifdef __LIBM_MATHFUN@@
	return __LIBM_MATHFUN(@ceil@, x);
@@pp_else@@
	double result;
	result = (double)(__INTMAX_TYPE__)x; /* Round towards 0 */
	if (result < x)
		result += 1.0;
	return result;
@@pp_endif@@
}

@@>> fabsf(3), fabs(3), fabsl(3)
@@Absolute value of `x'
[[std, const, wunused, nothrow, crtbuiltin, export_alias("__fabs")]]
[[impl_include("<libm/fabs.h>")]]
double fabs(double x) {
@@pp_ifdef __LIBM_MATHFUN@@
	return __LIBM_MATHFUN(@fabs@, x);
@@pp_else@@
	return x < 0.0 ? -x : x;
@@pp_endif@@
}

@@>> floorf(3), floor(3), floorl(3)
@@Largest integer not greater than `x'
[[std, const, wunused, nothrow, crtbuiltin, export_alias("__floor")]]
[[impl_include("<hybrid/typecore.h>", "<libm/floor.h>")]]
double floor(double x) {
@@pp_ifdef __LIBM_MATHFUN@@
	return __LIBM_MATHFUN(@floor@, x);
@@pp_else@@
	double result;
	result = (double)(__INTMAX_TYPE__)x; /* Round towards 0 */
	if (result > x)
		result -= 1.0;
	return result;
@@pp_endif@@
}


@@>> fmodf(3), fmod(3), fmodl(3)
@@Floating-point modulo remainder of `x / y'
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__fmod")]]
[[impl_include("<libm/isinf.h>", "<libm/fcomp.h>")]]
[[impl_include("<libm/matherr.h>", "<libm/fmod.h>")]]
[[requires_include("<ieee754.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double fmod(double x, double y) {
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    (__LIBM_MATHFUNI(@isinf@, x) || y == 0.0) &&
	    !__LIBM_MATHFUN2(@isunordered@, x, y))
		return __kernel_standard(x, y, y, __LIBM_KMATHERR_FMOD); /* fmod(+-Inf,y) or fmod(x,0) */
	return __LIBM_MATHFUN2(@fmod@, x, y);
}
[[std, crtbuiltin, export_alias("__ceilf")]]  ceilf(*)  %{generate(double2float("ceil"))}
[[std, crtbuiltin, export_alias("__fabsf")]]  fabsf(*)  %{generate(double2float("fabs"))}
[[std, crtbuiltin, export_alias("__floorf")]] floorf(*) %{generate(double2float("floor"))}
[[std, crtbuiltin, export_alias("__fmodf")]]  fmodf(*)  %{generate(double2float("fmod"))}

%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[[std, crtbuiltin, export_alias("__ceill"), ldouble_variant_of("ceil", ...)]]  ceill(*)  %{generate(double2ldouble("ceil"))}
[[std, crtbuiltin, export_alias("__fabsl"), ldouble_variant_of("fabs", ...)]]  fabsl(*)  %{generate(double2ldouble("fabs"))}
[[std, crtbuiltin, export_alias("__floorl"), ldouble_variant_of("floor", ...)]] floorl(*) %{generate(double2ldouble("floor"))}
[[std, crtbuiltin, export_alias("__fmodl"), ldouble_variant_of("fmod", ...)]]  fmodl(*)  %{generate(double2ldouble("fmod"))}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */


%(std, c)
%(std, c, ccompat)#ifdef __USE_ISOC99
@@>> copysignf(3), copysign(3), copysignl(3)
@@Return `x' with its signed changed to `y's
[[std, const, wunused, nothrow, crtbuiltin, export_alias("__copysign", "_copysign")]]
[[impl_include("<libm/copysign.h>")]]
double copysign(double num, double sign) {
@@pp_ifdef __LIBM_MATHFUN2@@
	return __LIBM_MATHFUN2(@copysign@, num, sign);
@@pp_else@@
	if ((num < 0.0) != (sign < 0.0))
		num = -num;
	return num;
@@pp_endif@@
}

@@>> nanf(3), nan(3), nanl(3)
@@Return representation of qNaN for double type
[[std, const, wunused, nothrow, crtbuiltin, export_alias("__nan")]]
[[requires_include("<ieee754.h>"), impl_include("<libm/nan.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double nan(char const *tagb) {
	return __LIBM_MATHFUN1I(@nan@, tagb);
}

[[dos_only_export_alias("_copysignf")]]
[[std, crtbuiltin, export_alias("__copysignf")]] copysignf(*) %{generate(double2float("copysign"))}
[[std, crtbuiltin, export_alias("__nanf")]]      nanf(*)      %{generate(double2float("nan"))}
%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[[std, crtbuiltin, export_alias("__copysignl"), ldouble_variant_of("copysign", ...)]] copysignl(*) %{generate(double2ldouble("copysign"))}
[[std, crtbuiltin, export_alias("__nanl"), ldouble_variant_of("nan", ...)]]      nanl(*)      %{generate(double2ldouble("nan"))}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std, c, ccompat)#endif /* __USE_ISOC99 */



%(std, c)
%(std, c)/* Error and gamma functions. */
%(std, c, ccompat)#if defined(__USE_XOPEN) || defined(__USE_ISOC99)

@@>> erff(3), erf(3), erfl(3)
[[std, const, wunused, nothrow, crtbuiltin, export_alias("__erf")]]
[[requires_include("<ieee754.h>"), impl_include("<libm/erf.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double erf(double x) {
	return __LIBM_MATHFUN(@erf@, x);
}

@@>> erfcf(3), erfc(3), erfcl(3)
[[std, const, wunused, nothrow, crtbuiltin, export_alias("__erfc")]]
[[requires_include("<ieee754.h>"), impl_include("<libm/erfc.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double erfc(double x) {
	return __LIBM_MATHFUN(@erfc@, x);
}

@@>> lgammaf(3), lgamma(3), lgammal(3)
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("gamma", "__lgamma", "__gamma")]]
[[if(__has_builtin(__builtin_gamma) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline("gamma", { return __builtin_gamma(x); })]]
[[requires_include("<libc/template/signgam.h>")]]
[[requires(defined(__LOCAL_signgam) && $has_function(lgamma_r))]]
double lgamma(double x) {
	return lgamma_r(x, &__LOCAL_signgam);
}


[[std, crtbuiltin, export_alias("__erff")]]  erff(*)  %{generate(double2float("erf"))}
[[std, crtbuiltin, export_alias("__erfcf")]] erfcf(*) %{generate(double2float("erfc"))}

[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("gammaf", "__lgammaf", "__gammaf")]]
[[if(__has_builtin(__builtin_gammaf) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline("gammaf", { return __builtin_gammaf(x); })]]
[[requires_include("<libc/template/signgam.h>"), doc_alias("lgamma")]]
[[requires(defined(__LOCAL_signgam) && $has_function(lgammaf_r))]]
float lgammaf(float x) {
	return lgammaf_r(x, &__LOCAL_signgam);
}


%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[[std, crtbuiltin, export_alias("__erfl"), ldouble_variant_of("erf", ...)]]  erfl(*)  %{generate(double2ldouble("erf"))}
[[std, crtbuiltin, export_alias("__erfcl"), ldouble_variant_of("erfc", ...)]] erfcl(*) %{generate(double2ldouble("erfc"))}

[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("gammal", "__lgammal", "__gammal")]]
[[if(__has_builtin(__builtin_gammal) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline("gammal", { return __builtin_gammal(x); })]]
[[requires_include("<libc/template/signgam.h>"), doc_alias("lgamma")]]
[[requires(defined(__LOCAL_signgam) && $has_function(lgammal_r))]]
__LONGDOUBLE lgammal(__LONGDOUBLE x) {
	return lgammal_r(x, &__LOCAL_signgam);
}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std, c, ccompat)#endif /* __USE_XOPEN || __USE_ISOC99 */

%(std, c, ccompat)#ifdef __USE_ISOC99
@@>> tgammaf(3), tgamma(3), tgammal(3)
@@True gamma function
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__tgamma")]]
[[impl_include("<libm/fcomp.h>", "<libm/isinf.h>", "<libm/finite.h>")]]
[[impl_include("<libm/matherr.h>", "<libm/tgamma.h>", "<libm/floor.h>")]]
[[requires_include("<ieee754.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double tgamma(double x) {
	int my_signgam;
	double result = __LIBM_MATHFUN2I(@tgamma@, x, &my_signgam);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE && !__LIBM_MATHFUN1I(@finite@, result) &&
	    (__LIBM_MATHFUN1I(@finite@, x) || __LIBM_MATHFUN1I(@isinf@, x) < 0)) {
		if (x == 0.0)
			return __kernel_standard(x, x, result, __LIBM_KMATHERR_TGAMMA_ZERO); /* tgamma pole */
		if (__LIBM_MATHFUN(@floor@, x) == x && x < 0.0)
			return __kernel_standard(x, x, result, __LIBM_KMATHERR_TGAMMA_MINUS); /* tgamma domain */
		if (result == 0.0)
			return __kernel_standard(x, x, result, __LIBM_KMATHERR_TGAMMA_UNDERFLOW); /* tgamma underflow */
		return __kernel_standard(x, x, result, __LIBM_KMATHERR_TGAMMA_OVERFLOW);      /* tgamma overflow */
	}
	return my_signgam < 0 ? -result : result;
}

[[std, crtbuiltin, export_alias("__tgammaf")]] tgammaf(*) %{generate(double2float("tgamma"))}
%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[[std, crtbuiltin, export_alias("__tgammal"), ldouble_variant_of("tgamma", ...)]] tgammal(*) %{generate(double2ldouble("tgamma"))}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std, c, ccompat)#endif /* __USE_ISOC99 */

%(std, c)
%(std, c, ccompat)#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)

@@>> rintf(3), rint(3), rintl(3)
@@Return the integer nearest `x' in the direction of the prevailing rounding mode
[[std, const, wunused, nothrow, crtbuiltin, export_alias("nearbyint", "__rint", "__nearbyint")]]
[[if(__has_builtin(__builtin_nearbyint) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline("nearbyint", { return __builtin_nearbyint(x); })]]
[[requires_include("<ieee754.h>"), impl_include("<libm/rint.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double rint(double x) {
	return __LIBM_MATHFUN(@rint@, x);
}


@@>> nextafterf(3), nextafter(3), nextafterl(3)
@@Return `x + epsilon' if `x < y', and `x - epsilon' if `x > y'
[[std, const, wunused, nothrow, crtbuiltin, export_alias("nexttoward")]]
[[export_alias("__nextafter")]]
[[dos_only_export_alias("_nextafter")]]
[[export_alias("__nexttoward")]]
[[if(__has_builtin(__builtin_nexttoward) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline("nexttoward", { return __builtin_nexttoward(x); })]]
[[requires_include("<ieee754.h>"), impl_include("<libm/nextafter.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double nextafter(double x, double y) {
	return __LIBM_MATHFUN2(@nextafter@, x, y);
}

@@>> remainderf(3), remainder(3), remainderl(3)
@@Return the remainder of integer division `x / p' with infinite precision
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("drem", "__remainder", "__drem")]]
[[if(__has_builtin(__builtin_drem) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline("drem", { return __builtin_drem(x, p); })]]
[[impl_include("<libm/matherr.h>", "<libm/isnan.h>")]]
[[impl_include("<libm/isinf.h>", "<libm/remainder.h>")]]
[[requires_include("<ieee754.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double remainder(double x, double p) {
	if (((p == 0.0 && !__LIBM_MATHFUNI(@isnan@, x)) ||
	     (__LIBM_MATHFUNI(@isinf@, x) && !__LIBM_MATHFUNI(@isnan@, p))) &&
	    __LIBM_LIB_VERSION != __LIBM_IEEE)
		return __kernel_standard(x, p, p, __LIBM_KMATHERR_REMAINDER); /* remainder domain */
	return __LIBM_MATHFUN2(@remainder@, x, p);
}

@@>> ilogbf(3), ilogb(3), ilogbl(3)
@@Return the binary exponent of `x', which must be nonzero
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__), alias("llogb")]]
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__ilogb")]]
[[impl_include("<libm/ilogb.h>", "<libm/matherr.h>", "<bits/crt/mathdef.h>")]]
[[requires_include("<ieee754.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__))]]
int ilogb(double x) {
	int result;
	result = __LIBM_MATHFUNI(@ilogb@, x);
	if (result == __FP_ILOGB0 || result == __FP_ILOGBNAN || result == INT_MAX)
		__kernel_standard(x, x, x, __LIBM_KMATHERR_ILOGB);
	return result;
}

[[std, const, wunused, nothrow, crtbuiltin, export_alias("nearbyintf", "__rintf", "__nearbyintf")]]
[[if(__has_builtin(__builtin_nearbyintf) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline("nearbyintf", { return __builtin_nearbyintf(x); })]]
float rintf(float x) %{generate(double2float("rint"))}

[[std, const, wunused, nothrow, crtbuiltin]]
[[export_alias("nexttowardf", "__nextafterf", "__nexttowardf"), alias("_nextafterf")]]
[[if(__has_builtin(__builtin_nexttowardf) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline("nexttowardf", { return __builtin_nexttowardf(x); })]]
/* For some reason, only exported on x86_64 (s.a. <crt-features/crt-dos.h>) */
[[if(defined(__x86_64__)), dos_only_export_as("_nextafterf")]]
float nextafterf(float x, float y) %{generate(double2float("nextafter"))}

[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("dremf", "__remainderf", "__dremf")]]
[[if(__has_builtin(__builtin_dremf) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline("dremf", { return __builtin_dremf(x, p); })]]
float remainderf(float x, float p) %{generate(double2float("remainder"))}

[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__), alias("llogbf")]]
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__ilogbf")]]
int ilogbf(float x) %{generate(double2float("ilogb"))}


%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[[std, const, wunused, nothrow, crtbuiltin, export_alias("nearbyintl", "__rintl", "__nearbyintl")]]
[[if(__has_builtin(__builtin_nearbyintl) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline("nearbyintl", { return __builtin_nearbyintl(x); })]]
[[ldouble_variant_of("rint", ...)]]
__LONGDOUBLE rintl(__LONGDOUBLE x) %{generate(double2ldouble("rint"))}

[[std, const, wunused, nothrow, crtbuiltin, export_alias("nexttowardl", "__nextafterl", "__nexttowardl")]]
[[if(__has_builtin(__builtin_nexttowardl) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline("nexttowardl", { return __builtin_nexttowardl(x); })]]
[[ldouble_variant_of("nextafter", ...)]]
__LONGDOUBLE nextafterl(__LONGDOUBLE x, __LONGDOUBLE y) %{generate(double2ldouble("nextafter"))}

[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("dreml", "__remainderl", "__dreml")]]
[[if(__has_builtin(__builtin_dreml) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline("dreml", { return __builtin_dreml(x, p); })]]
[[ldouble_variant_of("remainder", ...)]]
__LONGDOUBLE remainderl(__LONGDOUBLE x, __LONGDOUBLE p) %{generate(double2ldouble("remainder"))}

[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__ && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)), alias("llogb")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__), alias("llogbl")]]
[[std, wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__ilogbl")]]
[[ldouble_variant_of("ilogb", ...)]]
int ilogbl(__LONGDOUBLE x) %{generate(double2ldouble("ilogb"))}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std, c, ccompat)#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */



%(std, c)
%(std, c, ccompat)#ifdef __USE_ISOC99

@@>> nexttowardf(3), nexttoward(3), nexttowardl(3)
[[std, const, wunused, nothrow, crtbuiltin, export_alias("__nexttoward")]]
[[requires_include("<ieee754.h>"), impl_include("<libm/nexttoward.h>")]]
[[requires(((defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
             defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__)) &&
            defined(__IEEE854_LONG_DOUBLE_TYPE__)) ||
            $has_function(nextafterl))]]
[[if($extended_include_prefix("<hybrid/typecore.h>")defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)), crt_intern_alias("nextafter")]]
double nexttoward(double x, __LONGDOUBLE y) {
@@pp_ifdef      __IEEE854_LONG_DOUBLE_TYPE__@@
@@pp_ifdef __IEEE754_DOUBLE_TYPE_IS_DOUBLE__@@
	return (double)__ieee754_nexttoward((__IEEE754_DOUBLE_TYPE__)x, (__IEEE854_LONG_DOUBLE_TYPE__)y);
@@pp_else@@
	return (double)__ieee754_nexttowardf((__IEEE754_FLOAT_TYPE__)x, (__IEEE854_LONG_DOUBLE_TYPE__)y);
@@pp_endif@@
@@pp_else@@
	return (double)nextafterl((__LONGDOUBLE)x, y);
@@pp_endif@@
}

@@>> scalbnf(3), scalbn(3), scalbnl(3), scalblnf(3), scalbln(3), scalblnl(3)
@@Return `x' times (2 to the Nth power)
[[std, const, wunused, nothrow, crtbuiltin, export_alias("__scalbn")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__), alias("scalbln", "__scalbln")]]
[[requires_include("<ieee754.h>"), impl_include("<libm/scalbn.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double scalbn(double x, int n) {
	return __LIBM_MATHFUN2I(@scalbn@, x, n);
}

[[doc_alias("scalbn")]]
[[std, const, wunused, nothrow, crtbuiltin, export_alias("__scalbln")]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__, scalbn)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__), alias("__scalbn")]]
[[requires_include("<ieee754.h>"), impl_include("<libm/scalbn.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double scalbln(double x, long int n) {
	return __LIBM_MATHFUN2I(@scalbln@, x, n);
}

@@>> nearbyintf(3), nearbyint(3), nearbyintl(3)
@@Return the integer nearest `x' in the direction of the prevailing rounding mode
@@This function is similar to `rint()', but does not tend to produce wrong results (so use this one)
[[std, const, wunused, nothrow, nocrt, alias("nearbyint", "__nearbyint", "rint", "__rint")]]
[[if(__has_builtin(__builtin_nearbyint) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline("nearbyint", { return __builtin_nearbyint(x); })]]
[[if($extended_include_prefix("<ieee754.h>")defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
                                            defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
                                            defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)),
  bind_local_function(rint)]]
double nearbyint(double x);



@@>> roundf(3), round(3), roundl(3)
@@Round `x' to nearest integral value, rounding halfway cases away from zero
[[std, const, wunused, nothrow, crtbuiltin, export_alias("__round")]]
[[impl_include("<hybrid/typecore.h>", "<libm/round.h>")]]
double round(double x) {
@@pp_ifdef __LIBM_MATHFUN@@
	return (double)__LIBM_MATHFUN(@round@, x);
@@pp_else@@
	double result;
	result = (double)(__INTMAX_TYPE__)x;
	if (x < 0.0) {
		/* result >= x */
		if ((result - x) >= 0.5)
			result -= 1.0;
	} else {
		/* result <= x */
		if ((x - result) >= 0.5)
			result += 1.0;
	}
	return result;
@@pp_endif@@
}

@@>> truncf(3), trunc(3), truncl(3)
@@Round `x' to the integral value in floating-point
@@format   nearest  but  not  larger  in  magnitude
[[std, const, wunused, nothrow, crtbuiltin, export_alias("__trunc")]]
[[impl_include("<hybrid/typecore.h>", "<libm/trunc.h>")]]
double trunc(double x) {
@@pp_ifdef __LIBM_MATHFUN@@
	return __LIBM_MATHFUN(@trunc@, x);
@@pp_else@@
	return (double)(__INTMAX_TYPE__)x;
@@pp_endif@@
}

@@>> remquof(3), remquo(3), remquol(3)
@@Compute remainder of `x' and `p' and put in `*pquo' a value with
@@sign of x/p and magnitude  congruent `mod 2^n' to the  magnitude
@@of the integral quotient x/p, with n >= 3
[[std, wunused, nothrow, crtbuiltin, export_alias("__remquo")]]
[[requires_include("<ieee754.h>"), impl_include("<libm/remquo.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double remquo(double x, double p, [[out]] int *pquo) {
	return __LIBM_MATHFUN3I(@remquo@, x, p, pquo);
}

@@>> lrintf(3), lrint(3), lrintl(3)
@@Round `x' to nearest integral value according to current rounding direction
[[std, const, wunused, nothrow, crtbuiltin, export_alias("__lrint")]]
[[impl_include("<hybrid/typecore.h>", "<libm/lrint.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias("llrint")]]
long int lrint(double x) {
@@pp_ifdef __LIBM_MATHFUNI@@
	return __LIBM_MATHFUNI(@lrint@, x);
@@pp_else@@
	return (long int)rint(x);
@@pp_endif@@
}

@@>> lroundf(3), lround(3), lroundl(3)
@@Round `x' to nearest integral value, rounding halfway cases away from zero
[[std, const, wunused, nothrow, crtbuiltin, export_alias("__lround")]]
[[impl_include("<hybrid/typecore.h>", "<libm/lround.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias("llround")]]
long int lround(double x) {
@@pp_ifdef __LIBM_MATHFUNI@@
	return __LIBM_MATHFUNI(@lround@, x);
@@pp_else@@
	return (long int)round(x);
@@pp_endif@@
}

@@>> fdimf(3), fdim(3), fdiml(3)
@@Return positive difference between `x' and `y'
[[std, const, wunused, nothrow, crtbuiltin, export_alias("__fdim")]]
double fdim(double x, double y) {
	/* TODO: ieee754-specific function */
	return fabs(y - x);
}

@@>> fmaxf(3), fmax(3), fmaxl(3)
@@Return maximum numeric value from `x' and `y'
[[std, const, wunused, nothrow, crtbuiltin, export_alias("__fmax")]]
[[impl_include("<ieee754.h>", "<libm/fcomp.h>", "<libm/isnan.h>")]]
double fmax(double x, double y) {
@@pp_if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)@@
	if (__LIBM_MATHFUNI2(@isgreaterequal@, x, y))
		return x;
	if (__LIBM_MATHFUNI(@isnan@, y))
		return x;
@@pp_else@@
	if (x >= y)
		return x;
@@pp_endif@@
	return y;
}

@@>> fminf(3), fmin(3), fminl(3)
@@Return minimum numeric value from `x' and `y'
[[std, const, wunused, nothrow, crtbuiltin, export_alias("__fmin")]]
[[impl_include("<ieee754.h>", "<libm/fcomp.h>", "<libm/isnan.h>")]]
double fmin(double x, double y) {
@@pp_if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)@@
	if (__LIBM_MATHFUNI2(@islessequal@, x, y))
		return x;
	if (__LIBM_MATHFUNI(@isnan@, y))
		return x;
@@pp_else@@
	if (x <= y)
		return x;
@@pp_endif@@
	return y;
}

@@>> fmaf(3), fma(3), fmal(3)
@@Multiply-add function computed as a ternary operation
[[std, const, wunused, nothrow, crtbuiltin, export_alias("__fma")]]
double fma(double x, double y, double z) {
	/* TODO: ieee754-specific function */
	return (x * y) + z;
}

%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGLONG
@@>> llrintf(3), llrint(3), llrintl(3)
@@Round `x' to nearest integral value according to current rounding direction
[[std, const, wunused, nothrow, crtbuiltin, export_alias("__llrint")]]
[[impl_include("<hybrid/typecore.h>", "<libm/lrint.h>")]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__, lrint)]]
__LONGLONG llrint(double x) {
@@pp_ifdef __LIBM_MATHFUNI@@
	return __LIBM_MATHFUNI(@llrint@, x);
@@pp_else@@
	return (__LONGLONG)rint(x);
@@pp_endif@@
}

@@>> llroundf(3), llround(3), llroundl(3)
@@Round `x' to nearest integral value, rounding halfway cases away from zero
[[std, const, wunused, nothrow, crtbuiltin, export_alias("__llround")]]
[[impl_include("<hybrid/typecore.h>", "<libm/lround.h>")]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__, lround)]]
__LONGLONG llround(double x) {
@@pp_ifdef __LIBM_MATHFUNI@@
	return __LIBM_MATHFUNI(@llround@, x);
@@pp_else@@
	return (__LONGLONG)round(x);
@@pp_endif@@
}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGLONG */

[[std, const, wunused, nothrow, crtbuiltin, export_alias("__nexttowardf"), doc_alias("nexttoward")]]
[[requires_include("<ieee754.h>"), impl_include("<libm/nexttoward.h>")]]
[[requires(((defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) ||
             defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__)) &&
            defined(__IEEE854_LONG_DOUBLE_TYPE__)) ||
            $has_function(nextafterl))]]
float nexttowardf(float x, __LONGDOUBLE y) {
@@pp_ifdef    __IEEE854_LONG_DOUBLE_TYPE__@@
@@pp_ifdef __IEEE754_FLOAT_TYPE_IS_FLOAT__@@
	return (float)__ieee754_nexttowardf((__IEEE754_FLOAT_TYPE__)x, (__IEEE854_LONG_DOUBLE_TYPE__)y);
@@pp_else@@
	return (float)__ieee754_nexttoward((__IEEE754_DOUBLE_TYPE__)x, (__IEEE854_LONG_DOUBLE_TYPE__)y);
@@pp_endif@@
@@pp_elif defined(__IEEE754_DOUBLE_TYPE__) && defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__)@@
	return (float)__ieee754_nexttowardf_d((__IEEE754_FLOAT_TYPE__)x, (__IEEE754_DOUBLE_TYPE__)y);
@@pp_else@@
	return (float)nextafterl((__LONGDOUBLE)x, y);
@@pp_endif@@
}



[[std, const, wunused, nothrow, crtbuiltin, export_alias("__scalbnf")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__), alias("scalblnf", "__scalblnf")]]
float scalbnf(float x, int n) %{generate(double2float("scalbn"))}

[[std, const, wunused, nothrow, crtbuiltin, export_alias("__scalblnf")]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__, scalbnf)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__), alias("__scalbnf")]]
float scalblnf(float x, long int n) %{generate(double2float("scalbln"))}

[[std, const, wunused, nothrow, doc_alias("nearbyint")]]
[[nocrt, alias("nearbyintf", "__nearbyintf", "rintf", "__rintf")]]
[[if(__has_builtin(__builtin_nearbyintf) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline("nearbyintf", { return __builtin_nearbyintf(x); })]]
[[if($extended_include_prefix("<ieee754.h>")defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) ||
                                            defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) ||
                                            defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)),
  bind_local_function(rintf)]]
float nearbyintf(float x);

[[std, crtbuiltin, export_alias("__roundf")]]  roundf(*)  %{generate(double2float("round"))}
[[std, crtbuiltin, export_alias("__truncf")]]  truncf(*)  %{generate(double2float("trunc"))}
[[std, crtbuiltin, export_alias("__remquof")]] remquof(*) %{generate(double2float("remquo"))}

[[std, const, wunused, nothrow, crtbuiltin, export_alias("__lrintf")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias("llrintf", "__llrintf")]]
long int lrintf(float x) %{generate(double2float("lrint"))}

[[std, const, wunused, nothrow, crtbuiltin, export_alias("__lroundf")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias("llroundf", "__llroundf")]]
long int lroundf(float x) %{generate(double2float("lround"))}

[[std, crtbuiltin, export_alias("__fdimf")]] fdimf(*) %{generate(double2float("fdim"))}
[[std, crtbuiltin, export_alias("__fmaxf")]] fmaxf(*) %{generate(double2float("fmax"))}
[[std, crtbuiltin, export_alias("__fminf")]] fminf(*) %{generate(double2float("fmin"))}
[[std, crtbuiltin, export_alias("__fmaf")]]  fmaf(*)  %{generate(double2float("fma"))}

%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGLONG
[[std, const, wunused, nothrow, crtbuiltin, export_alias("__llrintf")]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__, lrintf)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias("__lrintf")]]
__LONGLONG llrintf(float x) %{generate(double2float("llrint"))}

[[std, const, wunused, nothrow, crtbuiltin, export_alias("__llroundf")]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__, lroundf)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias("__lroundf")]]
__LONGLONG llroundf(float x) %{generate(double2float("llround"))}
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGLONG */

%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGDOUBLE
[[std]] nexttowardl(*) = nextafterl;

[[std, const, wunused, nothrow, crtbuiltin, export_alias("__scalbnl")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__ && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)), alias("scalbln", "__scalbln")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__), alias("scalblnl", "__scalblnl")]]
[[ldouble_variant_of("scalbn", ...)]]
__LONGDOUBLE scalbnl(__LONGDOUBLE x, int n) %{generate(double2ldouble("scalbn"))}

[[std, const, wunused, nothrow, crtbuiltin, export_alias("__scalblnl")]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__ && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE), scalbn)]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__, scalbnl)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__ && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)), alias("__scalbn")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__), alias("__scalbnl")]]
[[ldouble_variant_of("scalbln", ...)]]
__LONGDOUBLE scalblnl(__LONGDOUBLE x, long int n) %{generate(double2ldouble("scalbln"))}

[[std, const, wunused, nothrow, doc_alias("nearbyint")]]
[[nocrt, alias("nearbyintl", "__nearbyintl", "rintl", "__rintl")]]
[[if(__has_builtin(__builtin_nearbyintl) && defined(__LIBC_BIND_CRTBUILTINS)),
  preferred_extern_inline("nearbyintl", { return __builtin_nearbyintl(x); })]]
[[if($extended_include_prefix("<ieee754.h>")defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__) ||
                                            defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) ||
                                            defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__)),
  bind_local_function(rintl)]]
__LONGDOUBLE nearbyintl(__LONGDOUBLE x);

[[std, crtbuiltin, export_alias("__roundl"), ldouble_variant_of("round", ...)]]   roundl(*)  %{generate(double2ldouble("round"))}
[[std, crtbuiltin, export_alias("__truncl"), ldouble_variant_of("trunc", ...)]]   truncl(*)  %{generate(double2ldouble("trunc"))}
[[std, crtbuiltin, export_alias("__remquol"), ldouble_variant_of("remquo", ...)]] remquol(*) %{generate(double2ldouble("remquo"))}

[[std, const, wunused, nothrow, crtbuiltin, export_alias("__lrintl")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)), alias("llrint", "__llrint")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias("llrintl", "__llrintl")]]
[[ldouble_variant_of("remquo", ...)]]
long int lrintl(__LONGDOUBLE x) %{generate(double2ldouble("lrint"))}

[[std, const, wunused, nothrow, crtbuiltin, export_alias("__lroundl")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias("llroundl", "__llroundl")]]
long int lroundl(__LONGDOUBLE x) %{generate(double2ldouble("lround"))}

[[std, crtbuiltin, export_alias("__fdiml"), ldouble_variant_of("fdim", ...)]] fdiml(*) %{generate(double2ldouble("fdim"))}
[[std, crtbuiltin, export_alias("__fmaxl"), ldouble_variant_of("fmax", ...)]] fmaxl(*) %{generate(double2ldouble("fmax"))}
[[std, crtbuiltin, export_alias("__fminl"), ldouble_variant_of("fmin", ...)]] fminl(*) %{generate(double2ldouble("fmin"))}
[[std, crtbuiltin, export_alias("__fmal"), ldouble_variant_of("fma", ...)]]  fmal(*)  %{generate(double2ldouble("fma"))}

%(std, c, ccompat)#ifdef __COMPILER_HAVE_LONGLONG
[[std, const, wunused, nothrow, crtbuiltin, export_alias("__llrintl")]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE), lrint)]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__, lrintl)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)), alias("__lrint")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias("__lrintl")]]
[[ldouble_variant_of("llrint", ...)]]
__LONGLONG llrintl(__LONGDOUBLE x) %{generate(double2ldouble("llrint"))}

[[std, const, wunused, nothrow, crtbuiltin, export_alias("__llroundl")]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE), lround)]]
[[alt_variant_of($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__, lroundl)]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__ && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)), alias("__lround")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_LONG__ == __SIZEOF_LONG_LONG__), alias("__lroundl")]]
[[ldouble_variant_of("llround", ...)]]
__LONGLONG llroundl(__LONGDOUBLE x) %{generate(double2ldouble("llround"))}

%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGLONG */
%(std, c, ccompat)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std, c, ccompat)#endif /* __USE_ISOC99 */



/* C++ overload aliases */
%(std)#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP_MATH_H_PROTO)
%[insert:std_function_nousing(acos = acosf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(asin = asinf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(atan = atanf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(atan2 = atan2f, externLinkageOverride: "C++")]
%[insert:std_function_nousing(cos = cosf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(sin = sinf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(tan = tanf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(cosh = coshf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(sinh = sinhf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(tanh = tanhf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(exp = expf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(frexp = frexpf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(ldexp = ldexpf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(log = logf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(log10 = log10f, externLinkageOverride: "C++")]
%[insert:std_function_nousing(modf = modff, externLinkageOverride: "C++")]
%[insert:std_function_nousing(pow = powf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(sqrt = sqrtf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(ceil = ceilf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(fabs = fabsf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(floor = floorf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(fmod = fmodf, externLinkageOverride: "C++")]

%(std)#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:std_function_nousing(acos = acosl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(asin = asinl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(atan = atanl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(atan2 = atan2l, externLinkageOverride: "C++")]
%[insert:std_function_nousing(cos = cosl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(sin = sinl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(tan = tanl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(cosh = coshl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(sinh = sinhl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(tanh = tanhl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(exp = expl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(frexp = frexpl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(ldexp = ldexpl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(log = logl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(log10 = log10l, externLinkageOverride: "C++")]
%[insert:std_function_nousing(modf = modfl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(pow = powl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(sqrt = sqrtl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(ceil = ceill, externLinkageOverride: "C++")]
%[insert:std_function_nousing(fabs = fabsl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(floor = floorl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(fmod = fmodl, externLinkageOverride: "C++")]
%(std)#endif /* __COMPILER_HAVE_LONGDOUBLE */


%(std)#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
%[insert:std_function_nousing(acosh = acoshf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(asinh = asinhf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(atanh = atanhf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(expm1 = expm1f, externLinkageOverride: "C++")]
%[insert:std_function_nousing(log1p = log1pf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(logb = logbf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(cbrt = cbrtf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(rint = rintf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(nextafter = nextafterf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(remainder = remainderf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(ilogb = ilogbf, externLinkageOverride: "C++")]
%(std)#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:std_function_nousing(acosh = acoshl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(asinh = asinhl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(atanh = atanhl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(expm1 = expm1l, externLinkageOverride: "C++")]
%[insert:std_function_nousing(log1p = log1pl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(logb = logbl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(cbrt = cbrtl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(rint = rintl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(nextafter = nextafterl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(remainder = remainderl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(ilogb = ilogbl, externLinkageOverride: "C++")]
%(std)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std)#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */


%(std)#ifdef __USE_ISOC99
%[insert:std_function_nousing(exp2 = exp2f, externLinkageOverride: "C++")]
%[insert:std_function_nousing(log2 = log2f, externLinkageOverride: "C++")]
%[insert:std_function_nousing(copysign = copysignf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(tgamma = tgammaf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(nexttoward = nexttowardf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(scalbn = scalbnf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(scalbln = scalblnf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(nearbyint = rintf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(round = roundf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(trunc = truncf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(remquo = remquof, externLinkageOverride: "C++")]
%[insert:std_function_nousing(lrint = lrintf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(lround = lroundf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(fdim = fdimf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(fmax = fmaxf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(fmin = fminf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(fma = fmaf, externLinkageOverride: "C++")]
%(std)#ifdef __COMPILER_HAVE_LONGLONG
%[insert:std_function_nousing(llrint = llrintf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(llround = llroundf, externLinkageOverride: "C++")]
%(std)#endif /* __COMPILER_HAVE_LONGLONG */
%(std)#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:std_function_nousing(exp2 = exp2l, externLinkageOverride: "C++")]
%[insert:std_function_nousing(log2 = log2l, externLinkageOverride: "C++")]
%[insert:std_function_nousing(copysign = copysignl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(tgamma = tgammal, externLinkageOverride: "C++")]
%[insert:std_function_nousing(nexttoward = nextafterl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(scalbn = scalbnl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(scalbln = scalblnl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(nearbyint = rintl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(round = roundl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(trunc = truncl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(remquo = remquol, externLinkageOverride: "C++")]
%[insert:std_function_nousing(lrint = lrintl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(lround = lroundl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(fdim = fdiml, externLinkageOverride: "C++")]
%[insert:std_function_nousing(fmax = fmaxl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(fmin = fminl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(fma = fmal, externLinkageOverride: "C++")]
%(std)#ifdef __COMPILER_HAVE_LONGLONG
%[insert:std_function_nousing(llrint = llrintl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(llround = llroundl, externLinkageOverride: "C++")]
%(std)#endif /* __COMPILER_HAVE_LONGLONG */
%(std)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std)#endif /* __USE_ISOC99 */


%(std)#if defined(__USE_XOPEN) || defined(__USE_ISOC99)
%[insert:std_function_nousing(hypot = hypotf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(erf = erff, externLinkageOverride: "C++")]
%[insert:std_function_nousing(erfc = erfcf, externLinkageOverride: "C++")]
%[insert:std_function_nousing(lgamma = lgammaf, externLinkageOverride: "C++")]
%(std)#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:std_function_nousing(hypot = hypotl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(erf = erfl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(erfc = erfcl, externLinkageOverride: "C++")]
%[insert:std_function_nousing(lgamma = lgammal, externLinkageOverride: "C++")]
%(std)#endif /* __COMPILER_HAVE_LONGDOUBLE */
%(std)#endif /* __USE_XOPEN || __USE_ISOC99 */
%(std)#endif /* __cplusplus && __CORRECT_ISO_CPP_MATH_H_PROTO */




%[define_double_replacement(sincos = sincosf, sincosl)]

%
%#ifdef __USE_GNU
@@>> sincosf(3), sincos(3), sincosl(3)
@@Calculate both sine (*psinx) and cosine (*pcosx) of `x'
[[nothrow, crtbuiltin, export_alias("__sincos")]]
[[attribute("__DECL_SIMD_sincos"), decl_include("<bits/crt/math-vector.h>")]]
[[impl_include("<libm/sincos.h>"), requires_include("<ieee754.h>")]]
[[requires(($has_function(sin) && $has_function(cos)) ||
           defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
void sincos(double x, [[out]] double *psinx, [[out]] double *pcosx) {
@@pp_if defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)@@
	__LIBM_MATHFUNX(@sincos@)(x, (__LIBM_MATHFUN_T *)psinx, (__LIBM_MATHFUN_T *)pcosx);
@@pp_else@@
	*psinx = sin(x);
	*pcosx = cos(x);
@@pp_endif@@
}

@@>> exp10f(3), exp10(3), exp10l(3)
@@A function missing in all standards: compute exponent to base ten
[[wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__exp10")]]
[[requires_function(exp, __signbit)]]
[[impl_include("<hybrid/floatcore.h>", "<asm/crt/fenv.h>")]]
[[impl_include("<libm/matherr.h>")]]
double exp10(double x) {
	double result;
	if (finite(x) && x < __DBL_MIN_10_EXP__ - __DBL_DIG__ - 10) {
@@pp_if $has_function(feraiseexcept) && defined(FE_UNDERFLOW)@@
		feraiseexcept(FE_UNDERFLOW);
@@pp_endif@@
		return 0.0;
	}
	result = exp(M_LN10 * x);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE && !finite(result) && finite(x)) {
		/* exp10 overflow (46) if x > 0, underflow (47) if x < 0. */
		return __kernel_standard(x, x, result, __signbit(x)
		                         ? __LIBM_KMATHERR_EXP10_UNDERFLOW
		                         : __LIBM_KMATHERR_EXP10_OVERFLOW);
	}
	return result;
}

@@>> pow10f(3), pow10(3), pow10l(3)
@@Another  name  occasionally  used
[[wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__pow10")]]
[[requires_function(pow)]]
double pow10(double x) {
	return pow(10.0, x);
}

[[crtbuiltin, export_alias("__sincosf"), nothrow, doc_alias("sincos")]]
[[attribute("__DECL_SIMD_sincosf"), decl_include("<bits/crt/math-vector.h>")]]
[[impl_include("<libm/sincos.h>"), requires_include("<ieee754.h>")]]
[[requires($has_function(sincos) || ($has_function(sinf) && $has_function(cosf)) ||
           defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__))]]
void sincosf(float x, [[out]] float *psinx, [[out]] float *pcosx) {
@@pp_if defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) || defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)@@
	__LIBM_MATHFUNXF(@sincos@)(x, (__LIBM_MATHFUNF_T *)psinx, (__LIBM_MATHFUNF_T *)pcosx);
@@pp_elif $has_function(sincos)@@
	double sinx, cosx;
	sincos((double)x, &sinx, &cosx);
	*psinx = (float)sinx;
	*pcosx = (float)cosx;
@@pp_else@@
	*psinx = sinf(x);
	*pcosx = cosf(x);
@@pp_endif@@
}

[[wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__exp10f")]]
[[requires_function(exp, __signbitf), doc_alias("exp10")]]
[[impl_include("<hybrid/floatcore.h>", "<asm/crt/fenv.h>")]]
[[impl_include("<libm/matherr.h>")]]
float exp10f(float x) {
	float result;
	result = (float)exp(M_LN10 * (double)x);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE && !finitef(result) && finitef(x)) {
		/* exp10 overflow (46) if x > 0, underflow (47) if x < 0. */
		return __kernel_standard_f(x, x, result, __signbitf(x)
		                           ? __LIBM_KMATHERRF_EXP10_UNDERFLOW
		                           : __LIBM_KMATHERRF_EXP10_OVERFLOW);
	}
	return result;
}


[[crtbuiltin, export_alias("__pow10f")]] pow10f(*) %{generate(double2float("pow10"))}

%#ifdef __COMPILER_HAVE_LONGDOUBLE
[[nothrow, crtbuiltin, export_alias("__sincosl"), doc_alias("sincos")]]
[[attribute("__DECL_SIMD_sincosl"), decl_include("<bits/crt/math-vector.h>")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)), alias("__sincos", "sincos")]]
[[impl_include("<libm/sincos.h>"), requires_include("<ieee754.h>")]]
[[requires($has_function(sincos) || ($has_function(sinl) && $has_function(cosl)) ||
           defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__))]]
void sincosl(__LONGDOUBLE x, [[out]] __LONGDOUBLE *psinx, [[out]] __LONGDOUBLE *pcosx) {
@@pp_if defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) || defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)@@
	__LIBM_MATHFUNXL(@sincos@)(x, (__LIBM_MATHFUNL_T *)psinx, (__LIBM_MATHFUNL_T *)pcosx);
@@pp_elif $has_function(sincos)@@
	double sinx, cosx;
	sincos((double)x, &sinx, &cosx);
	*psinx = (__LONGDOUBLE)sinx;
	*pcosx = (__LONGDOUBLE)cosx;
@@pp_else@@
	*psinx = sinl(x);
	*pcosx = cosl(x);
@@pp_endif@@
}

[[wunused, ATTR_MCONST, nothrow, crtbuiltin, export_alias("__exp10l")]]
[[requires_function(expl, __signbitl), doc_alias("exp10")]]
[[impl_include("<hybrid/floatcore.h>", "<asm/crt/fenv.h>")]]
[[impl_include("<libm/matherr.h>")]]
__LONGDOUBLE exp10l(__LONGDOUBLE x) {
	__LONGDOUBLE result;
	if (finitel(x) && x < __LDBL_MIN_10_EXP__ - __LDBL_DIG__ - 10) {
@@pp_if $has_function(feraiseexcept) && defined(FE_UNDERFLOW)@@
		feraiseexcept(FE_UNDERFLOW);
@@pp_endif@@
		return 0.0L;
	}
	result = expl(M_LN10l * x);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE && !finitel(result) && finitel(x)) {
		/* exp10 overflow (46) if x > 0, underflow (47) if x < 0. */
		return __kernel_standard_l(x, x, result, __signbitl(x)
		                           ? __LIBM_KMATHERRL_EXP10_UNDERFLOW
		                           : __LIBM_KMATHERRL_EXP10_OVERFLOW);
	}
	return result;
}

[[crtbuiltin, export_alias("__pow10l")]]
[[ldouble_variant_of("pow10", ...)]]
pow10l(*) %{generate(double2ldouble("pow10"))}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_GNU */


%
%#ifdef __USE_MISC

%#if !defined(__cplusplus) || !defined(__CORRECT_ISO_CPP11_MATH_H_PROTO_FP) /* isinf conflicts with C++11. */
@@>> isinff(3), isinf(3), isinfl(3)
@@Return 0 if `value' is finite or NaN, +1 if it is +Infinity, -1 if it is -Infinity
[[const, wunused, nothrow, crtbuiltin, export_alias("__isinf")]]
[[impl_include("<libm/isinf.h>")]]
[[requires_include("<ieee754.h>", "<bits/math-constants.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__INFINITY) || defined(__HUGE_VAL))]]
int isinf(double x) {
@@pp_ifdef __LIBM_MATHFUNI@@
	return __LIBM_MATHFUNI(@isinf@, x);
@@pp_elif defined(__INFINITY)@@
	return x == __INFINITY;
@@pp_else@@
	return x == __HUGE_VAL;
@@pp_endif@@
}
%#endif /* !__cplusplus || !__CORRECT_ISO_CPP11_MATH_H_PROTO_FP */

[[crtbuiltin, export_alias("__isinff")]]
isinff(*) %{generate(double2float("isinf"))}
%#ifdef __COMPILER_HAVE_LONGDOUBLE
[[crtbuiltin, export_alias("__isinfl")]]
[[ldouble_variant_of("isinf", ...)]]
isinfl(*) %{generate(double2ldouble("isinf"))}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */

@@>> finitef(3), finite(3), finitel(3)
@@Return nonzero if `value' is finite and not NaN
[[const, wunused, nothrow, crtbuiltin, export_alias("__finite", "_finite")]]
[[requires_include("<ieee754.h>"), impl_include("<libm/finite.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__) ||
           ($has_function(isinf) && $has_function(isnan)))]]
int finite(double x) {
@@pp_ifdef __LIBM_MATHFUNI@@
	return __LIBM_MATHFUNI(@finite@, x);
@@pp_else@@
	return !isinf(x) && !isnan(x);
@@pp_endif@@
}

drem(*) = remainder;

@@>> significandf(3), significand(3), significandl(3)
@@Return the fractional part of `x' after dividing out `ilogb(x)'
[[const, wunused, nothrow, crtbuiltin, export_alias("__significand")]]
[[requires_include("<ieee754.h>"), impl_include("<libm/significand.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double significand(double x) {
	return __LIBM_MATHFUN(@significand@, x);
}

[[crtbuiltin, export_alias("__finitef"), alias("_finitef")]]
/* For some reason, only exported on x86_64 (s.a. <crt-features/crt-dos.h>) */
[[if(defined(__x86_64__)), dos_only_export_as("_finitef")]]
finitef(*) %{generate(double2float("finite"))}

dremf(*) = remainderf;

[[crtbuiltin, export_alias("__significandf")]]
significandf(*) %{generate(double2float("significand"))}

%#ifdef __COMPILER_HAVE_LONGDOUBLE
[[crtbuiltin, export_alias("__finitel")]]
[[ldouble_variant_of("finite", ...)]]
finitel(*) %{generate(double2ldouble("finite"))}

dreml(*) = remainderl;

[[crtbuiltin, export_alias("__significandl")]]
[[ldouble_variant_of("significand", ...)]]
significandl(*) %{generate(double2ldouble("significand"))}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_MISC */

%
%#if defined(__USE_MISC) || (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K))
%#if !defined(__cplusplus) || !defined(__CORRECT_ISO_CPP11_MATH_H_PROTO_FP) /* isnan conflicts with C++11. */
@@>> isnanf(3), isnan(3), isnanl(3)
@@Return nonzero if `value' is not a number
[[const, wunused, nothrow, crtbuiltin]]
[[dos_only_export_alias("_isnan"), export_alias("__isnan")]]
[[requires_include("<ieee754.h>"), impl_include("<libm/isnan.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
int isnan(double x) {
	return __LIBM_MATHFUNI(@isnan@, x);
}
%#endif /* !cplusplus || !__CORRECT_ISO_CPP11_MATH_H_PROTO_FP */

[[crtbuiltin, export_alias("__isnanf"), alias("_isnanf")]]
/* For some reason, only exported on x86_64 (s.a. <crt-features/crt-dos.h>) */
[[if(defined(__x86_64__)), dos_only_export_as("_isnanf")]]
isnanf(*) %{generate(double2float("isnan"))}

%#ifdef __COMPILER_HAVE_LONGDOUBLE
[[crtbuiltin, export_alias("__isnanl")]]
[[ldouble_variant_of("isnan", ...)]]
isnanl(*) %{generate(double2ldouble("isnan"))}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */

%#endif /* __USE_MISC || (__USE_XOPEN && !__USE_XOPEN2K) */

%
%/* Bessel functions. */
%#if defined(__USE_MISC) || defined(__USE_XOPEN)
@@>> j0f(3), j0(3), j0l(3)
[[wunused, ATTR_MCONST, nothrow, crtbuiltin, dos_only_export_alias("_j0"), export_alias("__j0")]]
[[impl_include("<libm/j0.h>", "<libm/fcomp.h>", "<libm/fabs.h>", "<libm/matherr.h>")]]
[[requires_include("<ieee754.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double j0(double x) {
	if (__LIBM_LIB_VERSION != __LIBM_IEEE && __LIBM_LIB_VERSION != __LIBM_POSIX &&
	    __LIBM_MATHFUNI2(@isgreater@, __LIBM_MATHFUN(@fabs@, x), @1.41484755040568800000e+16@ /*X_TLOSS*/))
		return __kernel_standard(x, x, 0.0, __LIBM_KMATHERR_J0_TLOSS); /* j0(|x|>X_TLOSS) */
	return __LIBM_MATHFUN(@j0@, x);
}

@@>> j1f(3), j1(3), j1l(3)
[[wunused, ATTR_MCONST, nothrow, crtbuiltin, dos_only_export_alias("_j1"), export_alias("__j1")]]
[[impl_include("<libm/j1.h>", "<libm/fcomp.h>", "<libm/fabs.h>", "<libm/matherr.h>")]]
[[requires_include("<ieee754.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double j1(double x) {
	if (__LIBM_LIB_VERSION != __LIBM_IEEE && __LIBM_LIB_VERSION != __LIBM_POSIX &&
	    __LIBM_MATHFUNI2(@isgreater@, __LIBM_MATHFUN(@fabs@, x), @1.41484755040568800000e+16@ /*X_TLOSS*/))
		return __kernel_standard(x, x, 0.0, __LIBM_KMATHERR_J1_TLOSS); /* j1(|x|>X_TLOSS) */
	return __LIBM_MATHFUN(@j1@, x);
}

@@>> jnf(3), jn(3), jnl(3)
[[wunused, ATTR_MCONST, nothrow, crtbuiltin, dos_only_export_alias("_jn"), export_alias("__jn")]]
[[impl_include("<libm/jn.h>", "<libm/fcomp.h>", "<libm/fabs.h>", "<libm/matherr.h>")]]
[[requires_include("<ieee754.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double jn(int n, double x) {
	if (__LIBM_LIB_VERSION != __LIBM_IEEE && __LIBM_LIB_VERSION != __LIBM_POSIX &&
	    __LIBM_MATHFUNI2(@isgreater@, __LIBM_MATHFUN(@fabs@, x), @1.41484755040568800000e+16@ /*X_TLOSS*/))
		return __kernel_standard(n, x, 0.0, __LIBM_KMATHERR_JN_TLOSS); /* jn(n,|x|>X_TLOSS) */
	return __LIBM_MATHFUNIM(@jn@, n, x);
}

@@>> y0f(3), y0(3), y0l(3)
[[wunused, ATTR_MCONST, nothrow, crtbuiltin, dos_only_export_alias("_y0"), export_alias("__y0")]]
[[impl_include("<libm/fcomp.h>", "<bits/math-constants.h>")]]
[[impl_include("<libm/matherr.h>", "<libm/y0.h>", "<asm/crt/fenv.h>")]]
[[requires_include("<ieee754.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double y0(double x) {
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    (__LIBM_MATHFUNI2(@islessequal@, x, 0.0) ||
	     __LIBM_MATHFUNI2(@isgreater@, x, @1.41484755040568800000e+16@ /*X_TLOSS*/))) {
		if (x < 0.0) {
@@pp_if $has_function(feraiseexcept) && defined(FE_INVALID)@@
			feraiseexcept(FE_INVALID);
@@pp_endif@@
			return __kernel_standard(x, x, -__HUGE_VAL, __LIBM_KMATHERR_Y0_MINUS);
		} else if (x == 0.0) {
			return __kernel_standard(x, x, -__HUGE_VAL, __LIBM_KMATHERR_Y0_ZERO);
		} else if (__LIBM_LIB_VERSION != __LIBM_POSIX) {
			return __kernel_standard(x, x, 0.0f, __LIBM_KMATHERR_Y0_TLOSS);
		}
	}
	return __LIBM_MATHFUN(@y0@, x);
}

@@>> y1f(3), y1(3), y1l(3)
[[wunused, ATTR_MCONST, nothrow, crtbuiltin, dos_only_export_alias("_y1"), export_alias("__y1")]]
[[impl_include("<libm/fcomp.h>", "<bits/math-constants.h>")]]
[[impl_include("<libm/matherr.h>", "<libm/y1.h>", "<asm/crt/fenv.h>")]]
[[requires_include("<ieee754.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double y1(double x) {
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    (__LIBM_MATHFUNI2(@islessequal@, x, 0.0) ||
	     __LIBM_MATHFUNI2(@isgreater@, x, @1.41484755040568800000e+16@ /*X_TLOSS*/))) {
		if (x < 0.0) {
@@pp_if $has_function(feraiseexcept) && defined(FE_INVALID)@@
			feraiseexcept(FE_INVALID);
@@pp_endif@@
			return __kernel_standard(x, x, -__HUGE_VAL, __LIBM_KMATHERR_Y1_MINUS);
		} else if (x == 0.0) {
			return __kernel_standard(x, x, -__HUGE_VAL, __LIBM_KMATHERR_Y1_ZERO);
		} else if (__LIBM_LIB_VERSION != __LIBM_POSIX) {
			return __kernel_standard(x, x, 0.0f, __LIBM_KMATHERR_Y1_TLOSS);
		}
	}
	return __LIBM_MATHFUN(@y1@, x);
}

@@>> ynf(3), yn(3), ynl(3)
[[wunused, ATTR_MCONST, nothrow, crtbuiltin, dos_only_export_alias("_yn"), export_alias("__yn")]]
[[impl_include("<libm/fcomp.h>", "<bits/math-constants.h>")]]
[[impl_include("<libm/matherr.h>", "<libm/yn.h>", "<asm/crt/fenv.h>")]]
[[requires_include("<ieee754.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double yn(int n, double x) {
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    (__LIBM_MATHFUNI2(@islessequal@, x, 0.0) ||
	     __LIBM_MATHFUNI2(@isgreater@, x, @1.41484755040568800000e+16@ /*X_TLOSS*/))) {
		if (x < 0.0) {
@@pp_if $has_function(feraiseexcept) && defined(FE_INVALID)@@
			feraiseexcept(FE_INVALID);
@@pp_endif@@
			return __kernel_standard(n, x, -__HUGE_VAL, __LIBM_KMATHERR_YN_MINUS);
		} else if (x == 0.0) {
			return __kernel_standard(n, x, -__HUGE_VAL, __LIBM_KMATHERR_YN_ZERO);
		} else if (__LIBM_LIB_VERSION != __LIBM_POSIX) {
			return __kernel_standard(n, x, 0.0f, __LIBM_KMATHERR_YN_TLOSS);
		}
	}
	return __LIBM_MATHFUNIM(@yn@, n, x);
}
%#endif /* __USE_MISC || __USE_XOPEN */

%#ifdef __USE_MISC
[[crtbuiltin, export_alias("__j0f")]] j0f(*) %{generate(double2float("j0"))}
[[crtbuiltin, export_alias("__j1f")]] j1f(*) %{generate(double2float("j1"))}
[[crtbuiltin, export_alias("__jnf")]] jnf(*) %{generate(double2float("jn"))}
[[crtbuiltin, export_alias("__y0f")]] y0f(*) %{generate(double2float("y0"))}
[[crtbuiltin, export_alias("__y1f")]] y1f(*) %{generate(double2float("y1"))}
[[crtbuiltin, export_alias("__ynf")]] ynf(*) %{generate(double2float("yn"))}

%#ifdef __COMPILER_HAVE_LONGDOUBLE
[[crtbuiltin, export_alias("__j0l"), ldouble_variant_of("j0", ...)]] j0l(*) %{generate(double2ldouble("j0"))}
[[crtbuiltin, export_alias("__j1l"), ldouble_variant_of("j1", ...)]] j1l(*) %{generate(double2ldouble("j1"))}
[[crtbuiltin, export_alias("__jnl"), ldouble_variant_of("jn", ...)]] jnl(*) %{generate(double2ldouble("jn"))}
[[crtbuiltin, export_alias("__y0l"), ldouble_variant_of("y0", ...)]] y0l(*) %{generate(double2ldouble("y0"))}
[[crtbuiltin, export_alias("__y1l"), ldouble_variant_of("y1", ...)]] y1l(*) %{generate(double2ldouble("y1"))}
[[crtbuiltin, export_alias("__ynl"), ldouble_variant_of("yn", ...)]] ynl(*) %{generate(double2ldouble("yn"))}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_MISC */


%
%#if defined(__USE_MISC) || (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K))
@@Obsolete export_alias for `lgamma'
gamma(*) = lgamma;

@@Obsolete export_alias for `lgammaf'
gammaf(*) = lgammaf;

%#ifdef __COMPILER_HAVE_LONGDOUBLE
@@Obsolete export_alias for `lgammal'
gammal(*) = lgammal;
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_MISC || (__USE_XOPEN && !__USE_XOPEN2K) */

%#ifdef __USE_MISC
@@>> lgammaf_r(3), lgamma_r(3), lgammal_r(3)
@@Reentrant    version    of     `lgamma(3)'
[[wunused, crtbuiltin, export_alias("__lgamma_r")]]
[[requires_include("<ieee754.h>"), impl_include("<libm/lgamma.h>")]]
[[impl_include("<libm/matherr.h>", "<libm/finite.h>", "<libm/floor.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double lgamma_r(double x, [[out]] int *signgamp) {
	double result = __LIBM_MATHFUN2I(@lgamma@, x, signgamp);
	if (__LIBM_LIB_VERSION != __LIBM_IEEE &&
	    !__LIBM_MATHFUNI(@finite@, result) && __LIBM_MATHFUNI(@finite@, x)) {
		return __kernel_standard(x, x, result,
		                         __LIBM_MATHFUN(@floor@, x) == x &&
		                         x <= 0.0 ? __LIBM_KMATHERR_LGAMMA_MINUS      /* lgamma pole */
		                                  : __LIBM_KMATHERR_LGAMMA_OVERFLOW); /* lgamma overflow */
	}
	return result;
}


[[crtbuiltin, export_alias("__lgammaf_r")]]
lgammaf_r(*) %{generate(double2float("lgamma_r"))};
%#ifdef __COMPILER_HAVE_LONGDOUBLE
[[crtbuiltin, export_alias("__lgammal_r")]]
[[ldouble_variant_of("lgamma_r", ["__lgamma_r"])]]
lgammal_r(*) %{generate(double2ldouble("lgamma_r"))};
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_MISC */

%
%#if defined(__USE_MISC) || (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_XOPEN2K8))
@@>> scalbf(3), scalb(3), scalbl(3)
@@Return `x' times (2 to the Nth power)
[[wunused, ATTR_MCONST, nothrow, crtbuiltin]]
[[dos_only_export_alias("_scalb"), export_alias("__scalb")]]
[[impl_include("<libm/isnan.h>", "<libm/finite.h>", "<libm/isinf.h>")]]
[[impl_include("<libm/matherr.h>", "<libc/errno.h>", "<libm/scalb.h>")]]
[[requires_include("<ieee754.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double scalb(double x, double fn) {
	/*
	 * ====================================================
	 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
	 *
	 * Developed at SunSoft, a Sun Microsystems, Inc. business.
	 * Permission  to  use, copy,  modify, and  distribute this
	 * software is freely  granted, provided  that this  notice
	 * is preserved.
	 * ====================================================
	 */
	double result;
	result = __LIBM_MATHFUN2(@scalb@, x, fn);
	if (__LIBM_LIB_VERSION == __LIBM_SVID) {
		if (__LIBM_MATHFUNI(@isinf@, result)) {
			if (__LIBM_MATHFUNI(@finite@, x)) {
				return __kernel_standard(x, fn, result, __LIBM_KMATHERR_SCALB_OVERFLOW); /* scalb overflow */
			} else {
@@pp_ifdef ERANGE@@
				(void)libc_seterrno(ERANGE);
@@pp_endif@@
			}
		} else if (result == 0.0 && result != x) {
			return __kernel_standard(x, fn, result, __LIBM_KMATHERR_SCALB_UNDERFLOW); /* scalb underflow */
		}
	} else {
		if (!__LIBM_MATHFUNI(@finite@, result) || result == 0.0) {
			if (__LIBM_MATHFUNI(@isnan@, result)) {
				if (!__LIBM_MATHFUNI(@isnan@, x) && !__LIBM_MATHFUNI(@isnan@, fn))
					result = __kernel_standard(x, fn, result, __LIBM_KMATHERR_SCALB_INVALID);
			} else if (__LIBM_MATHFUNI(@isinf@, result)) {
				if (!__LIBM_MATHFUNI(@isinf@, x) && !__LIBM_MATHFUNI(@isinf@, fn))
					result = __kernel_standard(x, fn, result, __LIBM_KMATHERR_SCALB_OVERFLOW);
			} else {
				/* result == 0. */
				if (x != 0.0 && !__LIBM_MATHFUNI(@isinf@, fn))
					result = __kernel_standard(x, fn, result, __LIBM_KMATHERR_SCALB_UNDERFLOW);
			}
		}
	}
	return result;
}
%#endif /* __USE_MISC || (__USE_XOPEN_EXTENDED && !__USE_XOPEN2K8) */

%#ifdef __USE_MISC
[[dos_only_export_alias("_scalbf")]]
[[crtbuiltin, export_alias("__scalbf")]]
scalbf(*) %{generate(double2float("scalb"))}
%#ifdef __COMPILER_HAVE_LONGDOUBLE
[[crtbuiltin, export_alias("__scalbl")]]
[[ldouble_variant_of("scalb", ...)]]
scalbl(*) %{generate(double2ldouble("scalb"))}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_MISC */







%
%
%/************************************************************************/
%/* Glibc __aliases                                                      */
%/************************************************************************/

%#ifdef __USE_GLIBC_BLOAT
%[insert:function(__acos = acos)]
%[insert:function(__asin = asin)]
%[insert:function(__atan = atan)]
%[insert:function(__atan2 = atan2)]
%[insert:function(__cos = cos)]
%[insert:function(__sin = sin)]
%[insert:function(__tan = tan)]
%[insert:function(__cosh = cosh)]
%[insert:function(__sinh = sinh)]
%[insert:function(__tanh = tanh)]
%[insert:function(__exp = exp)]
%[insert:function(__frexp = frexp)]
%[insert:function(__ldexp = ldexp)]
%[insert:function(__log = log)]
%[insert:function(__log10 = log10)]
%[insert:function(__pow = pow)]
%[insert:function(__sqrt = sqrt)]
%[insert:function(__ceil = ceil)]
%[insert:function(__fabs = fabs)]
%[insert:function(__floor = floor)]
%[insert:function(__fmod = fmod)]

%[insert:function(__modf = modf)]
%[insert:function(__acosf = acosf)]
%[insert:function(__asinf = asinf)]
%[insert:function(__atanf = atanf)]
%[insert:function(__atan2f = atan2f)]
%[insert:function(__cosf = cosf)]
%[insert:function(__sinf = sinf)]
%[insert:function(__tanf = tanf)]
%[insert:function(__coshf = coshf)]
%[insert:function(__sinhf = sinhf)]
%[insert:function(__tanhf = tanhf)]
%[insert:function(__expf = expf)]
%[insert:function(__frexpf = frexpf)]
%[insert:function(__ldexpf = ldexpf)]
%[insert:function(__logf = logf)]
%[insert:function(__log10f = log10f)]
%[insert:function(__modff = modff)]
%[insert:function(__powf = powf)]
%[insert:function(__sqrtf = sqrtf)]
%[insert:function(__ceilf = ceilf)]
%[insert:function(__fabsf = fabsf)]
%[insert:function(__floorf = floorf)]
%[insert:function(__fmodf = fmodf)]

%#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:function(__acosl = acosl)]
%[insert:function(__asinl = asinl)]
%[insert:function(__atanl = atanl)]
%[insert:function(__atan2l = atan2l)]
%[insert:function(__cosl = cosl)]
%[insert:function(__sinl = sinl)]
%[insert:function(__tanl = tanl)]
%[insert:function(__coshl = coshl)]
%[insert:function(__sinhl = sinhl)]
%[insert:function(__tanhl = tanhl)]
%[insert:function(__expl = expl)]
%[insert:function(__frexpl = frexpl)]
%[insert:function(__ldexpl = ldexpl)]
%[insert:function(__logl = logl)]
%[insert:function(__log10l = log10l)]
%[insert:function(__modfl = modfl)]
%[insert:function(__powl = powl)]
%[insert:function(__sqrtl = sqrtl)]
%[insert:function(__ceill = ceill)]
%[insert:function(__fabsl = fabsl)]
%[insert:function(__floorl = floorl)]
%[insert:function(__fmodl = fmodl)]
%#endif /* __COMPILER_HAVE_LONGDOUBLE */


%#ifdef __USE_GNU
%[insert:function(__sincos = sincos)]
%[insert:function(__exp10 = exp10)]
%[insert:function(__pow10 = pow10)]

%[insert:function(__sincosf = sincosf)]
%[insert:function(__exp10f = exp10f)]
%[insert:function(__pow10f = pow10f)]

%#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:function(__sincosl = sincosl)]
%[insert:function(__exp10l = exp10l)]
%[insert:function(__pow10l = pow10l)]
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_GNU */



%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
%[insert:function(__acosh = acosh)]
%[insert:function(__asinh = asinh)]
%[insert:function(__atanh = atanh)]
%[insert:function(__expm1 = expm1)]
%[insert:function(__log1p = log1p)]
%[insert:function(__logb = logb)]
%[insert:function(__cbrt = cbrt)]
%[insert:function(__rint = rint)]
%[insert:function(__nextafter = nextafter)]
%[insert:function(__remainder = remainder)]
%[insert:function(__ilogb = ilogb)]

%[insert:function(__acoshf = acoshf)]
%[insert:function(__asinhf = asinhf)]
%[insert:function(__atanhf = atanhf)]
%[insert:function(__expm1f = expm1f)]
%[insert:function(__log1pf = log1pf)]
%[insert:function(__logbf = logbf)]
%[insert:function(__cbrtf = cbrtf)]
%[insert:function(__rintf = rintf)]
%[insert:function(__nextafterf = nextafterf)]
%[insert:function(__remainderf = remainderf)]
%[insert:function(__ilogbf = ilogbf)]

%#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:function(__acoshl = acoshl)]
%[insert:function(__asinhl = asinhl)]
%[insert:function(__atanhl = atanhl)]
%[insert:function(__expm1l = expm1l)]
%[insert:function(__log1pl = log1pl)]
%[insert:function(__logbl = logbl)]
%[insert:function(__cbrtl = cbrtl)]
%[insert:function(__rintl = rintl)]
%[insert:function(__nextafterl = nextafterl)]
%[insert:function(__remainderl = remainderl)]
%[insert:function(__ilogbl = ilogbl)]
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */



%#ifdef __USE_ISOC99
%[insert:function(__tgamma = tgamma)]
%[insert:function(__nexttoward = nexttoward)]
%[insert:function(__scalbn = scalbn)]
%[insert:function(__scalbln = scalbln)]
%[insert:function(__nearbyint = rint)]
%[insert:function(__round = round)]
%[insert:function(__trunc = trunc)]
%[insert:function(__remquo = remquo)]
%[insert:function(__lrint = lrint)]
%[insert:function(__lround = lround)]
%[insert:function(__fdim = fdim)]
%[insert:function(__fmax = fmax)]
%[insert:function(__fmin = fmin)]
%[insert:function(__fma = fma)]
%[insert:function(__exp2 = exp2)]
%[insert:function(__log2 = log2)]
%[insert:function(__copysign = copysign)]
%[insert:function(__nan = nan)]

%[insert:function(__tgammaf = tgammaf)]
%[insert:function(__nexttowardf = nexttowardf)]
%[insert:function(__scalbnf = scalbnf)]
%[insert:function(__scalblnf = scalblnf)]
%[insert:function(__nearbyintf = rintf)]
%[insert:function(__roundf = roundf)]
%[insert:function(__truncf = truncf)]
%[insert:function(__remquof = remquof)]
%[insert:function(__lrintf = lrintf)]
%[insert:function(__lroundf = lroundf)]
%[insert:function(__fdimf = fdimf)]
%[insert:function(__fmaxf = fmaxf)]
%[insert:function(__fminf = fminf)]
%[insert:function(__fmaf = fmaf)]
%[insert:function(__exp2f = exp2f)]
%[insert:function(__log2f = log2f)]
%[insert:function(__copysignf = copysignf)]
%[insert:function(__nanf = nanf)]

%#ifdef __COMPILER_HAVE_LONGLONG
%[insert:function(__llrint = llrint)]
%[insert:function(__llround = llround)]
%[insert:function(__llrintf = llrintf)]
%[insert:function(__llroundf = llroundf)]
%#endif /* __COMPILER_HAVE_LONGLONG */

%#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:function(__nexttowardl = nextafterl)]
%[insert:function(__scalbnl = scalbnl)]
%[insert:function(__scalblnl = scalblnl)]
%[insert:function(__nearbyintl = rintl)]
%[insert:function(__roundl = roundl)]
%[insert:function(__truncl = truncl)]
%[insert:function(__remquol = remquol)]
%[insert:function(__lrintl = lrintl)]
%[insert:function(__lroundl = lroundl)]
%[insert:function(__fdiml = fdiml)]
%[insert:function(__fmaxl = fmaxl)]
%[insert:function(__fminl = fminl)]
%[insert:function(__fmal = fmal)]
%[insert:function(__tgammal = tgammal)]
%[insert:function(__exp2l = exp2l)]
%[insert:function(__log2l = log2l)]
%[insert:function(__copysignl = copysignl)]
%[insert:function(__nanl = nanl)]
%#ifdef __COMPILER_HAVE_LONGLONG
%[insert:function(__llrintl = llrintl)]
%[insert:function(__llroundl = llroundl)]
%#endif /* __COMPILER_HAVE_LONGLONG */
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_ISOC99 */



%#if defined(__USE_XOPEN) || defined(__USE_ISOC99)
%[insert:function(__hypot = hypot)]
%[insert:function(__erf = erf)]
%[insert:function(__erfc = erfc)]
%[insert:function(__lgamma = lgamma)]
%[insert:function(__hypotf = hypotf)]
%[insert:function(__erff = erff)]
%[insert:function(__erfcf = erfcf)]
%[insert:function(__lgammaf = lgammaf)]
%#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:function(__hypotl = hypotl)]
%[insert:function(__erfl = erfl)]
%[insert:function(__erfcl = erfcl)]
%[insert:function(__lgammal = lgammal)]
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_XOPEN || __USE_ISOC99 */



%#if defined(__USE_MISC) || defined(__USE_XOPEN)
%[insert:function(__j0 = j0)]
%[insert:function(__j1 = j1)]
%[insert:function(__jn = jn)]
%[insert:function(__y0 = y0)]
%[insert:function(__y1 = y1)]
%[insert:function(__yn = yn)]
%#endif /* __USE_MISC || __USE_XOPEN */



%#ifdef __USE_MISC
%[insert:function(__drem = remainder)]
%[insert:function(__significand = significand)]
%[insert:function(__lgamma_r = lgamma_r)]

%[insert:function(__dremf = remainderf)]
%[insert:function(__significandf = significandf)]
%[insert:function(__lgammaf_r = lgammaf_r)]
%[insert:function(__j0f = j0f)]
%[insert:function(__j1f = j1f)]
%[insert:function(__jnf = jnf)]
%[insert:function(__y0f = y0f)]
%[insert:function(__y1f = y1f)]
%[insert:function(__ynf = ynf)]

%#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:function(__dreml = remainderl)]
%[insert:function(__significandl = significandl)]
%[insert:function(__lgammal_r = lgammal_r)]
%[insert:function(__j0l = j0l)]
%[insert:function(__j1l = j1l)]
%[insert:function(__jnl = jnl)]
%[insert:function(__y0l = y0l)]
%[insert:function(__y1l = y1l)]
%[insert:function(__ynl = ynl)]
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_MISC */



%#if defined(__USE_MISC) || (defined(__USE_XOPEN) && !defined(__USE_XOPEN2K))
%[insert:function(__gamma = lgamma)]

%[insert:function(__gammaf = lgammaf)]

%#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:function(__gammal = lgammal)]
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_MISC || (__USE_XOPEN && !__USE_XOPEN2K) */



%#if defined(__USE_MISC) || (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_XOPEN2K8))
%[insert:function(__scalb = scalb)]

%[insert:function(__scalbf = scalbf)]

%#ifdef __COMPILER_HAVE_LONGDOUBLE
%[insert:function(__scalbl = scalbl)]
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_MISC || (__USE_XOPEN_EXTENDED && !__USE_XOPEN2K8) */



%#endif /* __USE_GLIBC_BLOAT */





%
%
%/* Floating point classification */
%#ifdef __USE_ISOC99

@@>> fpclassify(3)
[[const, wunused, nothrow]]
[[export_alias("fpclassify"), dos_only_export_alias("_dclass")]]
[[requires_include("<ieee754.h>"), impl_include("<libm/fpclassify.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
[[crt_dos_variant({ impl:{ return fptype_kos2dos(libc___fpclassify(x)); }})]]
int __fpclassify(double x) {
	return __LIBM_MATHFUNI(@fpclassify@, x);
}


@@>> signbit(3)
[[const, wunused, nothrow, dos_only_export_alias("_dsign")]]
[[impl_include("<libm/signbit.h>")]]
int __signbit(double x) {
@@pp_ifdef __LIBM_MATHFUNI@@
	return __LIBM_MATHFUNI(@signbit@, x);
@@pp_else@@
	return x < 0.0;
@@pp_endif@@
}

%[insert:function(__isinf = isinf)]
%[insert:function(__finite = finite)]
%[insert:function(__isnan = isnan)]


[[const, wunused, nothrow, export_alias("fpclassifyf"), dos_only_export_alias("_fdclass")]]
[[crt_dos_variant({ impl:{ return fptype_kos2dos(libc___fpclassifyf(x)); }})]]
int __fpclassifyf(float x) %{generate(double2float("__fpclassify"))}

[[dos_only_export_alias("_fdsign")]]
__signbitf(*) %{generate(double2float("__signbit"))}


%[insert:function(__isinff = isinff)]
%[insert:function(__finitef = finitef)]
%[insert:function(__isnanf = isnanf)]

%#ifdef __COMPILER_HAVE_LONGDOUBLE
[[const, wunused, nothrow, export_alias("fpclassifyl"), dos_only_export_alias("_ldclass")]]
[[crt_dos_variant({ impl:{ return fptype_kos2dos(libc___fpclassifyl(x)); }})]]
[[ldouble_variant_of("__fpclassify", ["fpclassify", "_dclass"])]]
int __fpclassifyl(__LONGDOUBLE x) %{generate(double2ldouble("__fpclassify"))}

[[dos_only_export_alias("_ldsign")]]
[[ldouble_variant_of("__signbit", ["_dsign"])]]
__signbitl(*) %{generate(double2ldouble("__signbit"))}

%[insert:function(__isinfl = isinfl)]
%[insert:function(__finitel = finitel)]
%[insert:function(__isnanl = isnanl)]
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_ISOC99 */

%
%#if defined(__USE_GNU) || defined(__STDC_WANT_IEC_60559_BFP_EXT__)
%{
#define __iscanonicalf(x) ((void)(x), 1)
#define __iscanonical(x)  ((void)(x), 1)
}

@@>> issignaling(3), __issignalingf(3), __issignaling(3), __issignalingl(3)
[[const, wunused, nothrow, preferred_export_alias("issignaling")]]
[[requires_include("<ieee754.h>"), impl_include("<libm/issignaling.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
int __issignaling(double x) {
	return __LIBM_MATHFUNI(@issignaling@, x);
}

[[preferred_export_alias("issignalingf")]]
__issignalingf(*) %{generate(double2float("__issignaling"))}

%#ifdef __COMPILER_HAVE_LONGDOUBLE
[[const, wunused, nothrow, impl_include("<libm/iscanonical.h>")]]
int __iscanonicall(__LONGDOUBLE x) {
@@pp_ifdef __IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__@@
	return __ieee854_iscanonicall((__IEEE854_LONG_DOUBLE_TYPE__)x);
@@pp_else@@
	(void)x;
	return 1;
@@pp_endif@@
}

[[preferred_export_alias("issignalingl")]]
[[ldouble_variant_of("__issignaling", ...)]]
__issignalingl(*) %{generate(double2ldouble("__issignaling"))}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */


%
%#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)
@@>> nextdownf(3), nextdown(3), nextdownl(3)
[[const, wunused, nothrow, requires_function(nextup)]]
double nextdown(double x) {
	return -nextup(-x);
}

@@>> nextupf(3), nextup(3), nextupl(3)
[[const, wunused, nothrow]]
[[requires_include("<ieee754.h>"), impl_include("<libm/nextup.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double nextup(double x) {
	return __LIBM_MATHFUN(@nextup@, x);
}

nextdownf(*) %{generate(double2float("nextdown"))}
nextupf(*) %{generate(double2float("nextup"))}
%#ifdef __COMPILER_HAVE_LONGDOUBLE
[[ldouble_variant_of("nextdown", ...)]] nextdownl(*) %{generate(double2ldouble("nextdown"))}
[[ldouble_variant_of("nextup", ...)]]   nextupl(*) %{generate(double2ldouble("nextup"))}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */
%#endif /* __USE_XOPEN_EXTENDED || __USE_ISOC99 */

[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__), alias("ilogb")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__), crt_intern_alias("ilogb")]]
[[wunused, ATTR_MCONST, nothrow, requires_function(ilogb)]]
long int llogb(double x) {
	return (long int)ilogb(x); /* TODO: support for sizeof(long) > sizeof(int) */
}

[[const, wunused, nothrow]]
[[requires_include("<ieee754.h>"), impl_include("<libm/roundeven.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
double roundeven(double x) {
	return __LIBM_MATHFUN(@roundeven@, x);
}

[[wunused, decl_include("<hybrid/typecore.h>")]]
$intmax_t fromfp(double x, int round, unsigned int width); /* TODO */

[[wunused, decl_include("<hybrid/typecore.h>")]]
$uintmax_t ufromfp(double x, int round, unsigned int width); /* TODO */

[[wunused, decl_include("<hybrid/typecore.h>")]]
$intmax_t fromfpx(double x, int round, unsigned int width); /* TODO */

[[wunused, decl_include("<hybrid/typecore.h>")]]
$uintmax_t ufromfpx(double x, int round, unsigned int width); /* TODO */

[[const, wunused, nothrow]]
[[requires_include("<ieee754.h>")]]
[[requires($has_function(fmax) &&
           (defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
            defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
            defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)))]]
[[impl_include("<libm/fcomp.h>", "<libm/fabs.h>")]]
double fmaxmag(double x, double y) {
	double x_abs = __LIBM_MATHFUN(@fabs@, x);
	double y_abs = __LIBM_MATHFUN(@fabs@, y);
	if (__LIBM_MATHFUN2(@isgreater@, x_abs, y_abs))
		return x;
	if (__LIBM_MATHFUN2(@isless@, x_abs, y_abs))
		return y;
	return fmax(x, y);
}

[[const, wunused, nothrow]]
[[requires_include("<ieee754.h>")]]
[[requires($has_function(fmin) &&
           (defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
            defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
            defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)))]]
[[impl_include("<libm/fcomp.h>", "<libm/fabs.h>")]]
double fminmag(double x, double y) {
	double x_abs = __LIBM_MATHFUN(@fabs@, x);
	double y_abs = __LIBM_MATHFUN(@fabs@, y);
	if (__LIBM_MATHFUN2(@isless@, x_abs, y_abs))
		return x;
	if (__LIBM_MATHFUN2(@isgreater@, x_abs, y_abs))
		return y;
	return fmin(x, y);
}


%[define(__MAGIC_FLOAT_TYPE_IS_DOUBLE = 1)]
%[define(__MAGIC_FLOAT_TYPE_IS_FLOAT = 0)]
%[define(__MAGIC_FLOAT_TYPE_IS_LONG_DOUBLE = 0)]

@@>> canonicalizef(3), canonicalize(3), canonicalizel(3)
@@@param: x:  Pointer to the value to canonicalize.
@@@param: cx: Store the canonicalized value of `*x' here.
@@@return: 0: Success
@@@return: 1: Error (`!iscanonical(*x)')
int canonicalize([[out]] double *cx,
                 [[in]] double const *x) {
	double value = *x;
@@pp_if __MAGIC_FLOAT_TYPE_IS_LONG_DOUBLE@@
	if (!__iscanonicall(value))
		return 1;
@@pp_endif@@
	if (__issignaling(value)) {
		*cx = value + value;
	} else {
		*cx = value;
	}
	return 0;
}

[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__), alias("ilogbf")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__), crt_intern_alias("ilogbf")]]
llogbf(*) %{generate(double2float("llogb"))}

roundevenf(*) %{generate(double2float("roundeven"))}
fromfpf(*) %{generate(double2float("fromfp"))}
ufromfpf(*) %{generate(double2float("ufromfp"))}
fromfpxf(*) %{generate(double2float("fromfpx"))}
ufromfpxf(*) %{generate(double2float("ufromfpx"))}
fmaxmagf(*) %{generate(double2float("fmaxmag"))}
fminmagf(*) %{generate(double2float("fminmag"))}
canonicalizef(*) %{generate(double2float("canonicalize"))}

%#ifdef __COMPILER_HAVE_LONGDOUBLE
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__ && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)), alias("ilogb")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__ && defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)), crt_intern_alias("ilogb")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__), alias("ilogbl")]]
[[if($extended_include_prefix("<hybrid/typecore.h>")__SIZEOF_INT__ == __SIZEOF_LONG__), crt_intern_alias("ilogbl")]]
[[ldouble_variant_of("llogbl", ...)]]
llogbl(*) %{generate(double2ldouble("llogb"))}

[[ldouble_variant_of("roundeven", ...)]]    roundevenl(*)    %{generate(double2ldouble("roundeven"))}
[[ldouble_variant_of("fromfp", ...)]]       fromfpl(*)       %{generate(double2ldouble("fromfp"))}
[[ldouble_variant_of("ufromfp", ...)]]      ufromfpl(*)      %{generate(double2ldouble("ufromfp"))}
[[ldouble_variant_of("fromfpx", ...)]]      fromfpxl(*)      %{generate(double2ldouble("fromfpx"))}
[[ldouble_variant_of("ufromfpx", ...)]]     ufromfpxl(*)     %{generate(double2ldouble("ufromfpx"))}
[[ldouble_variant_of("fmaxmag", ...)]]      fmaxmagl(*)      %{generate(double2ldouble("fmaxmag"))}
[[ldouble_variant_of("fminmag", ...)]]      fminmagl(*)      %{generate(double2ldouble("fminmag"))}
[[ldouble_variant_of("canonicalize", ...)]] canonicalizel(*) %{generate(double2ldouble("canonicalize"))}
%#endif /* __COMPILER_HAVE_LONGDOUBLE */

%#endif /* __USE_GNU || __STDC_WANT_IEC_60559_BFP_EXT__ */






@@>> _fdpcomp(3), _dpcomp(3), _ldpcomp(3)
[[ignore, const, wunused, nothrow]]
[[section(".text.crt.dos.math.math")]]
[[requires_include("<ieee754.h>"), impl_include("<libm/fcomp.h>")]]
[[requires(defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||
           defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||
           defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__))]]
int _dpcomp(double x, double y) {
	int result = 0;
	if (!__LIBM_MATHFUN2(@isunordered@, x, y)) {
		if (__LIBM_MATHFUN2(@isgreater@, x, y))
			result |= 4;
		if (__LIBM_MATHFUN2(@isgreaterequal@, x, y))
			result |= 2 | 4;
		if (__LIBM_MATHFUN2(@isless@, x, y))
			result |= 1;
		if (__LIBM_MATHFUN2(@islessequal@, x, y))
			result |= 1 | 2;
		if (__LIBM_MATHFUN2(@islessgreater@, x, y))
			result |= 1 | 4;
	}
	return result;
}

[[section(".text.crt.dos.math.math")]]
[[ignore]] _fdpcomp(*) %{generate(double2float("_dpcomp"))}
[[section(".text.crt.dos.math.math")]]
[[ldouble_variant_of("_dpcomp", ...)]]
[[ignore]] _ldpcomp(*) %{generate(double2ldouble("_dpcomp"))}

%(auto_source){
#ifndef __KERNEL__
#undef signgam
#undef __signgam
INTERN ATTR_SECTION(".bss.crt.math.math") int libc_signgam = 0;
DEFINE_PUBLIC_ALIAS(signgam, libc_signgam);
DEFINE_PUBLIC_ALIAS(__signgam, libc___signgam);
#define signgam     GET_NOREL_GLOBAL(signgam)
#define __signgam() (&signgam)
INTERN ATTR_CONST ATTR_RETNONNULL WUNUSED ATTR_SECTION(".text.crt.math.math") int *
NOTHROW(LIBCCALL libc___signgam)(void) {
	return &signgam;
}
#endif /* !__KERNEL__ */
}

%[declare_user_export("signgam")]
%[declare_user_export("__signgam")]

%
%{

#if defined(__USE_MISC) || defined(__USE_XOPEN)
/* This variable is used by `gamma(3)' and `lgamma(3)'. */
#ifndef signgam
#ifdef __CRT_HAVE_signgam
__CSDECLARE(,int,signgam)
#define signgam signgam
#elif defined(__LOCAL_signgam)
#define signgam __LOCAL_signgam
#elif defined(__CRT_HAVE___signgam)
#ifndef ____signgam_defined
#define ____signgam_defined
__CDECLARE(__ATTR_CONST __ATTR_RETNONNULL __ATTR_WUNUSED,int *,__NOTHROW_NCX,__signgam,(void),())
#endif /* !____signgam_defined */
#define signgam (*__signgam())
#endif /* __CRT_HAVE_signgam */
#endif /* !signgam */
#endif /* __USE_MISC || __USE_XOPEN */

#ifdef __COMPILER_HAVE_C11_GENERIC
#ifdef __COMPILER_HAVE_LONGDOUBLE
#define __FPFUNC(x, f, d, l)      _Generic(x, float: f(x), double: d(x), default: l(x))
#define __FPFUNC2(x, y, f, d, l)  _Generic((x) + (y), float: f(x, y), double: d(x, y), default: l(x, y))
#else /* __COMPILER_HAVE_LONGDOUBLE */
#define __FPFUNC(x, f, d, l)      _Generic(x, float: f(x), default: d(x))
#define __FPFUNC2(x, y, f, d, l)  _Generic((x) + (y), float: f(x, y), default: d(x, y))
#endif /* !__COMPILER_HAVE_LONGDOUBLE */
#elif (!defined(__NO_builtin_choose_expr) &&        \
       !defined(__NO_builtin_types_compatible_p) && \
       defined(__COMPILER_HAVE_TYPEOF))
#ifdef __COMPILER_HAVE_LONGDOUBLE
#define __FPFUNC(x, f, d, l)                                                                 \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((x) + 0.0f), float), f(x), \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((x) + 0.0), double), d(x), l(x)))
#define __FPFUNC2(x, y, f, d, l)                                                                      \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((x) + (y) + 0.0f), float), f(x, y), \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((x) + (y) + 0.0), double), d(x, y), l(x, y)))
#else /* __COMPILER_HAVE_LONGDOUBLE */
#define __FPFUNC(x, f, d, l) \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((x) + 0.0f), float), f(x), d(x))
#define __FPFUNC2(x, y, f, d, l) \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((x) + (y) + 0.0f), float), f(x, y), d(x, y))
#endif /* !__COMPILER_HAVE_LONGDOUBLE */
#elif !defined(__NO_builtin_types_compatible_p) && defined(__COMPILER_HAVE_TYPEOF)
#ifdef __COMPILER_HAVE_LONGDOUBLE
#define __FPFUNC(x, f, d, l)                                       \
	(__builtin_types_compatible_p(__typeof__((x) + 0.0f), float)   \
	 ? f((float)(x))                                               \
	 : __builtin_types_compatible_p(__typeof__((x) + 0.0), double) \
	   ? d((double)(x))                                            \
	   : l((__LONGDOUBLE)(x)))
#define __FPFUNC2(x, y, f, d, l)                                         \
	(__builtin_types_compatible_p(__typeof__((x) + (y) + 0.0f), float)   \
	 ? f((float)(x), (float)(y))                                         \
	 : __builtin_types_compatible_p(__typeof__((x) + (y) + 0.0), double) \
	   ? d((double)(x), (double)(y))                                     \
	   : l((__LONGDOUBLE)(x), (__LONGDOUBLE)(y)))
#else /* __COMPILER_HAVE_LONGDOUBLE */
#define __FPFUNC(x, f, d, l) \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((x) + 0.0f), float), f(x), d(x))
#define __FPFUNC2(x, y, f, d, l) \
	__builtin_choose_expr(__builtin_types_compatible_p(__typeof__((x) + (y) + 0.0f), float), f(x, y), d(x, y))
#endif /* !__COMPILER_HAVE_LONGDOUBLE */
#elif defined(__COMPILER_HAVE_LONGDOUBLE)
#define __FPFUNC(x, f, d, l)               \
	(sizeof((x) + 0.0f) == sizeof(float)   \
	 ? f((float)(x))                       \
	 : sizeof((x) + 0.0) == sizeof(double) \
	   ? d((double)(x))                    \
	   : l((__LONGDOUBLE)(x)))
#define __FPFUNC2(x, y, f, d, l)                 \
	(sizeof((x) + (y) + 0.0f) == sizeof(float)   \
	 ? f((float)(x), (float)(y))                 \
	 : sizeof((x) + (y) + 0.0) == sizeof(double) \
	   ? d((double)(x), (double)(y))             \
	   : l((__LONGDOUBLE)(x), (__LONGDOUBLE)(y)))
#else /* ... */
#define __FPFUNC(x, f, d, l)             \
	(sizeof((x) + 0.0f) == sizeof(float) \
	 ? f((float)(x))                     \
	 : d((double)(x)))
#define __FPFUNC2(x, y, f, d, l)               \
	(sizeof((x) + (y) + 0.0f) == sizeof(float) \
	 ? f((float)(x), (float)(y))               \
	 : d((double)(x), (double)(y)))
#endif /* ... */

#ifdef __USE_ISOC99
/*
 * float_t:    float-type at least as wide  as `float'; used to eval  `float'-expressions
 * double_t:   float-type at least as wide as `double'; used to eval `double'-expressions
 *
 * FLT_EVAL_METHOD:
 *    0:    `float_t' <=> `float',       `double_t' <=> `double'
 *    1:    `float_t' <=> `double',      `double_t' <=> `double'
 *    2:    `float_t' <=> `long double', `double_t' <=> `long double'
 *    else: Mapping of `float_t' and `double_t' is unspecified
 */
#if ((!defined(FP_NAN) && defined(__FP_NAN)) || (!defined(FP_INFINITE) && defined(__FP_INFINITE)) ||     \
     (!defined(FP_ZERO) && defined(__FP_ZERO)) || (!defined(FP_SUBNORMAL) && defined(__FP_SUBNORMAL)) || \
     (!defined(FP_NORMAL) && defined(__FP_NORMAL)))
/* Categories for floating-point numbers. */
/*[[[enum]]]*/
#ifdef __CC__
enum {
#if !defined(FP_NAN) && defined(__FP_NAN)
	FP_NAN = __FP_NAN, /* ... */
#endif /* !FP_NAN && __FP_NAN */
#if !defined(FP_INFINITE) && defined(__FP_INFINITE)
	FP_INFINITE = __FP_INFINITE, /* ... */
#endif /* !FP_INFINITE && __FP_INFINITE */
#if !defined(FP_ZERO) && defined(__FP_ZERO)
	FP_ZERO = __FP_ZERO, /* ... */
#endif /* !FP_ZERO && __FP_ZERO */
#if !defined(FP_SUBNORMAL) && defined(__FP_SUBNORMAL)
	FP_SUBNORMAL = __FP_SUBNORMAL, /* ... */
#endif /* !FP_SUBNORMAL && __FP_SUBNORMAL */
#if !defined(FP_NORMAL) && defined(__FP_NORMAL)
	FP_NORMAL = __FP_NORMAL /* ... */
#endif /* !FP_NORMAL && __FP_NORMAL */
};
#endif /* __CC__ */
/*[[[AUTO]]]*/
#ifdef __COMPILER_PREFERR_ENUMS
#if !defined(FP_NAN) && defined(__FP_NAN)
#define FP_NAN       FP_NAN       /* ... */
#endif /* !FP_NAN && __FP_NAN */
#if !defined(FP_INFINITE) && defined(__FP_INFINITE)
#define FP_INFINITE  FP_INFINITE  /* ... */
#endif /* !FP_INFINITE && __FP_INFINITE */
#if !defined(FP_ZERO) && defined(__FP_ZERO)
#define FP_ZERO      FP_ZERO      /* ... */
#endif /* !FP_ZERO && __FP_ZERO */
#if !defined(FP_SUBNORMAL) && defined(__FP_SUBNORMAL)
#define FP_SUBNORMAL FP_SUBNORMAL /* ... */
#endif /* !FP_SUBNORMAL && __FP_SUBNORMAL */
#if !defined(FP_NORMAL) && defined(__FP_NORMAL)
#define FP_NORMAL    FP_NORMAL    /* ... */
#endif /* !FP_NORMAL && __FP_NORMAL */
#else /* __COMPILER_PREFERR_ENUMS */
#if !defined(FP_NAN) && defined(__FP_NAN)
#define FP_NAN       __FP_NAN       /* ... */
#endif /* !FP_NAN && __FP_NAN */
#if !defined(FP_INFINITE) && defined(__FP_INFINITE)
#define FP_INFINITE  __FP_INFINITE  /* ... */
#endif /* !FP_INFINITE && __FP_INFINITE */
#if !defined(FP_ZERO) && defined(__FP_ZERO)
#define FP_ZERO      __FP_ZERO      /* ... */
#endif /* !FP_ZERO && __FP_ZERO */
#if !defined(FP_SUBNORMAL) && defined(__FP_SUBNORMAL)
#define FP_SUBNORMAL __FP_SUBNORMAL /* ... */
#endif /* !FP_SUBNORMAL && __FP_SUBNORMAL */
#if !defined(FP_NORMAL) && defined(__FP_NORMAL)
#define FP_NORMAL    __FP_NORMAL    /* ... */
#endif /* !FP_NORMAL && __FP_NORMAL */
#endif /* !__COMPILER_PREFERR_ENUMS */
/*[[[end]]]*/
#endif /* ... */

/* Figure out defaults for `float_t' and `double_t' if those
 * haven't  already  been defined  by `<bits/crt/mathdef.h>' */
#if !defined(__float_t) || !defined(__double_t)
#if (defined(__FLT_EVAL_METHOD__) && (__FLT_EVAL_METHOD__ + 0) == 2)
#ifdef __COMPILER_HAVE_LONGDOUBLE
#define __float_t  __LONGDOUBLE
#define __double_t __LONGDOUBLE
#else /* __COMPILER_HAVE_LONGDOUBLE */
#define __float_t  double
#define __double_t double
#endif /* !__COMPILER_HAVE_LONGDOUBLE */
#elif (defined(__FLT_EVAL_METHOD__) && (__FLT_EVAL_METHOD__ + 0) == 1)
#define __float_t  double
#define __double_t double
#else /* __FLT_EVAL_METHOD__ == ... */
#define __float_t  float
#define __double_t double
#endif /* __FLT_EVAL_METHOD__ != ... */
#endif /* !__float_t || !__double_t */

/* `float' expressions are evaluated as this. */
typedef __float_t float_t;

/* `double' expressions are evaluated as this. */
typedef __double_t double_t;


#ifndef __OPTIMIZE_SIZE__
#if __has_builtin(__builtin_signbitf) && __has_builtin(__builtin_signbit) && __has_builtin(__builtin_signbitl)
#define signbit(x) __FPFUNC(x, __builtin_signbitf, __builtin_signbit, __builtin_signbitl)
#endif /* __builtin_signbitf && __builtin_signbit && __builtin_signbitl */
#ifndef __SUPPORT_SNAN__
#if (__has_builtin(__builtin_fpclassify) &&             \
     defined(__FP_NAN) && defined(__FP_INFINITE) &&     \
     defined(__FP_NORMAL) && defined(__FP_SUBNORMAL) && \
     defined(__FP_ZERO))
#define fpclassify(x) __builtin_fpclassify(__FP_NAN, __FP_INFINITE, __FP_NORMAL, __FP_SUBNORMAL, __FP_ZERO, x)
#endif /* __builtin_fpclassify && defined(__FP_...) */
#if __has_builtin(__builtin_isfinite)
#define isfinite(x) __builtin_isfinite(x)
#endif /* __builtin_isfinite */
#if __has_builtin(__builtin_isnormal)
#define isnormal(x) __builtin_isnormal(x)
#endif /* __builtin_isnormal */
#if __has_builtin(__builtin_isnan)
#define isnan(x) __builtin_isnan(x)
#endif /* __builtin_isnan */
#if __has_builtin(__builtin_isinf_sign)
#define isinf(x) __builtin_isinf_sign(x)
#endif /* __builtin_isinf_sign */
#endif /* !__SUPPORT_SNAN__ */
#endif /* !__OPTIMIZE_SIZE__ */

#ifndef fpclassify
#define fpclassify(x) __FPFUNC(x, __fpclassifyf, __fpclassify, __fpclassifyl)
#endif /* !fpclassify */

#ifndef signbit
#define signbit(x) __FPFUNC(x, __signbitf, __signbit, __signbitl)
#endif /* !signbit */

#ifndef isnormal
#ifdef fpclassify
#ifdef __FP_NORMAL
#define isnormal(x) (fpclassify(x) == __FP_NORMAL)
#endif /* __FP_NORMAL */
#endif /* fpclassify */
#endif /* !isnormal */

#ifndef isfinite
#define isfinite(x) __FPFUNC(x, __finitef, __finite, __finitel)
#endif /* !isfinite */

#ifndef isnan
#define isnan(x) __FPFUNC(x, __isnanf, __isnan, __isnanl)
#endif /* !isnan */

#ifndef isinf
#define isinf(x) __FPFUNC(x, __isinff, __isinf, __isinfl)
#endif /* !isinf */

#ifdef __USE_ISOC99
#if ((defined(__CRT_HAVE__dpcomp) && !defined(__stub__dpcomp)) &&    \
     (defined(__CRT_HAVE__fdpcomp) && !defined(__stub__fdpcomp)) &&  \
     ((defined(__CRT_HAVE__ldpcomp) && !defined(__stub__ldpcomp)) || \
       defined(__ARCH_LONG_DOUBLE_IS_DOUBLE)))
#undef __PRIVATE_DOS_FPCOMPARE_USED /* vvv Only use if no alternative, or on WIN32 */
#if (!defined(__LIBM_MATHFUNXF) || !defined(__LIBM_MATHFUNX) || !defined(__LIBM_MATHFUNXL) || defined(_WIN32))
#define __PRIVATE_DOS_FPCOMPARE(x, y) __FPFUNC2(x, y, _fdpcomp, _dpcomp, _ldpcomp)
#endif /* ... */
#endif /* ... */

/* Generic... */
#ifndef isunordered
#if __has_builtin(__builtin_isunordered) && !defined(__OPTIMIZE_SIZE__)
#define isunordered(u, v) __builtin_isunordered(u, v)
#elif defined(__PRIVATE_DOS_FPCOMPARE)
#define __PRIVATE_DOS_FPCOMPARE_USED
#define isunordered(u, v) (__PRIVATE_DOS_FPCOMPARE(u, v) == 0)
#elif defined(__LIBM_MATHFUNXF) && defined(__LIBM_MATHFUNX) && defined(__LIBM_MATHFUNXL)
#define isunordered(u, v) __FPFUNC2(u, v, __LIBM_MATHFUNXF(isunordered), __LIBM_MATHFUNX(isunordered), __LIBM_MATHFUNXL(isunordered))
#elif defined(fpclassify) && defined(__FP_NAN)
#define isunordered(u, v) (fpclassify(u) == __FP_NAN || fpclassify(v) == __FP_NAN)
#else /* ... */
#define isunordered(u, v) 0
#endif /* !... */
#endif /* !isunordered */

#ifndef isgreater
#if __has_builtin(__builtin_isgreater) && !defined(__OPTIMIZE_SIZE__)
#define isgreater(x, y) __builtin_isgreater(x, y)
#elif defined(__PRIVATE_DOS_FPCOMPARE)
#define __PRIVATE_DOS_FPCOMPARE_USED
#define isgreater(x, y) ((__PRIVATE_DOS_FPCOMPARE(x, y)&4) != 0)
#elif defined(__LIBM_MATHFUNXF) && defined(__LIBM_MATHFUNX) && defined(__LIBM_MATHFUNXL)
#define isgreater(x, y) __FPFUNC2(x, y, __LIBM_MATHFUNXF(isgreater), __LIBM_MATHFUNX(isgreater), __LIBM_MATHFUNXL(isgreater))
#elif !defined(__NO_XBLOCK) && defined(__COMPILER_HAVE_AUTOTYPE)
#define isgreater(x, y) __XBLOCK({ __auto_type __isg_x = (x); __auto_type __isg_y = (y); __XRETURN !isunordered(__isg_x, __isg_y) && __isg_x > __isg_y; })
#elif !defined(__NO_XBLOCK) && defined(__COMPILER_HAVE_TYPEOF)
#define isgreater(x, y) __XBLOCK({ __typeof__(x) __isg_x = (x); __typeof__(y) __isg_y = (y); __XRETURN !isunordered(__isg_x, __isg_y) && __isg_x > __isg_y; })
#else /* ... */
#define isgreater(x, y) (!isunordered(x, y) && (x) > (y))
#endif /* !... */
#endif /* !isgreater */

#ifndef isgreaterequal
#if __has_builtin(__builtin_isgreaterequal) && !defined(__OPTIMIZE_SIZE__)
#define isgreaterequal(x, y) __builtin_isgreaterequal(x, y)
#elif defined(__PRIVATE_DOS_FPCOMPARE)
#define __PRIVATE_DOS_FPCOMPARE_USED
#define isgreaterequal(x, y) ((__PRIVATE_DOS_FPCOMPARE(x, y)&6) != 0)
#elif defined(__LIBM_MATHFUNXF) && defined(__LIBM_MATHFUNX) && defined(__LIBM_MATHFUNXL)
#define isgreaterequal(x, y) __FPFUNC2(x, y, __LIBM_MATHFUNXF(isgreaterequal), __LIBM_MATHFUNX(isgreaterequal), __LIBM_MATHFUNXL(isgreaterequal))
#elif !defined(__NO_XBLOCK) && defined(__COMPILER_HAVE_AUTOTYPE)
#define isgreaterequal(x, y) __XBLOCK({ __auto_type __isge_x = (x); __auto_type __isge_y = (y); __XRETURN !isunordered(__isge_x, __isge_y) && __isge_x >= __isge_y; })
#elif !defined(__NO_XBLOCK) && defined(__COMPILER_HAVE_TYPEOF)
#define isgreaterequal(x, y) __XBLOCK({ __typeof__(x) __isge_x = (x); __typeof__(y) __isge_y = (y); __XRETURN !isunordered(__isge_x, __isge_y) && __isge_x >= __isge_y; })
#else /* ... */
#define isgreaterequal(x, y) (!isunordered(x, y) && (x) >= (y))
#endif /* !... */
#endif /* !isgreaterequal */

#ifndef isless
#if __has_builtin(__builtin_isless) && !defined(__OPTIMIZE_SIZE__)
#define isless(x, y) __builtin_isless(x, y)
#elif defined(__PRIVATE_DOS_FPCOMPARE)
#define __PRIVATE_DOS_FPCOMPARE_USED
#define isless(x, y) ((__PRIVATE_DOS_FPCOMPARE(x, y)&1) != 0)
#elif defined(__LIBM_MATHFUNXF) && defined(__LIBM_MATHFUNX) && defined(__LIBM_MATHFUNXL)
#define isless(x, y) __FPFUNC2(x, y, __LIBM_MATHFUNXF(isless), __LIBM_MATHFUNX(isless), __LIBM_MATHFUNXL(isless))
#elif !defined(__NO_XBLOCK) && defined(__COMPILER_HAVE_AUTOTYPE)
#define isless(x, y) __XBLOCK({ __auto_type __isl_x = (x); __auto_type __isl_y = (y); __XRETURN !isunordered(__isl_x, __isl_y) && __isl_x < __isl_y; })
#elif !defined(__NO_XBLOCK) && defined(__COMPILER_HAVE_TYPEOF)
#define isless(x, y) __XBLOCK({ __typeof__(x) __isl_x = (x); __typeof__(y) __isl_y = (y); __XRETURN !isunordered(__isl_x, __isl_y) && __isl_x < __isl_y; })
#else /* ... */
#define isless(x, y) (!isunordered(x, y) && (x) < (y))
#endif /* !... */
#endif /* !isless */

#ifndef islessequal
#if __has_builtin(__builtin_islessequal) && !defined(__OPTIMIZE_SIZE__)
#define islessequal(x, y) __builtin_islessequal(x, y)
#elif defined(__PRIVATE_DOS_FPCOMPARE)
#define __PRIVATE_DOS_FPCOMPARE_USED
#define islessequal(x, y) ((__PRIVATE_DOS_FPCOMPARE(x, y)&3) != 0)
#elif defined(__LIBM_MATHFUNXF) && defined(__LIBM_MATHFUNX) && defined(__LIBM_MATHFUNXL)
#define islessequal(x, y) __FPFUNC2(x, y, __LIBM_MATHFUNXF(islessequal), __LIBM_MATHFUNX(islessequal), __LIBM_MATHFUNXL(islessequal))
#elif !defined(__NO_XBLOCK) && defined(__COMPILER_HAVE_AUTOTYPE)
#define islessequal(x, y) __XBLOCK({ __auto_type __isle_x = (x); __auto_type __isle_y = (y); __XRETURN !isunordered(__isle_x, __isle_y) && __isle_x <= __isle_y; })
#elif !defined(__NO_XBLOCK) && defined(__COMPILER_HAVE_TYPEOF)
#define islessequal(x, y) __XBLOCK({ __typeof__(x) __isle_x = (x); __typeof__(y) __isle_y = (y); __XRETURN !isunordered(__isle_x, __isle_y) && __isle_x <= __isle_y; })
#else /* ... */
#define islessequal(x, y) (!isunordered(x, y) && (x) <= (y))
#endif /* !... */
#endif /* !islessequal */

#ifndef islessgreater
#if __has_builtin(__builtin_islessgreater) && !defined(__OPTIMIZE_SIZE__)
#define islessgreater(x, y) __builtin_islessgreater(x, y)
#elif defined(__PRIVATE_DOS_FPCOMPARE)
#define __PRIVATE_DOS_FPCOMPARE_USED
#define islessgreater(x, y) ((__PRIVATE_DOS_FPCOMPARE(x, y)&5) != 0)
#elif defined(__LIBM_MATHFUNXF) && defined(__LIBM_MATHFUNX) && defined(__LIBM_MATHFUNXL)
#define islessgreater(x, y) __FPFUNC2(x, y, __LIBM_MATHFUNXF(islessgreater), __LIBM_MATHFUNX(islessgreater), __LIBM_MATHFUNXL(islessgreater))
#elif !defined(__NO_XBLOCK) && defined(__COMPILER_HAVE_AUTOTYPE)
#define islessgreater(x, y) __XBLOCK({ __auto_type __islg_x = (x); __auto_type __islg_y = (y); __XRETURN !isunordered(__islg_x, __islg_y) && (__islg_x < __islg_y || __islg_y < __islg_x); })
#elif !defined(__NO_XBLOCK) && defined(__COMPILER_HAVE_TYPEOF)
#define islessgreater(x, y) __XBLOCK({ __typeof__(x) __islg_x = (x); __typeof__(y) __islg_y = (y); __XRETURN !isunordered(__islg_x, __islg_y) && (__islg_x < __islg_y || __islg_y < __islg_x); })
#else /* ... */
#define islessgreater(x, y) (!isunordered(x, y) && ((x) < (y) || (y) < (x)))
#endif /* !... */
#endif /* !islessgreater */

#ifdef __PRIVATE_DOS_FPCOMPARE
#ifdef __PRIVATE_DOS_FPCOMPARE_USED
#undef __PRIVATE_DOS_FPCOMPARE_USED
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,_fdpcomp,(float __x, float __y),(__x,__y))
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,_dpcomp,(double __x, double __y),(__x,__y))
#ifdef __COMPILER_HAVE_LONGDOUBLE
#ifdef __ARCH_LONG_DOUBLE_IS_DOUBLE
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,_ldpcomp,(__LONGDOUBLE __x, __LONGDOUBLE __y),_dpcomp,(__x,__y))
#else /* __ARCH_LONG_DOUBLE_IS_DOUBLE */
__CDECLARE(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,_ldpcomp,(__LONGDOUBLE __x, __LONGDOUBLE __y),(__x,__y))
#endif /* !__ARCH_LONG_DOUBLE_IS_DOUBLE */
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#else /* __PRIVATE_DOS_FPCOMPARE_USED */
#undef __PRIVATE_DOS_FPCOMPARE
#endif /* !__PRIVATE_DOS_FPCOMPARE_USED */
#endif /* __PRIVATE_DOS_FPCOMPARE */
#endif /* __USE_ISOC99 */




#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP11_MATH_H_PROTO_FP)
/* Libstdc++ headers need us to define these as functions when also
 * defining `__CORRECT_ISO_CPP11_MATH_H_PROTO_FP', which we need to
 * do in order to get it to stop re-declaring other functions  such
 * as `acosh'... *ugh* */
__NAMESPACE_STD_BEGIN
extern "C++" {
#ifdef fpclassify
#ifndef __std_fpclassify_defined
#define __std_fpclassify_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(fpclassify)(float __x) { return fpclassify(__x); }
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(fpclassify)(double __x) { return fpclassify(__x); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(fpclassify)(__LONGDOUBLE __x) { return fpclassify(__x); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_fpclassify_defined */
#undef fpclassify
#endif /* fpclassify */
#ifdef signbit
#ifndef __std_signbit_defined
#define __std_signbit_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __BOOL __NOTHROW(signbit)(float __x) { return signbit(__x); }
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __BOOL __NOTHROW(signbit)(double __x) { return signbit(__x); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __BOOL __NOTHROW(signbit)(__LONGDOUBLE __x) { return signbit(__x); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_signbit_defined */
#undef signbit
#endif /* signbit */
#ifdef isnormal
#ifndef __std_isnormal_defined
#define __std_isnormal_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __BOOL __NOTHROW(isnormal)(float __x) { return isnormal(__x); }
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __BOOL __NOTHROW(isnormal)(double __x) { return isnormal(__x); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __BOOL __NOTHROW(isnormal)(__LONGDOUBLE __x) { return isnormal(__x); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_isnormal_defined */
#undef isnormal
#endif /* isnormal */
#ifdef isfinite
#ifndef __std_isfinite_defined
#define __std_isfinite_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __BOOL __NOTHROW(isfinite)(float __x) { return isfinite(__x); }
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __BOOL __NOTHROW(isfinite)(double __x) { return isfinite(__x); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __BOOL __NOTHROW(isfinite)(__LONGDOUBLE __x) { return isfinite(__x); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_isfinite_defined */
#undef isfinite
#endif /* isfinite */
#ifdef isnan
#ifndef __std_isnan_defined
#define __std_isnan_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __BOOL __NOTHROW(isnan)(float __x) { return isnan(__x); }
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __BOOL __NOTHROW(isnan)(double __x) { return isnan(__x); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __BOOL __NOTHROW(isnan)(__LONGDOUBLE __x) { return isnan(__x); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_isnan_defined */
#undef isnan
#endif /* isnan */
#ifdef isinf
#ifndef __std_isinf_defined
#define __std_isinf_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __BOOL __NOTHROW(isinf)(float __x) { return isinf(__x); }
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __BOOL __NOTHROW(isinf)(double __x) { return isinf(__x); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __BOOL __NOTHROW(isinf)(__LONGDOUBLE __x) { return isinf(__x); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_isinf_defined */
#undef isinf
#endif /* isinf */
#ifdef isunordered
#ifndef __std_isunordered_defined
#define __std_isunordered_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __BOOL __NOTHROW(isunordered)(float __x, float __y) { return isunordered(__x, __y); }
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __BOOL __NOTHROW(isunordered)(double __x, double __y) { return isunordered(__x, __y); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __BOOL __NOTHROW(isunordered)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return isunordered(__x, __y); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_isunordered_defined */
#undef isunordered
#endif /* isunordered */
#ifdef isgreater
#ifndef __std_isgreater_defined
#define __std_isgreater_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __BOOL __NOTHROW(isgreater)(float __x, float __y) { return isgreater(__x, __y); }
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __BOOL __NOTHROW(isgreater)(double __x, double __y) { return isgreater(__x, __y); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __BOOL __NOTHROW(isgreater)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return isgreater(__x, __y); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_isgreater_defined */
#undef isgreater
#endif /* isgreater */
#ifdef isgreaterequal
#ifndef __std_isgreaterequal_defined
#define __std_isgreaterequal_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __BOOL __NOTHROW(isgreaterequal)(float __x, float __y) { return isgreaterequal(__x, __y); }
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __BOOL __NOTHROW(isgreaterequal)(double __x, double __y) { return isgreaterequal(__x, __y); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __BOOL __NOTHROW(isgreaterequal)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return isgreaterequal(__x, __y); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_isgreaterequal_defined */
#undef isgreaterequal
#endif /* isgreaterequal */
#ifdef isless
#ifndef __std_isless_defined
#define __std_isless_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __BOOL __NOTHROW(isless)(float __x, float __y) { return isless(__x, __y); }
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __BOOL __NOTHROW(isless)(double __x, double __y) { return isless(__x, __y); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __BOOL __NOTHROW(isless)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return isless(__x, __y); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_isless_defined */
#undef isless
#endif /* isless */
#ifdef islessequal
#ifndef __std_islessequal_defined
#define __std_islessequal_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __BOOL __NOTHROW(islessequal)(float __x, float __y) { return islessequal(__x, __y); }
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __BOOL __NOTHROW(islessequal)(double __x, double __y) { return islessequal(__x, __y); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __BOOL __NOTHROW(islessequal)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return islessequal(__x, __y); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_islessequal_defined */
#undef islessequal
#endif /* islessequal */
#ifdef islessgreater
#ifndef __std_islessgreater_defined
#define __std_islessgreater_defined
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __BOOL __NOTHROW(islessgreater)(float __x, float __y) { return islessgreater(__x, __y); }
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __BOOL __NOTHROW(islessgreater)(double __x, double __y) { return islessgreater(__x, __y); }
#ifdef __COMPILER_HAVE_LONGDOUBLE
__FORCELOCAL __ATTR_ARTIFICIAL __ATTR_CONST __ATTR_WUNUSED __BOOL __NOTHROW(islessgreater)(__LONGDOUBLE __x, __LONGDOUBLE __y) { return islessgreater(__x, __y); }
#endif /* __COMPILER_HAVE_LONGDOUBLE */
#endif /* !__std_islessgreater_defined */
#undef islessgreater
#endif /* islessgreater */
} /* extern "C++" */
__NAMESPACE_STD_END
#ifndef __CXX_SYSTEM_HEADER
}%(c, ccompat){
#ifdef __std_fpclassify_defined
__NAMESPACE_STD_USING(fpclassify)
#endif /* __std_fpclassify_defined */
#ifdef __std_signbit_defined
__NAMESPACE_STD_USING(signbit)
#endif /* __std_signbit_defined */
#ifdef __std_isnormal_defined
__NAMESPACE_STD_USING(isnormal)
#endif /* __std_isnormal_defined */
#ifdef __std_isfinite_defined
__NAMESPACE_STD_USING(isfinite)
#endif /* __std_isfinite_defined */
#ifdef __std_isnan_defined
__NAMESPACE_STD_USING(isnan)
#endif /* __std_isnan_defined */
#ifdef __std_isinf_defined
__NAMESPACE_STD_USING(isinf)
#endif /* __std_isinf_defined */
#ifdef __std_isunordered_defined
__NAMESPACE_STD_USING(isunordered)
#endif /* __std_isunordered_defined */
#ifdef __std_isgreater_defined
__NAMESPACE_STD_USING(isgreater)
#endif /* __std_isgreater_defined */
#ifdef __std_isgreaterequal_defined
__NAMESPACE_STD_USING(isgreaterequal)
#endif /* __std_isgreaterequal_defined */
#ifdef __std_isless_defined
__NAMESPACE_STD_USING(isless)
#endif /* __std_isless_defined */
#ifdef __std_islessequal_defined
__NAMESPACE_STD_USING(islessequal)
#endif /* __std_islessequal_defined */
#ifdef __std_islessgreater_defined
__NAMESPACE_STD_USING(islessgreater)
#endif /* __std_islessgreater_defined */
}%{
#endif /* !__CXX_SYSTEM_HEADER */
#endif /* __cplusplus && __CORRECT_ISO_CPP11_MATH_H_PROTO_FP */

/* Bit values for `math_errhandling'. */
#define MATH_ERRNO     1 /* Errno is set by math functions. */
#define MATH_ERREXCEPT 2 /* Exceptions are raised by math functions. */

/* By   default,   all  functions   support   both  errno   and   exception  handling.
 * In gcc's fast math mode and if inline functions are defined this might not be true. */
#ifndef __FAST_MATH__
#define math_errhandling (MATH_ERRNO | MATH_ERREXCEPT)
#endif /* !__FAST_MATH__ */
#endif /* __USE_ISOC99 */


#if defined(__USE_GNU) || defined(__STDC_WANT_IEC_60559_BFP_EXT__)
#ifndef iscanonical
#define iscanonical(x) __FPFUNC(x, __iscanonicalf, __iscanonical, __iscanonicall)
#endif /* !iscanonical */

#ifndef issignaling
#define issignaling(x) __FPFUNC(x, __issignalingf, __issignaling, __issignalingl)
#endif /* !issignaling */

#if !defined(issubnormal) && defined(__FP_SUBNORMAL)
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP11_MATH_H_PROTO_FP)
#define issubnormal(x) (std::fpclassify(x) == __FP_SUBNORMAL)
#else /* __cplusplus && __CORRECT_ISO_CPP11_MATH_H_PROTO_FP */
#define issubnormal(x) (fpclassify(x) == __FP_SUBNORMAL)
#endif /* !__cplusplus || !__CORRECT_ISO_CPP11_MATH_H_PROTO_FP */
#endif /* !issubnormal && __FP_SUBNORMAL */

#ifndef iszero
#ifdef __SUPPORT_SNAN__
#ifdef __FP_ZERO
#if defined(__cplusplus) && defined(__CORRECT_ISO_CPP11_MATH_H_PROTO_FP)
#define iszero(x) (std::fpclassify(x) == __FP_ZERO)
#else /* __cplusplus && __CORRECT_ISO_CPP11_MATH_H_PROTO_FP */
#define iszero(x) (fpclassify(x) == __FP_ZERO)
#endif /* !__cplusplus || !__CORRECT_ISO_CPP11_MATH_H_PROTO_FP */
#endif /* __FP_ZERO */
#else /* __SUPPORT_SNAN__ */
#ifdef __COMPILER_HAVE_TYPEOF
#define iszero(x) (((__typeof__(x))(x)) == 0)
#else /* __COMPILER_HAVE_TYPEOF */
#define iszero(x) ((x) == 0)
#endif /* !__COMPILER_HAVE_TYPEOF */
#endif /* !__SUPPORT_SNAN__ */
#endif /* !iszero */

#ifndef iseqsig
#define iseqsig(x, y) __FPFUNC2(x, y, __iseqsigf, __iseqsig, __iseqsigl)
#endif /* !iseqsig */
#endif /* __USE_GNU || __STDC_WANT_IEC_60559_BFP_EXT__ */


#ifdef __USE_MISC
#if (defined(___IEEE_) || defined(___SVID_) ||   \
     defined(___XOPEN_) || defined(___POSIX_) || \
     defined(___ISOC_))
}%[push_macro @undef { _IEEE_ _SVID_ _XOPEN_ _POSIX_ _ISOC_ }]%{
/* Possible behavior for math standard error handling. */
typedef enum {
#ifdef ___IEEE_
	_IEEE_ = ___IEEE_,   /* s.a. IEEE 754/IEEE 854. */
#endif /* ___IEEE_ */
#ifdef ___SVID_
	_SVID_ = ___SVID_,   /* s.a. SysV, release 4. */
#endif /* ___SVID_ */
#ifdef ___XOPEN_
	_XOPEN_ = ___XOPEN_, /* aka. Unix98. */
#endif /* ___XOPEN_ */
#ifdef ___POSIX_
	_POSIX_ = ___POSIX_, /* ... */
#endif /* ___POSIX_ */
#ifdef ___ISOC_
	_ISOC_ = ___ISOC_    /* ISO C99. */
#endif /* ___ISOC_ */
} _LIB_VERSION_TYPE;
}%[pop_macro]%{

/* One of `_LIB_VERSION_TYPE': The current math error behavior */
#ifndef _LIB_VERSION
#ifdef __CRT_HAVE__LIB_VERSION
__CSDECLARE(,_LIB_VERSION_TYPE,_LIB_VERSION)
#define _LIB_VERSION _LIB_VERSION
#endif /* __CRT_HAVE__LIB_VERSION */
#endif /* !_LIB_VERSION */
#endif /* ... */


/* With SVID error handling, `matherr(3)' gets called with this struct on error:
 * >> int matherr(struct exception *exc) {
 * >>     ...
 * >> }
 * Yes: programs must simply define this function (with PUBLIC visibility), and
 * libc  will detect that  override and call their  function to facilitate math
 * error handling. */
#ifdef __cplusplus
struct __exception
#else /* __cplusplus */
}%[push_macro @undef { exception }]%{
struct exception
#endif /* !__cplusplus */
}%[push_macro @undef { type name arg1 arg2 retval err }]%{
{
	int                     type;   /* Exception type (one of `__MATH_EXCEPT_*'; s.a. the unescaped macros below) */
	char __KOS_FIXED_CONST *name;   /* [1..1] Math function name (e.g. "powf") */
	double                  arg1;   /* First argument */
	double                  arg2;   /* Second argument */
	double                  retval; /* [in|out] Return value */
	__errno_t               err;    /* [out] If non-zero, set as errno when `matherr(3)' returns `0' */
#ifdef __CRT_DOS
	int                   __pad;    /* ... */
#endif /* __CRT_DOS */
};
}%[pop_macro]%{

#ifdef __CRT_HAVE_matherr
#ifdef __cplusplus
__CDECLARE(,int,__NOTHROW,matherr,(struct __exception *__exc),(__exc))
#else /* __cplusplus */
__CDECLARE(,int,__NOTHROW,matherr,(struct exception *__exc),(__exc))
}%[pop_macro]%{
#endif /* !__cplusplus */
#endif /* __CRT_HAVE_matherr */

#define X_TLOSS 1.41484755040568800000e+16

/* Values for `exception::type' */
#ifdef __MATH_EXCEPT_DOMAIN
#define DOMAIN __MATH_EXCEPT_DOMAIN /* ... */
#endif /* __MATH_EXCEPT_DOMAIN */
#ifdef __MATH_EXCEPT_SING
#define SING __MATH_EXCEPT_SING /* ... */
#endif /* __MATH_EXCEPT_SING */
#ifdef __MATH_EXCEPT_OVERFLOW
#define OVERFLOW __MATH_EXCEPT_OVERFLOW /* ... */
#endif /* __MATH_EXCEPT_OVERFLOW */
#ifdef __MATH_EXCEPT_UNDERFLOW
#define UNDERFLOW __MATH_EXCEPT_UNDERFLOW /* ... */
#endif /* __MATH_EXCEPT_UNDERFLOW */
#ifdef __MATH_EXCEPT_TLOSS
#define TLOSS __MATH_EXCEPT_TLOSS /* ... */
#endif /* __MATH_EXCEPT_TLOSS */
#ifdef __MATH_EXCEPT_PLOSS
#define PLOSS __MATH_EXCEPT_PLOSS /* ... */
#endif /* __MATH_EXCEPT_PLOSS */

#define HUGE 3.40282347e+38F /* SVID-specific constant */
#else /* __USE_MISC */
#ifdef __USE_XOPEN
#define MAXFLOAT 3.40282347e+38F /* X/Open-specific constant */
#endif /* __USE_XOPEN */
#endif /* !__USE_MISC */

}


%{

__SYSDECL_END
#endif /* __CC__ */

#ifdef __USE_DOS
#if !defined(_INFCODE) && defined(__FP_INFINITE)
#define _INFCODE __FP_INFINITE
#endif /* !_INFCODE && __FP_INFINITE */
#if !defined(_NANCODE) && defined(__FP_NAN)
#define _NANCODE __FP_NAN
#endif /* !_NANCODE && __FP_NAN */
#if !defined(_FINITE) && defined(__FP_NORMAL)
#define _FINITE  __FP_NORMAL
#endif /* !_FINITE && __FP_NORMAL */
#if !defined(_DENORM) && defined(__FP_SUBNORMAL)
#define _DENORM  __FP_SUBNORMAL
#endif /* !_DENORM && __FP_SUBNORMAL */

#ifdef __CC__
__SYSDECL_BEGIN
}

%[default:section(".text.crt.dos.math.math")]

%[define_c_language_keyword(__KOS_FIXED_CONST)]

@@>> _fdtest(3), _dtest(3), _ldtest(3)
[[pure, crt_dos_variant, wunused, decl_include("<features.h>")]]
short _dtest([[in]] double __KOS_FIXED_CONST *px) {
	return __fpclassify(*px);
}

[[crt_dos_variant]] _fdtest(*) %{generate(double2float("_dtest"))}
[[crt_dos_variant]] _ldtest(*) %{generate(double2ldouble("_dtest"))}

[[const, wunused, nothrow]]
float _chgsignf(float x) {
	return -x;
}

[[guard, const, wunused, nothrow]]
double _chgsign(double x) {
	return -x;
}


%{
__SYSDECL_END
#endif /* __CC__ */
#endif /* __USE_DOS */

}
%(c, ccompat)#endif /* !__NO_FPU */
