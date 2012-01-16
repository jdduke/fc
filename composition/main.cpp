/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2012, Jared Duke.
// This code is released under the MIT License.
// www.opensource.org/licenses/mit-license.php
/////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <functional>
#include <type_traits>

namespace str {

using std::string;
using std::stringstream;
typedef std::vector<string> strings;

strings& split(const string& s, char delim, strings& elems) {
  stringstream ss(s);
  string item;
  while(std::getline(ss, item, delim)) {
    elems.push_back(item);
  }
  return elems;
}

strings split(const string &s, char delim) {
  strings elems;
  return split(s, delim, elems);
}

strings lines(const string& s) {
  return split(s, '\n');
}

string unlines(const strings& elems) {
  stringstream ss;
  std::for_each(elems.begin(), elems.end(), [&ss](const string& s) {
    ss << s << std::endl;
  });
  return ss.str();
}

}

namespace cmp {

/*
template <class T> struct function_arity;

template <class R>
struct function_arity<R()>{static const int value = 0;};

// for N=1..N_max do
template <class R,class T1>
struct function_arity<R(T1)>{static const int value = 1;};

template <class R,class T1,class T2>
struct function_arity<R(T1,T2)>{static const int value = 2;};

template <class R,class T1,class T2,class T3>
struct function_arity<R(T1,T2,T3)>{static const int value = 3;};

template <class R,class T1,class T2,class T3,class T4>
struct function_arity<R(T1,T2,T3,T4){static const int value = 4;};
*/

// etc
/*template <typename T>
typename std::add_rvalue_reference<T>::type declval();*/

  /*
template <typename T>
struct function_traits : public function_traits< decltype( &T::operator() ) >
{};

template <typename C, typename R, typename T0>
struct function_traits<R(C::*)(T0) const> { enum { arity = 1 }; };

template <typename C, typename R, typename T0, typename T1>
struct function_traits<R(C::*)(T0,T1) const> { enum { arity = 2 }; };

template <typename C, typename R, typename T0, typename T1, typename T2>
struct function_traits<R(C::*)(T0,T1,T2) const> { enum { arity = 3 }; };

template<typename Functor, size_t NArgs>
struct count_arg : std::enable_if<function_traits<Functor>::arity==NArgs, int>
{};

template<class F, class G>
class composed {
public:

  enum { arity = function_traits<G>::arity };

  composed(F f_, G g_) : f(f_), g(g_) { }

  template< class F0, class G0 >
  struct T0Arg { 
    //typedef typename std::result_of< declval<F0>(declval<G0>()) >::type type; 
    typedef typename std::result_of< G0() >::type U;
    typedef typename std::result_of< F(U) >::type type;
  };

  template< class F0, class G0, class T1 >
  struct T1Arg { 
    //typedef typename std::result_of< declval<F0>(declval<G0>()) >::type type; 
    typedef typename std::result_of< G0(T1) >::type U;
    typedef typename std::result_of< F(U) >::type type;
  };

  template< class F0, class G0, class T1, class T2 >
  struct T2Arg { 
    //typedef typename std::result_of< declval<F0>(declval<G0>()) >::type type; 
    typedef typename std::result_of< G0(T1, T2) >::type U;
    typedef typename std::result_of< F(U) >::type type;
  };

  template< class F0, class G0, class T1, class T2, class T3 >
  struct T3Arg { 
    //typedef typename std::result_of< declval<F0>(declval<G0>()) >::type type; 
    typedef typename std::result_of< G0(T1, T2, T3) >::type U;
    typedef typename std::result_of< F(U) >::type type;
  };

  typename std::enable_if<(0==arity) && std::is_same<typename T0Arg<F,G>::type,void>::value, typename T0Arg<F,G>::type >::type 
    operator()() {
      f(g());
      //f();
  }

  template<typename T1>
  typename std::enable_if<1==arity, typename T1Arg<F,G,T1>::type >::type 
    operator()(const T1& t1) {
      return f(g(t1));
  }

  template<typename T1, typename T2>
  typename std::enable_if<2==arity, typename T2Arg<F,G,T1,T2>::type >::type 
    operator()(const T1& t1, const T2& t2) {
      return f(g(t1,t2));
  }

  template<typename T1, typename T2, typename T3>
  typename std::enable_if<3==arity, typename T3Arg<F,G,T1,T2,T3>::type >::type 
    operator()(const T1& t1, const T1& t2, const T1& t3) {
      return f(g(t1,t2,t3));
  }

private:
  F f;
  G g;
};

template<class F, class G>
composed<F,G> compose(F f, G g) {
  return composed<F,G>(f, g);
}

template<class F, class G>
composed<F,G> compose(F f, G g) {
  return compose<F,G,function_traits<G>::arity>(f, g);
}*/


template <typename T>
struct function_traits : public function_traits<decltype(&T::operator())>
{};

template <typename C, typename R, typename T0>
struct function_traits<R(C::*)(T0) const> { enum { arity = 1 }; };

template <typename C, typename R, typename T0, typename T1>
struct function_traits<R(C::*)(T0,T1) const> { enum { arity = 2 }; };

template <typename C, typename R, typename T0, typename T1, typename T2>
struct function_traits<R(C::*)(T0,T1,T2) const> { enum { arity = 3 }; };

template<typename Functor, size_t NArgs>
struct count_arg : std::enable_if<function_traits<Functor>::arity==NArgs, int>
{};

template<class F, class G>
class composed_base {
public:
  composed_base(F f_, G g_) : f(f_), g(g_) { }

protected:
  F f;
  G g;
};

template<class F, class G, size_t ArgC = 0>
class composed : public composed_base<F,G> {
  typedef typename std::result_of< G() >::type U;
  typedef typename std::result_of< F(U) >::type type;

public:
  composed(F f_, G g_) : composed_base<F,G>(f_,g_) { }
  type operator()() { return f(g()); }
};


template<class F, class G>
class composed<F,G,1> : public composed_base<F,G> {
  template< class F0, class G0, class T1 >
  struct T1Arg { 
    //typedef typename std::result_of< declval<F0>(declval<G0>()) >::type type; 
    typedef typename std::result_of< G0(T1) >::type U;
    typedef typename std::result_of< F(U) >::type type;
  };

public:
  composed(F f_, G g_) : composed_base<F,G>(f_,g_) { }

  template<typename T>
  typename T1Arg<F,G,T>::type operator()(const T& t1) { return f(g(t1)); }
};

template<class F, class G>
class composed<F,G,2> : public composed_base<F,G> {
  template< class F0, class G0, class T1, class T2 >
  struct T2Arg { 
    typedef typename std::result_of< G0(T1,T2) >::type U;
    typedef typename std::result_of< F(U) >::type type;
  };

public:
  composed(F f_, G g_) : composed_base<F,G>(f_,g_) { }

  template<typename T1, typename T2>
  typename T2Arg<F,G,T1,T2>::type operator()(const T1& t1, const T2& t2) { return f(g(t1,t2)); }
};

template<class F, class G>
class composed<F,G,3> : public composed_base<F,G> {
  template< class F0, class G0, class T1, class T2, class T3 >
  struct T3Arg { 
    typedef typename std::result_of< G0(T1,T2,T3) >::type U;
    typedef typename std::result_of< F(U) >::type type;
  };

public:
  composed(F f_, G g_) : composed_base<F,G>(f_,g_) { }

  template<typename T1, typename T2, typename T3>
  typename T3Arg<F,G,T1,T2,T3>::type operator()(const T1& t1, const T2& t2, const T3& t3) { return f(g(t1,t2,t3)); }
};

/*
template<class F, class G>
composed<F,G,function_traits<G>::arity> compose(F f, G g) {
  return composed<F,G>(f, g);
}
*/
template<class F, class G>
auto compose(F f, G g) -> decltype(composed<F,G,function_traits<G>::arity>) {
  return composed<F,G>(f, g);
}

}

bool hello() { std::cout << "Hello "; return true; }
void world(bool print) { if(print) std::cout << " World "; }
 
int main(int argc, char** argv) {

  using namespace cmp;

  auto f = [](bool) { std::cout << "Test: "; };
  size_t arity = function_traits<decltype(f)>::arity;
  std::cout << "arity = " << arity << std::endl;

  auto g = compose([](bool) -> float { std::cout << " World" << std::endl; return 1.; }, 
                   []()     -> bool  { std::cout << "Hello"; return true;  });
  g();

  /*
  auto f = compose([](int y)          { std::cout << y * y << std::endl; },
                   [](float x) -> int { return (int)(x * 2);  });
  f(2.);

  auto h = compose(f, g);
  */
  return 0;
}
