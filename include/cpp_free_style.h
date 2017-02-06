// cpp_free_style.h   william k. johnson  2017


#pragma once

// c++ standard
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include <tuple>
#include <exception>
#include <stdexcept>
#include <system_error>
#include <future>
#include <mutex>
#include <deque>
#include <type_traits>
#include <typeinfo>

// c runtime
#include <cassert>
// boost
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>



namespace cpp_free_style
{

                //forward declarations
                //
                class atomic_schema;
                //abstract factory
                class atomic_message;
                //factory
                class atomic_message_factory;
                //protoype factory
                class atomic_message_proto_factory;
                //sentinel
                class sentinel_message;
                //immutable
                static std::string time_stamp()
                {
                    std::ostringstream ostr;
                    boost::posix_time::time_facet *facet =
                         new boost::posix_time::time_facet( "%d-%b-%Y %H:%M:%S" );
                    ostr.imbue( std::locale( ostr.getloc() , facet ) );
                    ostr << boost::posix_time::second_clock::local_time();

                    return ostr.str();
                }
                //
}
