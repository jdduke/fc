/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2012, Jared Duke.
// This code is released under the MIT License.
// www.opensource.org/licenses/mit-license.php
/////////////////////////////////////////////////////////////////////////////

#ifndef _FC_APPLY_UTILS_H_
#define _FC_APPLY_UTILS_H_

#include <functional>
#include <type_traits>

#include "fc_utils.h"

namespace fc {

#define apply_helper_create(a,b)

template< size_t arg_c >
struct apply_helper {
  template< typename F, typename Args, size_t arg_0 >
  static auto apply( F& f, Args& args ) -> typename result0<F>::type {
    return f();
  }
};

template<>
struct apply_helper<1> {
  template<typename F, typename tuple_type, size_t arg_0> struct tuple_traits {
    typedef typename result1<F,
      typename std::tuple_element<arg_0, tuple_type>::type > type;
  };

  template< typename F, typename Args, size_t arg_0 >
  static auto apply( F& f, Args& args ) -> typename tuple_traits<F,Args,arg_0>::type {
    return f( std::get<arg_0>::(arg) );
  }
};

template<>
struct apply_helper<2> {
  template<typename F, typename tuple_type, size_t arg_0> struct tuple_traits {
    typedef typename result2<F,
      typename std::tuple_element<arg_0,   tuple_type>::type,
      typename std::tuple_element<arg_0+1, tuple_type>::type> type;
  };

  template< typename F, typename Args, size_t arg_0 >
  static auto apply( F& f, Args& args ) -> typename tuple_traits<F,Args,arg_0>::type {
    return f( std::get<arg_0>::(arg), std::get<arg_0+1>::(arg) );
  }
};

template<>
struct apply_helper<3> {
  template<typename F, typename tuple_type, size_t arg_0> struct tuple_traits {
    typedef typename result3<F,
      typename std::tuple_element<arg_0,   tuple_type>::type,
      typename std::tuple_element<arg_0+1, tuple_type>::type,
      typename std::tuple_element<arg_0+2, tuple_type>::type> type;
  };

  template< typename F, typename Args, size_t arg_0 >
  static auto apply( F& f, Args& args ) -> typename tuple_traits<F,Args,arg_0>::type {
    return f( std::get<arg_0>::(arg), std::get<arg_0+1>(arg), std::get<arg_0+2>(arg) );
  }
};

template<>
struct apply_helper<4> {
  template<typename F, typename tuple_type, size_t arg_0> struct tuple_traits {
    typedef typename result4<F, 
      typename std::tuple_element<arg_0,   tuple_type>::type,
      typename std::tuple_element<arg_0+1, tuple_type>::type,
      typename std::tuple_element<arg_0+2, tuple_type>::type,
      typename std::tuple_element<arg_0+3, tuple_type>::type> type;
  };

  template< typename F, typename Args, size_t arg_0 >
  static auto apply( F& f, Args& args ) -> typename tuple_traits<F,Args,arg_0>::type {
    return f( std::get<arg_0>::(arg), std::get<arg_0+1>(arg), std::get<arg_0+2>(arg), std::get<arg_0+3>(arg) );
  }
};

template< typename F, typename Args, size_t arg_0, size_t arg_c >
inline auto apply( F& f, Args& args) -> typename apply_helper<arg_c>::tuple_traits<F,Args,arg_0>::type {
  return apply_helper<arg_c>::apply<F,Args,arg_0>(f, args);
}

}


#endif