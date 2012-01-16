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

#define TEST1 0
#define TEST2 0
#define TEST3 0
#define TEST4 1

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

///////////////////////////////////////////////////////////////////////////

template <typename T>
typename std::add_rvalue_reference<T>::type declval();

///////////////////////////////////////////////////////////////////////////

#if 0
template <typename T> struct function_arity;

template <typename R, typename C>
struct function_arity<R(C::*)()>{ enum { arity = 0 }; };

template <typename R, typename C,typename T1>
struct function_arity<R(C::*)(T1)>{ enum { arity = 1 }; };

template <typename R, typename C,typename T1,typename T2>
struct function_arity<R(C::*)(T1,T2)>{ enum { arity = 2 }; };

template <typename R, typename C,typename T1,typename T2,typename T3>
struct function_arity<R(C::*)(T1,T2,T3)>{ enum { arity = 3 }; };

template <typename R, typename C,typename T1,typename T2,typename T3,typename T4>
struct function_arity<R(C::*)(T1,T2,T3,T4)>{ enum { arity = 4 }; };

template<typename Functor, size_t NArgs, typename Return>
struct count_arg : std::enable_if<function_arity<Functor>::arity==NArgs, Return>
{};

#else

template <typename T>
struct function_traits : public function_traits< decltype( &T::operator() ) > {};

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

#endif

///////////////////////////////////////////////////////////////////////////

template<class F, class G>
class composed_base {
public:
  composed_base(F f_, G g_) : f(f_), g(g_) { }

  template< typename Composed >
  auto compose(Composed c) -> decltype( ::compose(::compose(f,g),c) ) {
    return ::compose(::compose(f,g),c);
  }

  template< typename Composed >
  auto operator+(Composed c) -> decltype( ::compose(::compose(f,g),c) ) {
    return this->compose(c);
  }

protected:
  F f;
  G g;
};

///////////////////////////////////////////////////////////////////////////

template<class F, class G, size_t ArgC = 0>
class composed : public composed_base<F,G> {
  template<typename F, typename G>
  struct result
  {
    typedef decltype( declval<G>().operator()() ) U;
    typedef decltype( declval<F>().operator()(declval<U>()) ) type;
  };

public:
  composed(F f_, G g_) : composed_base<F,G>(f_,g_) { }
  auto operator()() -> typename result<F,G>::type { return f(g()); }
};

///////////////////////////////////////////////////////////////////////////

template<class F, class G>
class composed<F,G,1> : public composed_base<F,G> {
  template<typename F, typename G, typename T1>
  struct result
  {
    typedef decltype( declval<G>().operator()(declval<T1>()) ) U;
    typedef decltype( declval<F>().operator()(declval<U>()) ) type;
  };

public:
  composed(F f_, G g_) : composed_base<F,G>(f_,g_) { }

  template<typename T1>
  auto operator()(const T1& t) -> typename result<F,G,T1>::type {
    return f(g(t));
  }
};

///////////////////////////////////////////////////////////////////////////

template<class F, class G>
class composed<F,G,2> : public composed_base<F,G> {
  template<typename F, typename G, typename T1, typename T2>
  struct result
  {
    typedef decltype( declval<G>().operator()(declval<T1>(), declval<T2>()) ) U;
    typedef decltype( declval<F>().operator()(declval<U>()) ) type;
  };

public:
  composed(F f_, G g_) : composed_base<F,G>(f_,g_) { }

  template<typename T1, typename T2>
  auto operator()(const T1& t1, const T2& t2) -> typename result<F,G,T1,T2>::type {
    return f(g(t1,t2));
  }
};

///////////////////////////////////////////////////////////////////////////

template<class F, class G>
class composed<F,G,3> : public composed_base<F,G> {
  template<typename F, typename G, typename T1, typename T2, typename T3>
  struct result
  {
    typedef decltype( declval<G>().operator()(declval<T1>(), declval<T2>(), declval<T3>()) ) U;
    typedef decltype( declval<F>().operator()(declval<U>()) ) type;
  };

public:
  composed(F f_, G g_) : composed_base<F,G>(f_,g_) { }

  template<typename T1, typename T2, typename T3>
  auto operator()(const T1& t1, const T2& t2, const T3& t3) -> typename result<F,G,T1,T2,T3>::type {
    return f(g(t1,t2,t3));
  }
};

///////////////////////////////////////////////////////////////////////////

template<typename F, typename G>
typename count_arg<G, 0, composed<F,G,0> >::type compose(F f, G g) {
  return composed<F,G,0>(f, g);
}

template<typename F, typename G>
typename count_arg<G, 1, composed<F,G,1> >::type compose(F f, G g) {
  return composed<F,G,1>(f, g);
}

template<typename F, typename G>
typename count_arg<G, 4, composed<F,G,4> >::type compose(F f, G g) {
  return composed<F,G,4>(f, g);
}

template<typename F, typename G>
typename count_arg<G, 3, composed<F,G,3> >::type compose(F f, G g) {
  return composed<F,G,3>(f, g);
}

#define COMPOSE (f,g)       compose((f),(g))
#define COMPOSE2(h,f,g)     compose(compose(h,f),g)
#define COMPOSE3(i,h,f,g)   compose(compose(compose(i,h),f),g)

}

bool hello() { std::cout << "Hello "; return true; }
void world(bool print) { if(print) std::cout << " World "; }

using namespace cmp;

void test() {
  {
    std::function<bool(void)> g = hello;
    std::function<void(bool)> f = world;
    //auto fg = compose(f,g);
    //auto fg = compose(world,hello);
    //std::cout << fg(2) << std::endl;
  }

  {
    auto g1 = [](int)  -> bool  { std::cout << "Hello"; return true;  };
    auto g2 = [](bool) -> float { std::cout << " World" << std::endl; return 1.; };
    auto g = compose(g2, g1);
    std::cout << g(1) << std::endl;

    auto f = compose([](int y) -> bool  { std::cout << y * y << std::endl; return y > 0; },
                     [](float x) -> int { return (int)(x * 2);  });
    std:: cout << f(2.f);

    auto h = compose(f, g2);
    std::cout << h(false);
  }

  ///////////////////////////////////////////////////////////////////////////

  {
    auto g = [](float x, float y, float z) -> float { return x*x + y*y + z*z; };
    auto f = [](float l2) -> float                  { return std::sqrt(l2); };

    float v[] = {1.f, 2.f, -1.f};
    auto fg = compose(f, g);

    std::cout << "Length = " << fg(v[0], v[1], v[2]) << std::endl;

    auto h    = [](float f_) -> int { return (int)std::ceil(f_); };
    auto hf   = compose(h,f);
    auto hfg  = compose(hf,g);
    auto hfg2 = COMPOSE2(h,f,g);
    auto hfg3 = compose(h,f) + g;
    auto hfg4 = compose(h,f).compose(g);

    std::cout << hf(9.f) << std::endl;
    std::cout << hfg(v[0], v[1], v[2]) << std::endl;
    std::cout << hfg2(v[0], v[1], v[2]) << std::endl;
    std::cout << hfg3(v[0], v[1], v[2]) << std::endl;
  }
}

int main(int argc, char** argv) {

  test();

  return 0;
}
