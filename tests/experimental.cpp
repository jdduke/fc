#if defined(FC_EXPERIMENTAL)

#include <gtest/gtest.h>

#include <fc.h>

#include "common.h"

using namespace fc;

///////////////////////////////////////////////////////////////////////////

template<typename A, typename B, typename C, typename D>
inline void testNoArgs(A& a, B& b, C& c, D& d)
{
  // TODO: This should compile properly
  //EXPECT_EQ(1.f, voidFunc3(1.f));
  EXPECT_EQ(1.f, d());
  EXPECT_EQ(1.f, (d + a)());
}

TEST(CompoundNoArgs, Func) {
  auto voidFunc  = compose(make_function(Void_Void),  make_function(Void_Void));
  auto voidFunc2 = compose(make_function(Void_Float), make_function(Float_Void));
  auto voidFunc3 = compose(make_function(Float_Void), make_function(Void_Float));
  auto voidFunc4 = compose(make_function(Float_Float), make_function(Float_Void));
  testNoArgs(voidFunc, voidFunc2, voidFunc3, voidFunc4);
}

TEST(CompoundNoArgs, FuncObj) {
  auto voidFunc  = S_Void_Void()   + S_Void_Void();
  auto voidFunc2 = S_Void_Float()  + S_Float_Void();
  auto voidFunc3 = S_Float_Void()  + S_Void_Float();
  auto voidFunc4 = S_Float_Float() + S_Float_Void();
  testNoArgs(voidFunc, voidFunc2, voidFunc3, voidFunc4);
}

TEST(CompoundNoArgs, Lambda) {
  auto voidFunc  = L_Void_Void   + L_Void_Void;
  auto voidFunc2 = L_Void_Float  + L_Float_Void;
  auto voidFunc3 = L_Float_Void  + L_Void_Float;
  auto voidFunc4 = L_Float_Float + L_Float_Void;
  testNoArgs(voidFunc, voidFunc2, voidFunc3, voidFunc4);
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