FunctionComposition
=============

FunctionComposition is a simple header-based C++ library for composing functions.

It provides a simple and expressive way of combining program logic and routines, with 
support for lambdas, function objects and pure functions.  


Example
-------------

    using namespace fc;
    
    auto sqare      = [](float x) { return x*x;           };
    auto halve      = [](float x) { return .5f*x;         };
    auto inv_square = [](float x) { return std::sqrtf(x); };
    auto inv_halve  = [](float x) { return 2.f*x;         };

    auto square_halve     = square           + halve;
    auto inv_square_halve = inv_halve        + inv_square;
    auto ident            = inv_square_halve + squave_halve;

    assert(square_halve(6.f)     == 9.f);
    assert(inv_square_halve(9.f) == 6.f);
    assert(ident(10.0f)          == 10.0f);


Documentation
-------------

Please see the file called INSTALL.  
Several samples and tests are included with the source, which together with CMake can be built and run 
with any compatible compiler (developed with VC10, tested on GCC 4.6).  

Licensing
---------

Please see the file called LICENSE.

Contributions
-------------

This projet was loosely inspired by Eric Niebler's blog post "Fun with Function Composition" over at Expressive C++ 
(http://cpp-next.com/archive/2010/11/expressive-c-fun-with-function-composition/)