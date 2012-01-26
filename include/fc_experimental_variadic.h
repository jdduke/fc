/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2012, Jared Duke.
// This code is released under the MIT License.
// www.opensource.org/licenses/mit-license.php
/////////////////////////////////////////////////////////////////////////////

#ifndef _FC_EXPERIMENTAL_VARIADIC_H_
#define _FC_EXPERIMENTAL_VARIADIC_H_

#include "fc_experimental_variadic_utils.h"
#include "fc_variadic.h"

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
  inline R apply(Args args) {
    return f(apply_helper<arity_0>::apply<G0,Args,0      >(g, args),
             apply_helper<arity_1>::apply<G1,Args,arity_1>(g1,args));

    /*return f(apply_func<G0,Args,0,      arity_0        >(g,args),
      apply_func<G1,Args,arity_0,arity_0+arity_1>(g1,args));*/
  }

  template<typename... Args>
  auto operator()(Args... args) -> typename compound_result2<F,G0,G1,Args...>::type {
    return apply<typename compound_result2<F,G0,G1,Args...>::type>(std::make_tuple(args...));
  }

protected:

  explicit composed_base2(F f_,   G0   g_, G1   g1_) : composed_base(f_,g_), g1(g1_) { }
  explicit composed_base2(F&& f_, G0&& g_, G1&& g1_) : composed_base(f_,g_), g1(std:::move(g1_)) { }
  composed_base2();

  G1 g1;
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


#endif
