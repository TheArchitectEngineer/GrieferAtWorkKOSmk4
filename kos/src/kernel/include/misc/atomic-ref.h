/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_MISC_ATOMIC_REF_H
#define GUARD_KERNEL_INCLUDE_MISC_ATOMIC_REF_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <sched/task.h>

#include <hybrid/__assert.h>
#include <hybrid/__atomic.h>

#include <kos/aref.h>

#ifdef __CC__
DECL_BEGIN

#ifdef __cplusplus
extern "C++" {

/* TODO: Everything in here is deprecated! (use <kos/aref.h> instead!) */

#define ATOMIC_REF(...)  atomic_ref< __VA_ARGS__ >
template<class T> struct atomic_ref {

#define ATOMIC_REF_INIT(p)        { ARREF_INIT(p) }
#define atomic_ref_init(self, p)  arref_init(&(self)->m_me, p)
#define atomic_ref_cinit(self, p) arref_cinit(&(self)->m_me, p)
#define atomic_ref_fini(self)     arref_fini(&(self)->m_me)
	ARREF(T) m_me;

	__CXX_CLASSMEMBER NOBLOCK ATTR_LEAF ATTR_RETNONNULL WUNUSED REF T *KCALL get() __CXX_NOEXCEPT { return arref_get(&m_me); }
	__CXX_CLASSMEMBER NOBLOCK NOPREEMPT ATTR_LEAF ATTR_RETNONNULL WUNUSED REF T *KCALL get_nopr() __CXX_NOEXCEPT { return arref_get_nopr(&m_me); }
	__CXX_CLASSMEMBER NOBLOCK NONNULL_CXX((1)) void KCALL set(T *__restrict new_pointer) __CXX_NOEXCEPT { arref_set(&m_me, new_pointer); }
	__CXX_CLASSMEMBER NOBLOCK NONNULL_CXX((1)) void KCALL set_inherit_new(REF T *__restrict new_pointer) __CXX_NOEXCEPT { arref_set_inherit(&m_me, new_pointer); }
	__CXX_CLASSMEMBER NOBLOCK ATTR_LEAF ATTR_RETNONNULL WUNUSED NONNULL_CXX((1)) REF T *KCALL exchange(T *__restrict new_pointer) __CXX_NOEXCEPT { return arref_xch(&m_me, new_pointer); }
	__CXX_CLASSMEMBER NOBLOCK ATTR_LEAF ATTR_RETNONNULL WUNUSED NONNULL_CXX((1)) REF T *KCALL exchange_inherit_new(REF T *__restrict new_pointer) __CXX_NOEXCEPT { return arref_xch_inherit(&m_me, new_pointer); }
	__CXX_CLASSMEMBER NOBLOCK NONNULL_CXX((1, 2)) bool KCALL cmpxch(T *__restrict old_pointer, T *__restrict new_pointer) __CXX_NOEXCEPT { return arref_cmpxch(&m_me, old_pointer, new_pointer); }
	__CXX_CLASSMEMBER NOBLOCK NONNULL_CXX((1, 2)) bool KCALL cmpxch_inherit_new(T *__restrict old_pointer, /*inherit(on_success)*/ REF T *__restrict new_pointer) __CXX_NOEXCEPT { return arref_cmpxch_inherit_new(&m_me, old_pointer, new_pointer); }
};

#define XATOMIC_REF_STRUCT(...) xatomic_ref_struct< __VA_ARGS__ >
#define XATOMIC_REF(...)        xatomic_ref< __VA_ARGS__ >
template<class T> struct xatomic_ref_struct { AXREF(T) m_me; };

template<class T> struct xatomic_ref {

#define XATOMIC_REF_INIT(p)        { AXREF_INIT(p) }
#define xatomic_ref_init(self, p)  axref_init(&(self)->m_me, p)
#define xatomic_ref_cinit(self, p) axref_cinit(&(self)->m_me, p)
#define xatomic_ref_fini(self)     axref_fini(&(self)->m_me)
	AXREF(T) m_me;

	__CXX_CLASSMEMBER NOBLOCK void KCALL clear() __CXX_NOEXCEPT { axref_clear(&m_me); }
	__CXX_CLASSMEMBER NOBLOCK ATTR_LEAF WUNUSED REF T *KCALL get() __CXX_NOEXCEPT { return axref_get(&m_me); }
	__CXX_CLASSMEMBER NOBLOCK ATTR_LEAF WUNUSED REF T *KCALL get_nopr() __CXX_NOEXCEPT { return axref_get_nopr(&m_me);  }
	__CXX_CLASSMEMBER NOBLOCK void KCALL set(T *new_pointer) __CXX_NOEXCEPT { axref_set(&m_me, new_pointer); }
	__CXX_CLASSMEMBER NOBLOCK void KCALL set_inherit_new(REF T *new_pointer) __CXX_NOEXCEPT { axref_set_inherit(&m_me, new_pointer); }
	__CXX_CLASSMEMBER ATTR_LEAF WUNUSED NOBLOCK REF T *KCALL exchange(T *new_pointer) __CXX_NOEXCEPT { return axref_xch(&m_me, new_pointer); }
	__CXX_CLASSMEMBER ATTR_LEAF WUNUSED NOBLOCK REF T *KCALL exchange_inherit_new(REF T *new_pointer) __CXX_NOEXCEPT { return axref_xch_inherit(&m_me, new_pointer); }
	__CXX_CLASSMEMBER NOBLOCK bool KCALL cmpxch(T *old_pointer, T *new_pointer) __CXX_NOEXCEPT { return axref_cmpxch(&m_me, old_pointer, new_pointer); }
	__CXX_CLASSMEMBER NOBLOCK bool KCALL cmpxch_inherit_new(T *old_pointer, /*inherit(on_success)*/ REF T *new_pointer) __CXX_NOEXCEPT { return axref_cmpxch_inherit_new(&m_me, old_pointer, new_pointer); }
};

#define XATOMIC_WEAKLYREF_STRUCT(...)  xatomic_weaklyref_struct< __VA_ARGS__ >
#define XATOMIC_WEAKLYREF(...)         xatomic_weaklyref<__VA_ARGS__>
#define xatomic_weaklyref_set(self, v) awref_set(&(self)->m_me, v)
#define xatomic_weaklyref_clear(self)  xatomic_weaklyref_set(self, __NULLPTR)
template<class T> struct xatomic_weaklyref_struct { AWREF(T) m_me; };

template<class T> struct xatomic_weaklyref {

#define XATOMIC_WEAKLYREF_INIT(p)        { AWREF_INIT(p) }
#define xatomic_weaklyref_init(self, p)  awref_init(&(self)->m_me, p)
#define xatomic_weaklyref_cinit(self, p) awref_cinit(&(self)->m_me, p)
	AWREF(T) m_me;

	__CXX_CLASSMEMBER NOBLOCK ATTR_LEAF void KCALL clear() __CXX_NOEXCEPT { awref_clear(&m_me); }
	__CXX_CLASSMEMBER NOBLOCK ATTR_LEAF WUNUSED bool KCALL is_nonnull() __CXX_NOEXCEPT { return awref_ptr(&m_me) != __NULLPTR; }
	__CXX_CLASSMEMBER NOBLOCK ATTR_LEAF WUNUSED REF T *KCALL get() __CXX_NOEXCEPT { return awref_get(&m_me); }
	__CXX_CLASSMEMBER NOBLOCK void KCALL set(T *new_pointer) __CXX_NOEXCEPT { awref_set(&m_me, new_pointer); }
	__CXX_CLASSMEMBER ATTR_LEAF WUNUSED NOBLOCK REF T *KCALL exchange(T *new_pointer) __CXX_NOEXCEPT { return awref_xch(&m_me, new_pointer); }
	__CXX_CLASSMEMBER NOBLOCK bool KCALL cmpxch(T *old_pointer, T *new_pointer) __CXX_NOEXCEPT { return awref_cmpxch(&m_me, old_pointer, new_pointer); }
};

} /* extern "c++" */
#else /* __cplusplus */

#define ATOMIC_REF(...)           struct { ARREF(__VA_ARGS__) m_me; }
#define atomic_ref_init(self, p)  arref_init(&(self)->m_me, p)
#define atomic_ref_cinit(self, p) arref_cinit(&(self)->m_me, p)
#define atomic_ref_fini(self)     arref_fini(&(self)->m_me)
#define XATOMIC_REF_STRUCT        ATOMIC_REF
#define XATOMIC_REF               ATOMIC_REF
#ifndef CONFIG_NO_SMP
#define xatomic_ref_init(self, p)  ((self)->m_pointer = (p), (self)->m_inuse = 0)
#define xatomic_ref_cinit(self, p) ((self)->m_pointer = (p), __hybrid_assert((self)->m_inuse == 0))
#define XATOMIC_REF_INIT(p)        { p, 0 }
#else /* !CONFIG_NO_SMP */
#define xatomic_ref_init(self, p)  ((self)->m_pointer = (p))
#define xatomic_ref_cinit(self, p) ((self)->m_pointer = (p))
#define XATOMIC_REF_INIT(p)        { p }
#endif /* CONFIG_NO_SMP */
#define xatomic_ref_fini(self)     xdecref((self)->m_pointer)

/* A weakly held reference (must be cleared by the associated object once that object gets destroyed) */
#define XATOMIC_WEAKLYREF          ATOMIC_REF
#define XATOMIC_WEAKLYREF_STRUCT   ATOMIC_REF
#ifndef CONFIG_NO_SMP
#define xatomic_weaklyref_init(self, p)  ((self)->m_pointer = (p), (self)->m_inuse = 0)
#define xatomic_weaklyref_cinit(self, p) ((self)->m_pointer = (p), __hybrid_assert((self)->m_inuse == 0))
#define XATOMIC_WEAKLYREF_INIT(p)        { p, 0 }
#else /* !CONFIG_NO_SMP */
#define xatomic_weaklyref_init(self, p)  ((self)->m_pointer = (p))
#define xatomic_weaklyref_cinit(self, p) ((self)->m_pointer = (p))
#define XATOMIC_WEAKLYREF_INIT(p)        { p }
#endif /* CONFIG_NO_SMP */

#endif /* !__cplusplus */

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_MISC_ATOMIC_REF_H */
