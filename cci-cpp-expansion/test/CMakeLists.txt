#cmake cpp_expansion william k. johnson 2016

#version
cmake_minimum_required(VERSION 2.82)
#project
project(CPPEXPANSION)

#cpp flags
set(CMAKE_CXX_FLAGS_DEBUG "-fPIC -Wall -g -O0  -Qunused-arguments  -DDEBUG -std=c++14")
set(CMAKE_CXX_FLAGS_RELEASE "-fPIC -Wall -O3  -Qunused-arguments  -DNDEBUG -std=c++14")

link_directories(${CPPEXPANSION_SOURCE_DIR}
                    $ENV{DEV}/lib
                    $ENV{DEV}/lib/cci)

#includes
include_directories(../../include
    $ENV{DEV}/include)

#executable
#add_executable(cci_exp_test_run  test_cci_numeric_utils.cpp
#                                 ../cci_complexity.cpp
#                                 ../cci_concurrent_impl.cpp)

#link libs
#target_link_libraries(cci_exp_test_run -lpthread -lgtest -lgtest_main)


