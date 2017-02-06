# cpp_free_style   william k. johnson 2016

cmake_minimum_required(VERSION 2.8)
#project
project(cppfreestyle)

#cpp flags
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -g -rdynamic -O0  -Qunused-arguments  -DDEBUG -std=c++14")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -O3  -rdynamic -Qunused-arguments  -DNDEBUG -std=c++14")

#includes
include_directories( ${cppfreestyle_SOURCE_DIR}
                     $ENV{DEV}/include
                     ./include
                   )
#link location
link_directories( /cci/dev_t/lib)

#binary
add_executable( cpp_free_style cpp_free_style.cpp )

#link
target_link_libraries(cpp_free_style -lboost_system -lboost_thread  -lpthread)



