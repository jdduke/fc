/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2012, Jared Duke.
// This code is released under the MIT License.
// www.opensource.org/licenses/mit-license.php
/////////////////////////////////////////////////////////////////////////////

#ifndef _FC_EXPERIMENTAL_UTILS_H_
#define _FC_EXPERIMENTAL_UTILS_H_

#include <tuple>

#include "fc_common.h"
#include "fc_utils.h"

namespace fc {

template<typename F, typename G0, typename G1>               class composed_base2;
template<typename F, typename G0, typename G1, size_t ArgGC> class composed2;

template<typename F, typename G0, typename G1, typename G2>               class composed_base3;
template<typename F, typename G0, typename G1, typename G2, size_t ArgGC> class composed3;

///////////////////////////////////////////////////////////////////////////

/*
template <typename F, typename G0, typename G1, size_t ArgGC>
struct function_traits< composed2<F,G0,G1,ArgGC> > {
  static const size_t arity = function_traits<G0>::arity + function_traits<G1>::arity;
};
*/

template< size_t arg_c >
struct apply_helper {

  template<typename F, typename tuple_type, size_t arg_0> struct tuple_traits {
    typedef typename result0<F>::type type;
  };

  template< typename F, typename Args, size_t arg_0 >
  static auto apply( F& f, const Args& args ) -> typename tuple_traits<F,Args,arg_0>::type {
    return f();
  }
};

template<>
struct apply_helper<1> {
  template<typename F, typename tuple_type, size_t arg_0> struct tuple_traits {
    typedef typename function_traits<F>::result_type type;
  };

  template< typename F, typename Args, size_t arg_0 >
  static auto apply( F& f, const Args& args ) -> typename tuple_traits<F,Args,arg_0>::type {
    return f( std::get<arg_0>(args) );
  }
};

template<>
struct apply_helper<2> {
  template<typename F, typename tuple_type, size_t arg_0> struct tuple_traits {
    typedef typename function_traits<F>::result_type type;
  };

  template< typename F, typename Args, size_t arg_0 >
  static auto apply( F& f, const Args& args ) -> typename tuple_traits<F,Args,arg_0>::type {
    return f( std::get<arg_0>(args), std::get<arg_0+1>(args) );
  }
};

template<>
struct apply_helper<3> {
  template<typename F, typename tuple_type, size_t arg_0> struct tuple_traits {
    typedef typename function_traits<F>::result_type type;
  };

  template< typename F, typename Args, size_t arg_0 >
  static auto apply( F& f, const Args& args ) -> typename tuple_traits<F,Args,arg_0>::type {
    return f( std::get<arg_0>(args), std::get<arg_0+1>(args), std::get<arg_0+2>(args) );
  }
};

template<>
struct apply_helper<4> {
  template<typename F, typename tuple_type, size_t arg_0> struct tuple_traits {
    typedef typename function_traits<F>::result_type type;
  };

  template< typename F, typename Args, size_t arg_0 >
  static auto apply( F& f, const Args& args ) -> typename tuple_traits<F,Args,arg_0>::type {
    return f( std::get<arg_0>(args), std::get<arg_0+1>(args), std::get<arg_0+2>(args), std::get<arg_0+3>(args) );
  }
};

template<>
struct apply_helper<5> {
  template<typename F, typename tuple_type, size_t arg_0> struct tuple_traits {
    typedef typename function_traits<F>::result_type type;
  };

  template< typename F, typename Args, size_t arg_0 >
  static auto apply( F& f, const Args& args ) -> typename tuple_traits<F,Args,arg_0>::type {
    return f( std::get<arg_0>(args), std::get<arg_0+1>(args), std::get<arg_0+2>(args), std::get<arg_0+3>(args), std::get<arg_0+4>(args) );
  }
};

template< typename F, typename Args, size_t arg_0, size_t arg_c >
auto apply_func( F& f, const Args& args) -> typename apply_helper<arg_c>::tuple_traits<F,Args,arg_0>::type {
  return apply_helper<arg_c>::apply<F,Args,arg_0>(f, args);
}

template< typename R, typename F, typename Args, size_t arg_0, size_t arg_c >
R apply_func2( F& f, const Args& args) {
  return apply_helper<arg_c>::apply<F,Args,arg_0>(f, args);
}

///////////////////////////////////////////////////////////////////////////

template<typename F, typename G0, typename G1>
struct composed_traits2 {
  typedef composed2<F,G0,G1,function_traits2<F,G0,G1>::arity> type;
};

///////////////////////////////////////////////////////////////////////////

template<typename F, typename G0, typename G1, typename tuple_type>
struct compound_result2_helper {
  typedef typename function_traits<G0>::result_type U;
  typedef typename function_traits<G1>::result_type V;
  typedef typename result2<F,U,V>::type type;
};

///////////////////////////////////////////////////////////////////////////

template<typename F, typename G0, typename G1>
struct compound_result20 {
  typedef void tuple_type;
  typedef typename compound_result2_helper<F,G0,G1,tuple_type>::type type;
};

#if defined(FC_VARIADIC)

template<typename F, typename G0, typename G1, typename... Args>
struct compound_result2 {
  typedef std::tuple<Args...> tuple_type;
  typedef typename compound_result2_helper<F,G0,G1,tuple_type>::type type;
};

#else

template<typename F, typename G0, typename G1, typename T0>
struct compound_result21 {
  typedef std::tuple<T0> tuple_type;
  typedef typename compound_result2_helper<F,G0,G1,tuple_type>::type type;
};

template<typename F, typename G0, typename G1, typename T0, typename T1>
struct compound_result22 {
  typedef std::tuple<T0,T1> tuple_type;
  typedef typename compound_result2_helper<F,G0,G1,tuple_type>::type type;
};

template<typename F, typename G0, typename G1, typename T0, typename T1, typename T2>
struct compound_result23 {
  typedef std::tuple<T0,T1,T2> tuple_type;
  typedef typename compound_result2_helper<F,G0,G1,tuple_type>::type type;
};

template<typename F, typename G0, typename G1, typename T0, typename T1, typename T2, typename T3>
struct compound_result24 {
  typedef std::tuple<T0,T1,T2,T3> tuple_type;
  typedef typename compound_result2_helper<F,G0,G1,tuple_type>::type type;
};

#endif

///////////////////////////////////////////////////////////////////////////

template<typename F, typename G0, typename G1, typename G2>
struct composed_traits3 {
  typedef composed3<F,G0,G1,G2,function_traits3<F,G0,G1,G2>::arity> type;
};

///////////////////////////////////////////////////////////////////////////

template<typename F, typename G0, typename G1, typename G2, typename tuple_type>
struct compound_result3_helper {
  typedef typename function_traits<G0>::result_type U;
  typedef typename function_traits<G1>::result_type V;
  typedef typename function_traits<G0>::result_type W;
  typedef typename result3<F,U,V,W>::type type;
};

template<typename F, typename G0, typename G1, typename G2>
struct compound_result30 {
  typedef void tuple_type;
  typedef typename compound_result3_helper<F,G0,G1,G2,tuple_type>::type type;
};

#if defined(FC_VARIADIC)

template<typename F, typename G0, typename G1, typename G2, typename... Args>
struct compound_result3 {
  typedef std::tuple<Args...> tuple_type;
  typedef typename compound_result3_helper<F,G0,G1,G2,tuple_type>::type type;
};

#else

template<typename F, typename G0, typename G1, typename G2, typename T0>
struct compound_result31 {
  typedef std::tuple<T0> tuple_type;
  typedef typename compound_result3_helper<F,G0,G1,G2,tuple_type>::type type;
};

template<typename F, typename G0, typename G1, typename G2, typename T0, typename T1>
struct compound_result32 {
  typedef std::tuple<T0,T1> tuple_type;
  typedef typename compound_result3_helper<F,G0,G1,G2,tuple_type>::type type;
};

template<typename F, typename G0, typename G1, typename G2,  typename T0, typename T1, typename T2>
struct compound_result33 {
  typedef std::tuple<T0,T1,T2> tuple_type;
  typedef typename compound_result3_helper<F,G0,G1,G2,tuple_type>::type type;
};

template<typename F, typename G0, typename G1, typename G2, typename T0, typename T1, typename T2, typename T3>
struct compound_result34 {
  typedef std::tuple<T0,T1,T2,T3> tuple_type;
  typedef typename compound_result3_helper<F,G0,G1,G2,tuple_type>::type type;
};

#endif

///////////////////////////////////////////////////////////////////////////

#if 0
#define COMMA ,

#define DEFINE_RESULT_HELPER_FUNC(argc0, argc1, typenames0, typenames1, types, tuple)    \
  template<typename F, typenames0 typenames1>                                            \
struct compund_result ## argc0 ## argc {                                               \
  typedef tuple tuple_type;                                                            \
  typedef typename compound_result_ ## arg0 ## _helper<F,types,tuple_type>::type type; \
};

#define DEFINE_RESULT_HELPER(argc, typenames, types) \
  DEFINE_RESULT_HELPER_FUNC(argc, 0, typenames,              , types, void) \
  DEFINE_RESULT_HELPER_FUNC(argc, 1, typenames, COMMA types, std::tuple<T0>) \
  DEFINE_RESULT_HELPER_FUNC(argc, 2, typenames, types, std::tuple<T0>) \
  DEFINE_RESULT_HELPER_FUNC(argc, 3, typenames, types, ) \
  DEFINE_RESULT_HELPER_FUNC(argc, 4, typenames, types, )
#endif

} /* namespace fc */

#endif /* _FC_EXPERIMENTAL_UTILS_H_ */
