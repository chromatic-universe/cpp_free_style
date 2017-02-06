// cpp_free_style.cpp      william k. johnson 2016


#include <cpp_create_style.h>
#include <cpp_adapter_style.h>


using namespace cppfs;

unsigned clone_limit = 3L;




int main( int argc , char* argv[] )
{

          std::cerr << time_stamp()
                    << "....cpp free style....william k. johnson...2016"
                    << "\n";

          try
          {
                //abstract factory
                /*
                std::cerr << time_stamp()
                          << "...abstract factory...\n";
                auto sc = std::make_unique<sentinel_schema>( "sentinel_schema" );
                auto sentinel = std::make_unique<sentinel_message>( sc.get() );
                std::cerr << time_stamp()
                          << "...sentinel schema returned: "
                          << sentinel->schema()->describe()
                          << "\n";
                //factory
                std::cerr << time_stamp()
                          << "...factory...\n";
                auto sm_factory = std::make_unique<message_factory<sentinel_message,
                                                                   std::vector<sentinel_message>>>( sc.get() );
                //clone prototype + singleton + double checked lock
                std::cerr << time_stamp()
                          << "...clone prototype...\n";
                ///returns smart pointer
                */
                const std::string sentinel_moniker( "sentinel_message" );
                sentinel_message* s = new sentinel_message();
                std::cerr << time_stamp()
                          << "..."
                          << typeid( s ).name()
                          << "\n";

                sentinel_schema scc( "...sentinel schema speaking..." );
                atomic_message_proto_factory::instance()->register_message<sentinel_message>( sentinel_moniker );
                atomic_message_proto_factory::instance()->register_message<sentinel_message>( sentinel_moniker );
                auto msg = atomic_message_proto_factory::instance()->gen_prototype( sentinel_moniker ,
                                                                                    &scc );
                if( msg )
                {
                    std::cerr << time_stamp()
                              << "...sentinel message cloned by decltype...\n"
                              << time_stamp();
                    msg->reflect();
                }

                //enum registrations
                std::cerr << time_stamp();
                atomic_message_proto_factory::instance()->enum_registered_messages( std::cerr );


            }
            catch( const std::exception& err )
            {
                std::cerr << err.what()
                          << "\n";
            }

            atomic_message_proto_factory::dispose_instance();



}
