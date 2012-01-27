FunctionComposition
=============

Usage
-----

FC is a header-only library; just include and forget.  All relevant functions and structures live
within the fc namespace.


Samples
-------------

Samples can be built using CMake.  Simply point CMake to the root directory to generate project files 
for the samples.  Several options for building are documented within CMake itself.


    fcSample       - Shows several simple examples of fc usage.
    fcSampleString - Shows some examples involving string parsing and manipulation. 
                     Patterned after a Haskell example seen recently.
    fcExperimental - Shows "nested" function composition.  
                     That is, given functions f,g,h, produced a composed function c = f(g(),h()).
