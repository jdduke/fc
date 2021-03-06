/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2012, Jared Duke.
// This code is released under the MIT License.
// www.opensource.org/licenses/mit-license.php
/////////////////////////////////////////////////////////////////////////////

#ifndef _FC_BASE_H_
#define _FC_BASE_H_

#include "fc_common.h"
#include "fc_utils.h"

namespace fc {

///////////////////////////////////////////////////////////////////////////

template <typename F, typename G>
inline auto compose(F f, G g) -> typename composed_traits<F,G>::type {
  return typename composed_traits<F,G>::type(f, g);
}

#if FC_PLUS_OPERATOR
// Example: (f + g)(Args) == (compose(f,g)(Args)
template<typename F, typename G>
inline auto operator+(F f, G g) -> typename composed_traits<F,G>::type {
  return compose(f,g);
}
#endif

#if FC_DOT_OPERATOR
// Example: (f <o> g)(Args) == (compose(f,g)(args))
static class compose_dot_helper { } o;
template<typename F, typename G>
inline auto operator>(F f, G g) -> typename composed_traits<F,G>::type {
	return compose(f,g);
}
template<typename F>
inline F operator<(F f, compose_dot_helper) {
	return f;
}
#endif

#if FC_AND_OPERATOR
// Example: (f & g)(Args) == (compose(f,g)(args))
template<typename F, typename G>
inline auto operator&(F f, G g) -> typename composed_traits<F,G>::type {
	return compose(f,g);
}
#endif

///////////////////////////////////////////////////////////////////////////

template<typename F, typename G>
class composed_base {
public:
  static const size_t arity   = function_traits<G>::arity;
  static const size_t f_arity = function_traits<F>::arity;

  template< typename G2 >
  auto with(G2 g2) const -> typename composed_traits< typename composed_traits<F,G>::type, G2>::type {
    return compose(compose(f,g), g2);
  }

#if defined(VC_VARIADIC)
  template<typename... Args>
  auto operator()(Args... args) -> typename compound_result<F,G,Args...>::type {
    return f(g(args...));
  }
#else

  template<typename T0>
  auto operator()(const T0& t) -> typename compound_result1<F,f_arity,G,T0>::type {
    return compound_result1<F,f_arity,G,T0>::apply(f,g,t);
  }

  template<typename T0, typename T1>
  auto operator()(const T0& t0, const T1& t1) -> typename compound_result2<F,f_arity,G,T0,T1>::type {
    return compound_result2<F,f_arity,G,T0,T1>::apply(f,g,t0,t1);
  }

  template<typename T0, typename T1, typename T2>
  auto operator()(const T0& t0, const T1& t1, const T2& t2) -> typename compound_result3<F,f_arity,G,T0,T1,T2>::type {
    return compound_result3<F,f_arity,G,T0,T1,T2>::apply(f,g,t0,t1,t2);
  }

  template<typename T0, typename T1, typename T2, typename T3>
  auto operator()(const T0& t0, const T1& t1, const T2& t2, const T3& t3) -> typename compound_result4<F,f_arity,G,T0,T1,T2,T3>::type {
    return compound_result4<F,f_arity,G,T0,T1,T2,T3>::apply(f,g,t0,t1,t2,t3);
  }
#endif

protected:

  explicit composed_base(F f_,   G g_)   : f(f_), g(g_) { }
  explicit composed_base(F&& f_, G&& g_) : f(std::move(f_)), g(std::move(g_)) { }
  composed_base();

  F f;
  G g;
};

///////////////////////////////////////////////////////////////////////////

template<typename F, typename G, size_t ArgFC, size_t ArgGC>
class composed : public composed_base<F,G> {
public:
  composed(F f_,   G g_)   : composed_base<F,G>(f_,g_) { }
  composed(F&& f_, G&& g_) : composed_base<F,G>(std::forward(f_),std::forward(g_)) { }
};

template<typename F, typename G, size_t ArgFC>
class composed<F,G,ArgFC,0> : public composed_base<F,G> {
public:
  composed(F f_,   G g_)   : composed_base<F,G>(f_,g_) { }
  composed(F&& f_, G&& g_) : composed_base<F,G>(std::forward(f_),std::forward(g_)) { }

  auto operator()() -> typename compound_result0<F,ArgFC,G>::type { return f(g()); }
};

template<typename F, typename G>
class composed<F,G,0,0> : public composed_base<F,G> {
public:
  composed(F f_,   G g_)   : composed_base<F,G>(f_,g_) { }
  composed(F&& f_, G&& g_) : composed_base<F,G>(std::forward(f_),std::forward(g_)) { }

  auto operator()() -> typename result0<F>::type { g(); return f(); }
};

} /* namespace fc */

#endif /* _FC_BASE_H_ */
