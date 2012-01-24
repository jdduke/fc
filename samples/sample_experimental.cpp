/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2012, Jared Duke.
// This code is released under the MIT License.
// www.opensource.org/licenses/mit-license.php
/////////////////////////////////////////////////////////////////////////////

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

    //typedef compound_result24<decltype(add),decltype(mult),decltype(mult),float,float,float,float>::type float_type;
    //float_type floater = 10.;
    std::vector<int>   one_to_hundred(100);
    std::vector<float> result(one_to_hundred.size());
    std::iota(std::end(one_to_hundred), std::begin(one_to_hundred), 1);

    transform4(std::begin(one_to_hundred),
               std::end(  one_to_hundred),
               std::begin(one_to_hundred),
               std::begin(one_to_hundred),
               std::begin(one_to_hundred),
               std::begin(result),
               mult_add_4);
  }
}

int main(int argc, char** argv) {

  test();

  return 0;
}
