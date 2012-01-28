#if defined(FC_EXPERIMENTAL)

#include <gtest/gtest.h>

#include <fc.h>

#include "common.h"

using namespace fc;

///////////////////////////////////////////////////////////////////////////

template<typename A, typename B, typename C>
inline void testNoArgs(A a_, B b_, C c_)
{
  auto a = compose2(b_, a_, a_);
  auto b = compose2(c_, a_, a_);

  EXPECT_EQ(2.f, b());
  EXPECT_EQ(2.f, (b + a)());
}

TEST(CompoundNoArgs, Func) {
  testNoArgs(f(Float_Void), f(Void_Float2), f(Float_Float2));
}

TEST(CompoundNoArgs, FuncObj) {
  testNoArgs(s(Float_Void), s(Void_Float2), s(Float_Float2));
}

TEST(CompoundNoArgs, Lambda) {
  testNoArgs(l(Float_Void), l(Void_Float2), l(Float_Float2));
}

///////////////////////////////////////////////////////////////////////////

template<typename A, typename B>
inline void testArgs(A a_, B b_)
{
  auto a = compose2(b_, a_, a_);
  auto b = compose2(b_, b_, b_);
  auto c = compose2(b_, a, a);

  EXPECT_EQ(2.f, a(1.f,1.f));
  EXPECT_EQ(4.f, b(1.f,1.f,1.f,1.f));
  EXPECT_EQ(4.f, c(1.f,1.f,1.f,1.f));

  EXPECT_EQ(0.f,  a(1.f,-1.f));
  EXPECT_EQ(0.f,  b(-1.f,1.f,-1.f,1.f));
  EXPECT_EQ(0.f,  c(-1.f,1.f,-1.f,1.f));

  auto mult_2 = [](float x) -> float { return x*2; };
  EXPECT_EQ(8.f,  (mult_2 + a)(2.f,2.f));
  EXPECT_EQ(16.f, (mult_2 + b)(2.f,2.f,2.f,2.f));
  EXPECT_EQ(16.f, (mult_2 + c)(2.f,2.f,2.f,2.f));
}

TEST(CompoundMultipleArgs, Func) {
  testArgs(f(Float_Float), f(Float_Float2));
}

TEST(CompoundMultipleArgs, FuncObj) {
  testArgs(s(Float_Float), s(Float_Float2));
}

TEST(CompoundMultipleArgs, Lambda) {
  testArgs(l(Float_Float), l(Float_Float2));
}

#endif