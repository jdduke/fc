/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2012, Jared Duke.
// This code is released under the MIT License.
// www.opensource.org/licenses/mit-license.php
/////////////////////////////////////////////////////////////////////////////

#ifndef _FC_VARIADIC_UTILS_H_
#define _FC_VARIADIC_UTILS_H_

#include <functional>
#include <type_traits>

namespace fc {

///////////////////////////////////////////////////////////////////////////

template<typename F, typename G>              class composed_base;
template<typename F, typename G, size_t ArgFC, size_t ArgGC> class composed;

///////////////////////////////////////////////////////////////////////////

#if defined(_WIN32)
namespace std {
  template <typename T>
  typename std::add_rvalue_reference<T>::type declval();
}
#endif

///////////////////////////////////////////////////////////////////////////

#if 1

template <typename T> struct function_traits;
template <typename T0, typename T1> struct function_traits2;

///////////////////////////////////////////////////////////////////////////

template <typename T>
struct function_traits : public function_traits< decltype( &T::operator() ) > {};

template <typename T0, typename T1>
struct function_traits2 {
  enum { arity = function_traits< decltype( &T0::operator() ) >::arity
               + function_traits< decltype( &T1::operator() ) >::arity };
};

template <typename F, typename G, size_t ArgFC, size_t ArgGC>
struct function_traits< composed<F,G,ArgFC,ArgGC> > : public function_traits<G> {};

///////////////////////////////////////////////////////////////////////////

template <typename C, typename R>
struct function_traits<R(C::*)() const> {
	enum { arity = 0 };
	typedef decltype( std::declval<C>().operator()() ) result_type;
};

template <typename C, typename R, typename T0>
struct function_traits<R(C::*)(T0) const> {
	enum { arity = 1 };
	typedef R result_type;
};

template <typename C, typename R, typename T0, typename T1>
struct function_traits<R(C::*)(T0,T1) const> {
	enum { arity = 2 };
	typedef R result_type;
};

template <typename C, typename R, typename T0, typename T1, typename T2>
struct function_traits<R(C::*)(T0,T1,T2) const> {
	enum { arity = 3 };
	typedef R result_type;
};

template <typename C, typename R, typename T0, typename T1, typename T2, typename T3>
struct function_traits<R(C::*)(T0,T1,T2,T3) const> {
	enum { arity = 4 };
	typedef R result_type;
};

#else

template <typename T>
struct function_traits : public function_traits<decltype(&T::operator())> {};

template <typename C, typename R, typename... Args>
struct function_traits<R(C::*)(Args...) const> {
  enum { arity = sizeof...(Args) };
  typedef R result_type;
};

#endif

///////////////////////////////////////////////////////////////////////////

template<typename... Args>
struct results;

template<typename F, typename... Args>
struct results<F,Args...> {
  typedef typename std::result_of< F(Args...) >::type type;
};

///////////////////////////////////////////////////////////////////////////

template<typename F, typename G, typename... Args>
struct compound_result {
  typedef typename results<G,Args...>::type U;
  typedef typename results<F,U>::type type;
};

///////////////////////////////////////////////////////////////////////////

template<typename F, typename G>
struct composed_traits {
  typedef composed<F,G,function_traits<F>::arity,function_traits<G>::arity> type;
};

///////////////////////////////////////////////////////////////////////////

template <typename T>
struct make_function_traits {
  typedef std::function<typename std::enable_if<std::is_function<T>::value, T>::type> type;
};

template<typename T>
auto make_function(T *t) -> typename make_function_traits<T>::type {
  return t;
}

}

#endif
