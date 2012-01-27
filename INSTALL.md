FunctionComposition
=============

Usage
-----

FC is a header-only library; just include and forget.  All relevant functions and structures live
within the fc namespace.

Compilation
--------
fc itself requires no compilation: it is header-only.  All that is required is support for a certain
subset of C++11 functionality.  It was developed with VC10 support at the minimum; variadic
templates are used where supported, as well as other C++11 features that significantly reduce
the code necessary to achieve the basic functionality.


Samples
-------

Samples can be built using CMake.  Simply point CMake to the root directory to generate project files 
for the samples.  Several options for building are documented within CMake itself, make sure BUILD_SAMPLES is enabled.


    fcSample       - Shows several simple examples of fc usage.
    fcSampleString - Shows some examples involving string parsing and manipulation. 
                     Patterned after a Haskell example seen recently.
    fcExperimental - Shows "nested" function composition.  
                     That is, given functions f,g,h, produced a composed function c = f(g(),h()).

Tests
-----

Tests are also built using CMake, and are dependent on the google unit testing framework (http://code.google.com/p/googletest/)  Several options for building are documented within CMake itself, make sure BUILD_TESTS is enabled.


    fcTests        - Contains all unit tests