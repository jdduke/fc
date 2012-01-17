/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2012, Jared Duke.
// This code is released under the MIT License.
// www.opensource.org/licenses/mit-license.php
/////////////////////////////////////////////////////////////////////////////

#ifndef _FC_H_
#define _FC_H_

#include <functional>
#include <type_traits>

namespace fc {

///////////////////////////////////////////////////////////////////////////

template<typename F, typename G>              class composed_base;
template<typename F, typename G, size_t ArgC> class composed;

///////////////////////////////////////////////////////////////////////////

template <typename T>
typename std::add_rvalue_reference<T>::type declval();

///////////////////////////////////////////////////////////////////////////

template <typename T>
struct function_traits : public function_traits< decltype( &T::operator() ) > {};

template <typename F, typename G, size_t ArgC>
struct function_traits< composed<F,G,ArgC> > : public function_traits<G> {};

template <typename C, typename R, typename T0>
struct function_traits<R(C::*)(T0) const> { enum { arity = 1 }; };

template <typename C, typename R, typename T0, typename T1>
struct function_traits<R(C::*)(T0,T1) const> { enum { arity = 2 }; };

template <typename C, typename R, typename T0, typename T1, typename T2>
struct function_traits<R(C::*)(T0,T1,T2) const> { enum { arity = 3 }; };

template <typename R, typename T0>
struct function_traits<std::function<R(T0)> > { enum { arity = 1 }; };

template <typename R, typename T0, typename T1>
struct function_traits<std::function<R(T0,T1)> > { enum { arity = 2 }; };

template <typename R, typename T0, typename T1, typename T2>
struct function_traits<std::function<R(T0,T1,T2)> > { enum { arity = 3 }; };

template<typename Functor, size_t NArgs, typename Return>
struct count_arg : std::enable_if<function_traits<Functor>::arity==NArgs, Return>
{};

///////////////////////////////////////////////////////////////////////////

template<typename F, typename G>
struct composed_traits {
  typedef composed<F,G,function_traits<G>::arity> type;
};

///////////////////////////////////////////////////////////////////////////
// 

template <typename F, typename G>
inline auto compose(F f, G g) -> typename composed_traits<F,G>::type {
  return typename composed_traits<F,G>::type(f, g);
}

template<typename F, typename G1, typename G2>
inline auto compose(F f, G1 g1, G2 g2) -> decltype( compose(compose(f,g1),g2) ) {
  return compose(compose(f, g1), g2);
}

template<typename F, typename G1, typename G2, typename G3>
inline auto compose(F f, G1 g1, G2 g2, G3 g3) -> decltype( compose(compose(f,g1,g2),g3) ) {
  return compose(compose(f,g1,g2),g4);
}

template<typename F, typename G1, typename G2, typename G3, typename G4>
inline auto compose(F f, G1 g1, G2 g2, G3 g3, G4 g4) -> decltype( compose(compose(f,g1,g2,g3),g4) ) {
  return compose(compose(f,g1,g2,g3),g4);
}

template<typename F, typename G1, typename G2, typename G3, typename G4, typename G5>
inline auto compose(F f, G1 g1, G2 g2, G3 g3, G4 g4, G5 g5) -> decltype( compose(compose(f,g1,g2,g3,g4),g5) ) {
  return compose(compose(f,g1,g2,g3,g4),g5);
}

template<typename F, typename G>
inline auto operator+(F f, G g) -> typename composed_traits<F,G>::type {
  return compose(f,g);
}

///////////////////////////////////////////////////////////////////////////

template<typename F, typename G>
class composed_base {
public:

  template< typename G2 >
  auto with(G2 g2) const -> typename composed_traits< typename composed_traits<F,G>::type, G2>::type {
    return compose(compose(f,g), g2);
  }

  template< typename G2 >
  auto operator+(G2 g2) -> decltype( this->compose(g2) ) {
    return with(g2);
  }

protected:

  explicit composed_base(F f_,   G g_)   : f(f_), g(g_) { }
  explicit composed_base(F&& f_, G&& g_) : f(std::move(f_)), g(std::move(g_)) { }
  composed_base();

  F f;
  G g;
};

///////////////////////////////////////////////////////////////////////////

template<typename F, typename G, size_t ArgC>
class composed : public composed_base<F,G> {
  template<typename F, typename G>
  struct result
  {
    typedef decltype( declval<G>().operator()() ) U;
    typedef decltype( declval<F>().operator()(declval<U>()) ) type;
  };

public:
  composed(F f_,   G g_)   : composed_base<F,G>(f_,g_) { }
  composed(F&& f_, G&& g_) : composed_base<F,G>(std::forward(f_),std::forward(g_)) { }

  auto operator()() -> typename result<F,G>::type { return f(g()); }
};

///////////////////////////////////////////////////////////////////////////

template<typename F, typename G>
class composed<F,G,1> : public composed_base<F,G> {
  template<typename F, typename G, typename T1>
  struct result
  {
    typedef decltype( declval<G>().operator()(declval<T1>()) ) U;
    typedef decltype( declval<F>().operator()(declval<U>()) ) type;
  };

public:
  explicit composed(F f_,   G g_)   : composed_base<F,G>(f_,g_) { }
  explicit composed(F&& f_, G&& g_) : composed_base<F,G>(std::forward(f_),std::forward(g_)) { }

  template<typename T1>
  auto operator()(const T1& t) -> typename result<F,G,T1>::type {
    return f(g(t));
  }
};

///////////////////////////////////////////////////////////////////////////

template<typename F, typename G>
class composed<F,G,2> : public composed_base<F,G> {
  template<typename F, typename G, typename T1, typename T2>
  struct result
  {
    typedef decltype( declval<G>().operator()(declval<T1>(), declval<T2>()) ) U;
    typedef decltype( declval<F>().operator()(declval<U>()) ) type;
  };

public:
  explicit composed(F f_,   G g_)   : composed_base<F,G>(f_,g_) { }
  explicit composed(F&& f_, G&& g_) : composed_base<F,G>(std::forward(f_),std::forward(g_)) { }

  template<typename T1, typename T2>
  auto operator()(const T1& t1, const T2& t2) -> typename result<F,G,T1,T2>::type {
    return f(g(t1,t2));
  }
};

///////////////////////////////////////////////////////////////////////////

template<typename F, typename G>
class composed<F,G,3> : public composed_base<F,G> {
  template<typename F, typename G, typename T1, typename T2, typename T3>
  struct result
  {
    typedef decltype( declval<G>().operator()(declval<T1>(), declval<T2>(), declval<T3>()) ) U;
    typedef decltype( declval<F>().operator()(declval<U>()) ) type;
  };

public:
  explicit composed(F f_,   G g_)   : composed_base<F,G>(f_,g_) { }
  explicit composed(F&& f_, G&& g_) : composed_base<F,G>(std::forward(f_),std::forward(g_)) { }

  template<typename T1, typename T2, typename T3>
  auto operator()(const T1& t1, const T2& t2, const T3& t3) -> typename result<F,G,T1,T2,T3>::type {
    return f(g(t1,t2,t3));
  }
};

///////////////////////////////////////////////////////////////////////////

}


#endif