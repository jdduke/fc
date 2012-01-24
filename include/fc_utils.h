/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2012, Jared Duke.
// This code is released under the MIT License.
// www.opensource.org/licenses/mit-license.php
/////////////////////////////////////////////////////////////////////////////

#ifndef _FC_UTILS_H_
#define _FC_UTILS_H_

#include <functional>
#include <type_traits>

namespace fc {

///////////////////////////////////////////////////////////////////////////

template<typename F, typename G>              class composed_base;
template<typename F, typename G, size_t ArgFC, size_t ArgGC> class composed;

///////////////////////////////////////////////////////////////////////////

template <typename T>
typename std::add_rvalue_reference<T>::type declval();

///////////////////////////////////////////////////////////////////////////

template <typename T> struct function_traits;

/*template <typename T, bool isFunction>
struct function_traits_helper : public function_traits< decltype( &T::operator() ) > {};

template <typename T>
struct function_traits_helper<T, true> : public function_traits< decltype( &T() ) > {};*/

#if 0
template <typename T>
struct function_traits : public function_traits_helper< T, typename std::is_pointer<T>::value > {};
#else
template <typename T>
struct function_traits : public function_traits< decltype( &T::operator() ) > {};
#endif

template <typename F, typename G, size_t ArgFC, size_t ArgGC>
struct function_traits< composed<F,G,ArgFC,ArgGC> > : public function_traits<G> {};

template <typename C, typename R>
struct function_traits<R(C::*)() const> { 
	enum { arity = 0 };
	typedef decltype( declval<C>().operator()() ) result_type;
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

///////////////////////////////////////////////////////////////////////////

template<typename F>
struct result0 { typedef decltype( declval<F>().operator()() ) type; };

template<typename F, typename T0>
struct result1 { typedef decltype( declval<F>().operator()(declval<T0>()) ) type; };

template<typename F, typename T0, typename T1>
struct result2 { typedef decltype( declval<F>().operator()(declval<T0>(), declval<T1>()) ) type; };

template<typename F, typename T0, typename T1, typename T2>
struct result3 { typedef decltype( declval<F>().operator()(declval<T0>(), declval<T1>(), declval<T2>()) ) type; };

template<typename F, typename T0, typename T1, typename T2, typename T3>
struct result4 { typedef decltype( declval<F>().operator()(declval<T0>(), declval<T1>(), declval<T2>(), declval<T3>()) ) type; };

///////////////////////////////////////////////////////////////////////////

template<typename F, typename G>
struct compound_result0 {
  typedef typename result0<G>::type U;
  typedef typename result1<F,U>::type type;
};

template<typename F, typename G, typename T0>
struct compound_result1 {
  typedef typename result1<G,T0>::type U;
  typedef typename result1<F,U>::type type;
};

template<typename F, typename G, typename T0, typename T1>
struct compound_result2 {	
  typedef typename result2<G,T0,T1>::type U;
  typedef typename result1<F,U>::type type;
};

template<typename F, typename G, typename T0, typename T1, typename T2>
struct compound_result3 {	
  typedef typename result3<G,T0,T1,T2>::type U;
  typedef typename result1<F,U>::type type;
};

///////////////////////////////////////////////////////////////////////////

template<typename Functor, size_t NArgs, typename Return>
struct enable_if_arg : std::enable_if<function_traits<Functor>::arity==NArgs, Return> { };

///////////////////////////////////////////////////////////////////////////

template<typename F, typename G0 = std::function<void(void)>, typename G1 = G0, typename G2 = G0>
struct arg_count {
	enum { arity = function_traits<F>::arity + function_traits<G0>::arity + function_traits<G1>::arity + function_traits<G2>::arity };
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