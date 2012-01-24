add_executable(fcSample sample.cpp)
add_executable(fcSampleString sample_string.cpp)
add_executable(fcSampleThreaded sample_threaded.cpp)

if(ENABLE_EXPERIMENTAL_FC)
  add_executable(fcExperimental sample_experimental.cpp)
endif()
