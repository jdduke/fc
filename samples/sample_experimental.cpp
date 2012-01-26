/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2012, Jared Duke.
// This code is released under the MIT License.
// www.opensource.org/licenses/mit-license.php
/////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER)
#pragma warning( disable : 4244 )
#endif

#include <algorithm>
#include <numeric>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include <fc.h>

template < class InputIterator1, class InputIterator2, class InputIterator3, class InputIterator4, class OutputIterator, class Op>
OutputIterator transform4(InputIterator1 first1, InputIterator1 last1,
                          InputIterator2 first2,
                          InputIterator3 first3,
                          InputIterator4 first4,
                          OutputIterator result, Op op ) {
  while (first1 != last1)
    *result++ = op(*first1++, *first2++, *first3++, *first4++);
  return result;
}

void test() {

  using namespace fc;

  ///////////////////////////////////////////////////////////////////////////
  {

    //auto length_squared = [](float x, float y, float z) -> float { return x*x + y*y + z*z; };
    auto add            = [](float x, float y) -> float { return x + y; };
    auto mult           = [](float x, float y) -> float { return x * y; };
    auto mult_add_4     = compose2(add, mult, mult);
    auto test           = [](float x, float y, float z, float w) -> float {
      return (x * y) + (z * w);
    };

    std::vector<float> one_to_hundred(100);
    std::vector<float> result(one_to_hundred.size());
    std::vector<float> test_result(one_to_hundred.size());
    std::iota(std::end(one_to_hundred), std::begin(one_to_hundred), 1);

    transform4(std::begin(one_to_hundred),
               std::end(  one_to_hundred),
               std::begin(one_to_hundred),
               std::begin(one_to_hundred),
               std::begin(one_to_hundred),
               std::begin(result),
               mult_add_4);

    transform4(std::begin(one_to_hundred),
      std::end(  one_to_hundred),
      std::begin(one_to_hundred),
      std::begin(one_to_hundred),
      std::begin(one_to_hundred),
      std::begin(test_result),
      test);

    std::cout << "Success = " << std::equal( result.begin(), result.end(), test_result.begin() ) << std::endl;
  }

  {
    //auto length_squared = [](float x, float y, float z) -> float { return x*x + y*y + z*z; };
    auto added          = [](float x, float y, float z) -> float { return x + y + z; };
    auto doubled        = [](float x) -> float { return x * 2.0f; };
    auto multiplied     = [](float x, float y) -> float { return x * y; };
    auto mult_add_4     = compose2(multiplied, added, doubled);
    auto test           = [](float x, float y, float z, float w) -> float {
      return .5f * (x + y + z + 2.0f * w);
    };

    std::vector<float> one_to_hundred(100);
    std::vector<float> result(one_to_hundred.size());
    std::vector<float> test_result(one_to_hundred.size());
    std::iota(std::end(one_to_hundred), std::begin(one_to_hundred), 1);

    transform4(std::begin(one_to_hundred),
      std::end(  one_to_hundred),
      std::begin(one_to_hundred),
      std::begin(one_to_hundred),
      std::begin(one_to_hundred),
      std::begin(result),
      mult_add_4);

    transform4(std::begin(one_to_hundred),
      std::end(  one_to_hundred),
      std::begin(one_to_hundred),
      std::begin(one_to_hundred),
      std::begin(one_to_hundred),
      std::begin(result),
      test);

    std::cout << "Success = " << std::equal( result.begin(), result.end(), test_result.begin() ) << std::endl;
  }

}

int main(int argc, char** argv) {

  test();

  return 0;
}
