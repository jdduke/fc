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

#include <fc.h>

bool hello() { std::cout << "Hello "; return true; }
void world(bool print) { if(print) std::cout << " World " << std::endl; }

void test() {

  using namespace fc;

  {
    auto hello_world = make_function(world) + make_function(hello);
    hello_world();

    auto hello2 = []()     -> bool { return hello(); };
    auto world2 = [](bool b)       { world(b);       };
    compose(world2, hello2)();
  }

  ///////////////////////////////////////////////////////////////////////////

  {
    auto g = [](float x, float y, float z) -> float { return x*x + y*y + z*z; };
    auto f = [](float l2) -> float                  { return std::sqrt(l2); };
    auto fg  = compose(f, g);
    auto fg2 = f+g;
    auto fg3  = [](float l2) -> float                  { return std::sqrt(l2); }
              + [](float x, float y, float z) -> float { return x*x + y*y + z*z; };
    auto fg4  = compose([](float l2) -> float                  { return std::sqrt(l2); },
                        [](float x, float y, float z) -> float { return x*x + y*y + z*z; });


    float v[] = {1.f, 2.f, -1.f};
    std::cout << "Length (compose(f,g))         = " << fg( v[0], v[1], v[2]) << std::endl;
    std::cout << "Length (f+g)                  = " << fg2(v[0], v[1], v[2]) << std::endl;
    std::cout << "Length (f_lam + g_lam)        = " << fg3(v[0], v[1], v[2]) << std::endl;
    std::cout << "Length (compose(f_lam,g_lam)) = " << fg4(v[0], v[1], v[2]) << std::endl;

    ///////////////////////////////////////////////////////////////////////////

    auto h    = [](float f_) -> int { return (int)std::ceil(f_); };
    auto hf   = compose(h,f);
    auto hfg  = compose(hf,g);
    auto hfg1 = compose( [](float f)                   -> int   { return (int)std::ceil(f); },
                         [](float l)                   -> float { return std::sqrt(l);      },
                         [](float x, float y, float z) -> float { return x*x + y*y + z*z;   } );
    auto hfg2 = compose(h,f,g);
    auto hfg3 = compose(h,f) + g;
    auto hfg4 = hf+g;
    auto hfg5 = h+f+g;
    auto hfg6 = h+(compose(f,g));
    auto hfg7 = (compose(h,f)+g);
    auto fffg  = (f+f).with(f).with(g);
    auto fffg2 = f+f+f+g;

    std::cout << "Length = " << fg( v[0], v[1], v[2]) << std::endl;
    std::cout << "Ceil(Length) = " << hfg( v[0], v[1], v[2]) << std::endl;
    std::cout << "Ceil(Length) = " << hfg1(v[0], v[1], v[2]) << std::endl;
    std::cout << "Ceil(Length) = " << hfg2(v[0], v[1], v[2]) << std::endl;
    std::cout << "Ceil(Length) = " << hfg3(v[0], v[1], v[2]) << std::endl;
    std::cout << "Ceil(Length) = " << hfg4(v[0], v[1], v[2]) << std::endl;
    std::cout << "Ceil(Length) = " << hfg5(v[0], v[1], v[2]) << std::endl;
    std::cout << "Ceil(Length) = " << hfg6(v[0], v[1], v[2]) << std::endl;
    std::cout << "Ceil(Length) = " << hfg7(v[0], v[1], v[2]) << std::endl;
    std::cout << "Sqrt(Sqrt(Length))) = " << fffg( v[0], v[1], v[2]) << std::endl;
    std::cout << "Sqrt(Sqrt(Length))) = " << fffg2(v[0], v[1], v[2]) << std::endl;
  }
}

int main(int argc, char** argv) {

  test();

  return 0;
}
