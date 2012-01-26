/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2012, Jared Duke.
// This code is released under the MIT License.
// www.opensource.org/licenses/mit-license.php
/////////////////////////////////////////////////////////////////////////////

#ifndef _FC_EXPERIMENTAL_H_
#define _FC_EXPERIMENTAL_H_

#if defined(FC_VARIADIC)
#include "fc_experimental_variadic.h"
#else

#include "fc_experimental_utils.h"

namespace fc {

///////////////////////////////////////////////////////////////////////////

template <typename F, typename G0, typename G1>
inline auto compose2(F f, G0 g0, G1 g1) -> typename composed_traits2<F,G0,G1>::type {
  return typename composed_traits2<F,G0,G1>::type(f, g0, g1);
}

///////////////////////////////////////////////////////////////////////////

template<typename F, typename G0, typename G1>
class composed_base2 : public composed_base<F,G0> {
public:
  typedef composed_base<F,G0> parent_type;

  enum {
    arity_0 = parent_type::arity,
    arity_1 = function_traits<G1>::arity,
    arity_c = arity_0 + arity_1
  };

  template<typename R, typename Args>
  R apply(const Args& args) {
    return f(apply_func<G0,Args,0,      arity_0        >(g,args),
             apply_func<G1,Args,arity_0,arity_0+arity_1>(g1,args));
  }

  template<typename T0>
  auto operator()(const T0& t) -> typename compound_result21<F,G0,G1,T0>::type {
    return apply<typename compound_result21<F,G0,G1,T0>::type>(std::forward_as_tuple(t));
  }

  template<typename T0, typename T1>
  auto operator()(const T0& t0, const T1& t1) -> typename compound_result22<F,G0,G1,T0,T1>::type {
    return apply< typename compound_result22<F,G0,G1,T0,T1>::type>(std::forward_as_tuple(t0,t1));
  }

  template<typename T0, typename T1, typename T2>
  auto operator()(const T0& t0, const T1& t1, const T2& t2) -> typename compound_result23<F,G0,G1,T0,T1,T2>::type {
    return apply<typename compound_result23<F,G0,G1,T0,T1,T2>::type >(std::forward_as_tuple(t0,t1,t2));
  }

  template<typename T0, typename T1, typename T2, typename T3>
  auto operator()(const T0& t0, const T1& t1, const T2& t2, const T3& t3) -> typename compound_result24<F,G0,G1,T0,T1,T2,T3>::type {
    auto tuple = std::make_tuple(t0,t1,t2,t3);
    //return apply(std::forward_as_tuple(t0,t1,t2,t3));
    return apply<typename compound_result24<F,G0,G1,T0,T1,T2,T3>::type>(tuple);
  }

protected:

  explicit composed_base2(F f_,   G0   g_, G1   g1_) : composed_base(f_,g_), g1(g1_) { }
  explicit composed_base2(F&& f_, G0&& g_, G1&& g1_) : composed_base(f_,g_), g1(std:::move(g1_)) { }
  composed_base2();

  G1 g1;
};

template<typename F, typename G0, typename G1, typename G2>
class composed_base3 : public composed_base2<F,G0,G1> {
public:
  typedef composed_base2<F,G0,G1> parent_type;
  enum {
    arity_0 = parent_type::arity_0,
    arity_1 = parent_type::arity_1,
    arity_2 = function_traits<G2>::arity,
    arity_c = parent_type::arity_c + arity_2;
  };

protected:

  explicit composed_base3(F f_,   G0   g_, G1   g1_, G2   g2_) : composed_base2(f_,g_,g1_), g2(g2_) { }
  explicit composed_base3(F&& f_, G0&& g_, G1&& g1_, G1&& g2_) : composed_base2(f_,g_,g1_), g2(std:::move(g2_)) { }
  composed_base3();

  G2 g2;
};

///////////////////////////////////////////////////////////////////////////

template<typename F, typename G0, typename G1, size_t ArgGC>
class composed2 : public composed_base2<F,G0,G1> {
public:
  composed2(F f_,   G0   g_, G1   g1_) : composed_base2<F,G0,G1>(f_,g_,g1_) { }
  composed2(F&& f_, G0&& g_, G1&& g1_) : composed_base2<F,G0,G1>(std::forward(f_),std::forward(g_), ,std::forward(g1_)) { }
};

template<typename F, typename G0, typename G1>
class composed2<F,G0,G1,0> : public composed_base2<F,G0,G1> {
public:
  composed2(F f_,   G0   g_, G1   g1_) : composed_base2<F,G0,G1>(f_,g_,g1_) { }
  composed2(F&& f_, G0&& g_, G1&& g1_) : composed_base2<F,G0,G1>(std::forward(f_),std::forward(g_), ,std::forward(g1_)) { }

  auto operator()() -> typename compound_result20<F,G0,G1>::type { return f(g(),g1()); }
};

}

#endif /* FC_VARIADIC */

#endif
