/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2012, Jared Duke.
// This code is released under the MIT License.
// www.opensource.org/licenses/mit-license.php
/////////////////////////////////////////////////////////////////////////////

#ifndef _FC_VARIADIC_H_
#define _FC_VARIADIC_H_

#include <functional>
#include <type_traits>

#if defined(FC_EXPERIMENTAL)
#include "fc_experimental.h"
#endif

#include "fc_variadic_utils.h"

namespace fc {

///////////////////////////////////////////////////////////////////////////

template <typename F, typename G>
inline auto compose(F f, G g) -> typename composed_traits<F,G>::type {
  return typename composed_traits<F,G>::type(f, g);
}

template<typename F, typename G>
inline auto operator+(F f, G g) -> typename composed_traits<F,G>::type {
  return compose(f,g);
}

///////////////////////////////////////////////////////////////////////////

template<typename F, typename G>
class composed_base {
public:
  enum {
    arity = function_traits<G>::arity
  };

  template< typename G2 >
  auto with(G2 g2) const -> typename composed_traits< typename composed_traits<F,G>::type, G2>::type {
    return compose(compose(f,g), g2);
  }

  template<typename... Args>
  auto operator()(Args... args) -> typename compound_result<F,G,Args...>::type {
    return f(g(args...));
  }

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

  auto operator()() -> typename compound_result<F,G>::type { return f(g()); }
};

}

#endif /* FC_H */
