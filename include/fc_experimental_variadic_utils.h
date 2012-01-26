/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2012, Jared Duke.
// This code is released under the MIT License.
// www.opensource.org/licenses/mit-license.php
/////////////////////////////////////////////////////////////////////////////

#ifndef _FC_EXPERIMENTAL_VARIADIC_UTILS_H_
#define _FC_EXPERIMENTAL_VARIADIC_UTILS_H_

#include <tuple>

#include "fc_variadic_utils.h"

namespace fc {

template<typename F, typename G0, typename G1>               class composed_base2;
template<typename F, typename G0, typename G1, size_t ArgGC> class composed2;

///////////////////////////////////////////////////////////////////////////

template<size_t arg_c, typename F, typename tuple_type, size_t arg_0>
struct tuple_traits { };

template<typename F, typename tuple_type, size_t arg_0>
struct tuple_traits<0,F,tuple_type,arg_0> {
  typedef typename std::result_of<F()>::type type;
};

template<typename F, typename tuple_type, size_t arg_0>
struct tuple_traits<1,F,tuple_type,arg_0> {
  typedef typename std::result_of<
  F( typename std::tuple_element<arg_0, tuple_type>::type )
  > type;
};

template<typename F, typename tuple_type, size_t arg_0>
struct tuple_traits<2,F,tuple_type,arg_0> {
  typedef typename std::result_of<
  F(typename std::tuple_element<arg_0,   tuple_type>::type,
    typename std::tuple_element<arg_0+1, tuple_type>::type)>::type type;
};

template<typename F, typename tuple_type, size_t arg_0>
struct tuple_traits<3,F,tuple_type,arg_0> {
  typedef typename std::result_of<
  F(typename std::tuple_element<arg_0,   tuple_type>::type,
    typename std::tuple_element<arg_0+1, tuple_type>::type,
    typename std::tuple_element<arg_0+2, tuple_type>::type)>::type type;
};

template<typename F, typename tuple_type, size_t arg_0>
struct tuple_traits<4,F,tuple_type,arg_0> {
  typedef typename std::result_of<
  F(typename std::tuple_element<arg_0,   tuple_type>::type,
    typename std::tuple_element<arg_0+1, tuple_type>::type,
    typename std::tuple_element<arg_0+2, tuple_type>::type,
    typename std::tuple_element<arg_0+3, tuple_type>::type)>::type type;
};

template<typename F, typename tuple_type, size_t arg_0>
struct tuple_traits<5,F,tuple_type,arg_0> {
  typedef typename std::result_of<
  F(typename std::tuple_element<arg_0,   tuple_type>::type,
    typename std::tuple_element<arg_0+1, tuple_type>::type,
    typename std::tuple_element<arg_0+2, tuple_type>::type,
    typename std::tuple_element<arg_0+3, tuple_type>::type,
    typename std::tuple_element<arg_0+4, tuple_type>::type)>::type type;
};

///////////////////////////////////////////////////////////////////////////

template< size_t arg_c >
struct apply_helper { };

template<> struct apply_helper<0> {
  template< typename F, typename Args, size_t arg_0 >
  static auto apply( F& f, Args& args ) -> typename tuple_traits<0,F,Args,arg_0>::type {
    return f();
  }
};

template<> struct apply_helper<1> {
  template< typename F, typename Args, size_t arg_0 >
  static auto apply( F& f, Args& args ) -> typename tuple_traits<1,F,Args,arg_0>::type {
    return f( std::get<arg_0>(args) );
  }
};

template<> struct apply_helper<2> {
  template< typename F, typename Args, size_t arg_0 >
  static auto apply( F& f, Args& args ) -> typename tuple_traits<2,F,Args,arg_0>::type {
    return f( std::get<arg_0>(args), std::get<arg_0+1>(args) );
  }
};

template<> struct apply_helper<3> {
  template< typename F, typename Args, size_t arg_0 >
  static auto apply( F& f, Args& args ) -> typename tuple_traits<3,F,Args,arg_0>::type {
    return f( std::get<arg_0>(args), std::get<arg_0+1>(args), std::get<arg_0+2>(args) );
  }
};

template<> struct apply_helper<4> {
  template< typename F, typename Args, size_t arg_0 >
  static auto apply( F& f, Args& args ) -> typename tuple_traits<4,F,Args,arg_0>::type {
    return f( std::get<arg_0>(args), std::get<arg_0+1>(args), std::get<arg_0+2>(args), std::get<arg_0+3>(args) );
  }
};

template<> struct apply_helper<5> {
  template< typename F, typename Args, size_t arg_0 >
  static auto apply( F& f, Args& args ) -> typename tuple_traits<5,F,Args,arg_0>::type {
    return f( std::get<arg_0>(args), std::get<arg_0+1>(args), std::get<arg_0+2>(args), std::get<arg_0+3>(args), std::get<arg_0+4>(args) );
  }
};

///////////////////////////////////////////////////////////////////////////

/*
template< typename F, typename Args, size_t arg_0, size_t arg_c >
auto apply_func( F& f, Args& args) -> typename tuple_traits<arg_c,F,Args,arg_0>::type {
  //return apply_helper<arg_c>::apply<F,Args,arg_0>(f, args);
  return apply_helper<arg_c>().apply<F,Args,arg_0>(f, args);
}
*/
///////////////////////////////////////////////////////////////////////////

template<typename F, typename G0, typename G1>
struct composed_traits2 {
  typedef composed2<F,G0,G1,function_traits2<G0,G1>::arity> type;
};

///////////////////////////////////////////////////////////////////////////

template<typename F, typename G0, typename G1, typename tuple_type>
struct compound_result2_helper {
  enum {
    arity0 = function_traits<G0>::arity,
    arity1 = function_traits<G1>::arity
  };
  typedef typename tuple_traits<arity0,G0,tuple_type,0>::type      U;
  typedef typename tuple_traits<arity1,G1,tuple_type,arity0>::type V;
  typedef typename results<F,U,V>::type type;
};

///////////////////////////////////////////////////////////////////////////

template<typename F, typename G0, typename G1>
struct compound_result20 {
  typedef void tuple_type;
  typedef typename compound_result2_helper<F,G0,G1,tuple_type>::type type;
};

template<typename F, typename G0, typename G1, typename... Args>
struct compound_result2 {
  typedef std::tuple<Args...> tuple_type;
  typedef typename compound_result2_helper<F,G0,G1,tuple_type>::type type;
};

}

#endif
