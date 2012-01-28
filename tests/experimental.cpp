#if defined(FC_EXPERIMENTAL)

#include <gtest/gtest.h>

#include <fc.h>

#include "common.h"

using namespace fc;

///////////////////////////////////////////////////////////////////////////

template<typename A, typename B>
inline void testNoArgs(A& a, B& b)
{
  EXPECT_EQ(2.f, b());
  EXPECT_EQ(2.f, (b + a)());
}

TEST(CompoundNoArgs, Func) {
  auto voidFuncA = compose2(make_function(Void_Float2), make_function(Float_Void), make_function(Float_Void));
  auto voidFuncB = compose2(make_function(Float_Float2), make_function(Float_Void), make_function(Float_Void));
  testNoArgs(voidFuncA, voidFuncB);
}

TEST(CompoundNoArgs, FuncObj) {
  auto voidFuncA = compose2(S_Void_Float2(),  S_Float_Void(), S_Float_Void());
  auto voidFuncB = compose2(S_Float_Float2(), S_Float_Void(), S_Float_Void());
  testNoArgs(voidFuncA, voidFuncB);
}

TEST(CompoundNoArgs, Lambda) {
  auto voidFuncA = compose2(L_Void_Float2,  L_Float_Void, L_Float_Void);
  auto voidFuncB = compose2(L_Float_Float2, L_Float_Void, L_Float_Void);
  testNoArgs(voidFuncA, voidFuncB);
}

///////////////////////////////////////////////////////////////////////////

template<typename A, typename B, typename C, typename D>
inline void testArgs(A& a, B& b, C& c, D& d)
{
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

TEST(CompoundMultipleArgs, Func) {
  auto floatFunc  = compose(make_function(Float_Float),  make_function(Float_Float));
  auto floatFunc2 = compose(make_function(Float_Float),  make_function(Float_Float2));
  auto floatFunc3 = compose(make_function(Float_Float),  make_function(Float_Float3));
  auto floatFunc4 = compose(make_function(Float_Float),  make_function(Float_Float4));
  testArgs(floatFunc, floatFunc2, floatFunc3, floatFunc4);
}

TEST(CompoundMultipleArgs, FuncObj) {
  auto floatFunc  = S_Float_Float() + S_Float_Float();
  auto floatFunc2 = S_Float_Float() + S_Float_Float2();
  auto floatFunc3 = S_Float_Float() + S_Float_Float3();
  auto floatFunc4 = S_Float_Float() + S_Float_Float4();
  testArgs(floatFunc, floatFunc2, floatFunc3, floatFunc4);
}

TEST(CompoundMultipleArgs, Lambda) {
  auto floatFunc  = L_Float_Float + L_Float_Float;
  auto floatFunc2 = L_Float_Float + L_Float_Float2;
  auto floatFunc3 = L_Float_Float + L_Float_Float3;
  auto floatFunc4 = L_Float_Float + L_Float_Float4;
  testArgs(floatFunc, floatFunc2, floatFunc3, floatFunc4);
}

#endif