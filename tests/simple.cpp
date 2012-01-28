#include <gtest/gtest.h>

#include <fc.h>

#include "common.h"

using namespace fc;

/////////////////////////////////////////////////////////////////////////////

template<typename A, typename B, typename C, typename D>
void testNoArgs(A a_, B b_, C c_, D d_)
{
  auto a = compose(a_,a_);
  auto b = compose(b_,c_);
  auto c = compose(c_,b_);
  auto d = compose(d_,c_);

  a();
  b();
  EXPECT_EQ(1.f, c(1.f));
  EXPECT_EQ(1.f, d());
  EXPECT_EQ(1.f, (d + a)());
}

TEST(SimpleNoArgs, Func) {
  testNoArgs(f(Void_Void), f(Void_Float), f(Float_Void), f(Float_Float));
}

TEST(SimpleNoArgs, FuncObj) {
  testNoArgs(s(Void_Void), s(Void_Float), s(Float_Void), s(Float_Float));
}

TEST(SimpleNoArgs, Lambda) {
  testNoArgs(l(Void_Void), l(Void_Float), l(Float_Void), l(Float_Float));
}

///////////////////////////////////////////////////////////////////////////

template<typename A, typename B, typename C, typename D>
void testArgs(A a_, B b_, C c_, D d_)
{
  auto a = compose(a_,a_);
  auto b = compose(a_,b_);
  auto c = compose(a_,c_);
  auto d = compose(a_,d_);

  EXPECT_EQ(1.f, a(1.f));
  EXPECT_EQ(2.f, b(1.f,1.f));
  EXPECT_EQ(3.f, c(1.f,1.f,1.f));
  EXPECT_EQ(4.f, d(1.f,1.f,1.f,1.f));

  EXPECT_EQ(1.f,  a(1.f));
  EXPECT_EQ(0.f,  b(-1.f,1.f));
  EXPECT_EQ(-1.f, c(-1.f,1.f,-1.f));
  EXPECT_EQ(0.f,  d(-1.f,1.f,-1.f,1.f));

  EXPECT_EQ(2.f, (a + a) (2.f));
  EXPECT_EQ(4.f, (a + b)(2.f,2.f));
  EXPECT_EQ(6.f, (a + c)(2.f,2.f,2.f));
  EXPECT_EQ(8.f, (a + d)(2.f,2.f,2.f,2.f));
}

TEST(SimpleMultipleArgs, Func) {
  testArgs(f(Float_Float), f(Float_Float2), f(Float_Float3), f(Float_Float4));
}

TEST(SimpleMultipleArgs, FuncObj) {
  testArgs(s(Float_Float), s(Float_Float2), s(Float_Float3), s(Float_Float4));
}

TEST(SimpleMultipleArgs, Lambda) {
  testArgs(l(Float_Float), l(Float_Float2), l(Float_Float3), l(Float_Float4));
}
