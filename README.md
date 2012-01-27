FunctionComposition
=============

FunctionComposition is a simple header-based C++ library for composing functions.

It provides a simple and expressive way of combining program logic and routines, with 
support for lambdas, function objects and pure functions.  


Example
-------------

A simple example with lambdas, using the (+) operator for composition:

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
    
A more complicated example, without the (+) for composition:

    using namespace fc;
    
    // polar coordinate r = sqrt(x*x+y*y)
    
    auto r1 = compose(std::sqrtf, [](float x, float y) { return x*x + y*y; });
    r1(1.f, 2.f);
    
    auto square = [](float x)          { return x*x; };
    auto add    = [](float x, float y) { return x + y; };
    auto sqrt   = [](float x)          { return std::sqrtf(x); };
    
    // r = f(g(h(x),h(y))) where f = sqrt, g = add, h = square
    auto r2     = compose(sqrt, compose2(add, square, square));
    r2(1.f, 2.f);


Documentation
-------------

Please see the file called INSTALL.  
Several samples and tests are included with the source, which together with CMake can be built and run 
with any compatible compiler (developed with VC10, tested on GCC 4.6).  

Licensing
---------

MIT.
Please see the file called LICENSE.

Contributions
-------------

This projet was loosely inspired by Eric Niebler's blog post "Fun with Function Composition" over at Expressive C++ 
(http://cpp-next.com/archive/2010/11/expressive-c-fun-with-function-composition/).  fc goes somewhat further, allowing 
multiple arguments at any level in the composition, with arbitrary return types.