// cpp_createstyle.h   william k. johnson  2016


#pragma once

#include <cpp_free_style.h>


namespace cpp_free_style
{

                static unsigned clone_limit;


                //enumerations
                enum class message_prototype : size_t {
                                                            mc_sentinel ,
                                                            mc_tag
                                                      };


                //types


                //aliases
                //
                using asc_ptr = atomic_schema*;
                using amsg_ptr = std::unique_ptr<atomic_message>;
                using amsg_factory_ptr = atomic_message_factory*;
                using amsg_proto_factory_ptr = atomic_message_proto_factory*;
                using atomic_msg_ptr = atomic_message*;
                using sentinel_msg_ptr = sentinel_message*;
                using msg_deq = std::deque<amsg_ptr>;
                using msg_deq_ptr = msg_deq*;
                using msg_ticker = std::map<message_prototype,unsigned>;
                using msg_ticker_ptr = msg_ticker*;
                using msg_prototypes = std::map<std::string,amsg_ptr>;



                //services
                //--------------------------------------------------------------------------
                class atomic_message
                {

                        public :

                            virtual void reflect() = 0;
                            virtual amsg_ptr clone() = 0;
                            virtual ~atomic_message() = 0;
                            virtual asc_ptr schema() = 0;
                            virtual void schema( asc_ptr asc ) = 0;

                };

                atomic_message::~atomic_message() {}
                //--------------------------------------------------------------------------

                class atomic_schema
                {

                        public :

                            virtual std::string describe() = 0;
                            virtual ~atomic_schema() = 0;

                };
                atomic_schema::~atomic_schema() {}
                //--------------------------------------------------------------------------
                class atomic_message_factory
                {


                        public :

                            virtual void spawn_message() = 0;
                            virtual void spawn_message_n( const unsigned gen_num ) = 0;
                            virtual ~atomic_message_factory() = 0;

                };
                atomic_message_factory::~atomic_message_factory() {}
                //--------------------------------------------------------------------------
                class sentinel_schema : public atomic_schema
                {


                        public :

                             //ctors
                             sentinel_schema() : m_str_description( "sentinel schema" )
                             {}

                             explicit sentinel_schema( const std::string& descr ) : m_str_description { descr } ,
                                                                                    m_dw_id { 0L }
                             {
                                    std::cerr << time_stamp()
                                              << "...sentinel schema contructor.."
                                              << "\n";


                            }

                            //dtor
                            virtual ~sentinel_schema()

                            {}



                        private :

                            //attributes
                            std::string  m_str_description;
                            unsigned     m_dw_id;


                        public:



                            //accessors-inspectors
                            std::string description() const noexcept { return m_str_description; }
                            unsigned id() const noexcept { return m_dw_id; }

                            //mutators
                            void description( const std::string& desc ) { m_str_description = desc; }
                            void id( const unsigned id_ ) { m_dw_id = id_; }

                            //services
                            std::string describe()
                            {
                                return description();
                            }


                };
                //--------------------------------------------------------------------------
                class sentinel_message : public atomic_message
                {

                        public :

                            //ctor
                            sentinel_message()
                            {}
                            sentinel_message( asc_ptr schema_atom ) :
                                               m_schema_atom( schema_atom )
                            {
                                assert( schema_atom );
                                std::cerr << time_stamp()

                                          << "...sentinel message contructor.."
                                          << "\n";
                            }



                            //dtor
                            virtual ~sentinel_message() = default;



                        private :

                            asc_ptr m_schema_atom;


                        public :


                            //accessors-inspectors
                            asc_ptr schema() { return m_schema_atom; }

                            //mutators
                            void schema( asc_ptr asc ) { m_schema_atom = asc; }

                            //services
                            void reflect()
                            {
                                assert( m_schema_atom );
                                std::cerr << m_schema_atom->describe()
                                          << "\n";
                            }

                            amsg_ptr clone()

                            {
                                return std::make_unique<sentinel_message>( m_schema_atom );
                            }

                };
                //--------------------------------------------------------------------------
                class tag_message : public atomic_message
                {

                        public :

                            //ctor
                            tag_message()
                            {}
                            tag_message( asc_ptr schema_atom ) :
                                               m_schema_atom( schema_atom )
                            {
                                assert( schema_atom );
                                std::cerr << time_stamp()

                                          << "...sentinel message contructor.."
                                          << "\n";
                            }



                            //dtor
                            virtual ~tag_message() = default;



                        private :

                            asc_ptr m_schema_atom;


                        public :


                            //accessors-inspectors
                            asc_ptr schema() { return m_schema_atom; }

                            //mutators
                            void schema( asc_ptr asc ) { m_schema_atom = asc; }

                            //services
                            void reflect()
                            {
                                assert( m_schema_atom );
                                std::cerr << m_schema_atom->describe()
                                          << "\n";
                            }

                            amsg_ptr clone()

                            {
                                return std::make_unique<tag_message>( m_schema_atom );
                            }

                };

                //--------------------------------------------------------------------------
                template<typename message , typename T>
                class message_factory
                {

                         public :


                            //ctor
                            message_factory( asc_ptr schema_atom ,
                                             unsigned count = 0L
                                           ) : m_schema_atom{ schema_atom } ,
                                               m_internal_count{ count } ,
                                               m_dq( new T )
                            {
                                assert( schema_atom );
                                std::cerr << time_stamp()
                                          << "...sentinel message factory constructor.."

                                          << "\n";
                            }



                            //dtor )
                            virtual ~message_factory() = default;

                            //no copy
                            message_factory( const message_factory& factory ) = delete;
                            //no assign
                            const message_factory& operator= ( const message_factory& factory ) = delete;


                         private :

                            asc_ptr                              m_schema_atom;
                            unsigned                             m_internal_count;
                            std::unique_ptr<T>                   m_dq;



                         public :

                            //accessors-inspectors
                            asc_ptr schema() { return m_schema_atom; }
                            unsigned internal_count() noexcept { return m_internal_count; }



                            //mutators
                            void schema( asc_ptr asc ) { m_schema_atom = asc; }


                            //services
                            ///internal storage
                            void spawn_message()
                            {
                                 std::cerr << time_stamp()
                                           << "...message factory spawn_message.."
                                           << "\n";
                                 auto msg = std::make_unique<message>( m_schema_atom );
                                 m_dq->emplace_back( std::move( msg ) ) ;

                            }


                            ///internal storage
                            void spawn_message_n( const unsigned gen_num )
                            {
                                 std::cerr << time_stamp()
                                           << "...message factory spawn_message.."
                                           << "\n";

                                 spawn_message_n( gen_num , m_dq.get() );
                            }


                            ///external storage
                            void spawn_message_n( const unsigned gen_num , T* sink )
                            {
                                assert( gen_num );
                                unsigned dw_gen{ gen_num };

                                std::cerr << time_stamp()
                                          << "...message factory spawning "
                                          << gen_num
                                          << " messages.."
                                          << "\n";

                                do
                                {
                                    auto msg = std::make_unique<message>( m_schema_atom );
                                    sink->push_back( msg  );

                                    dw_gen--;

                                } while( dw_gen );
                            }


                };

                //-------------------------------------------------------------------------
                typedef std::map<std::string,amsg_ptr (*)()> msg_map;


                //msg instance
                template<typename T>
                amsg_ptr create_msg_instance() { return std::make_unique<T>(); }


                //--------------------------------------------------------------------------
                class atomic_message_proto_factory
                {

                        public :


                            //instance
                            static amsg_proto_factory_ptr  instance()

                            {
                                //double checked lock
                                if( ! m_instance )
                                {
                                    std::lock_guard<std::mutex> lg( m_mutex );
                                    if( ! m_instance )
                                    {  m_instance = new atomic_message_proto_factory(); }
                                }

                                return  m_instance;
                            }
                            //dispose instance
                            static void dispose_instance()
                            {
                                delete m_instance;
                                m_instance = nullptr;
                            }

                             //dtor
                            ~atomic_message_proto_factory() = default;

                            //no copy
                            atomic_message_proto_factory( const  atomic_message_proto_factory& ampf ) = delete;
                            //no assign
                            atomic_message_proto_factory& operator=( const atomic_message_proto_factory& ampf ) = delete;



                        private :

                            //attributes
                            static amsg_proto_factory_ptr      m_instance;
                            static std::mutex                  m_mutex;
                            static msg_map                     mm;
                            msg_prototypes                     m_prototypes;


                            //singleton ctor
                            atomic_message_proto_factory()
                            {}


                        public :


                            //acce )ors-inspectors
                            static msg_map& prototypes() { return mm; }

                            //services
                            amsg_ptr gen_prototype( const std::string& selection )
                            {
                                return m_prototypes[selection]->clone();
                            }

                            amsg_ptr gen_prototype( const std::string& selection , asc_ptr schema )
                            {
                                auto msg = m_prototypes[selection]->clone();
                                if( msg ) { msg->schema( schema ); }

                                return msg;
                            }


                            //register message
                            template<typename T>
                            void register_message( const std::string& moniker )
                            {
                                //map of reference constructors - if exists is noop
                                mm[moniker] = &create_msg_instance<T>;
                                //map of registered reference instances
                                m_prototypes[moniker] = mm[moniker]();
                            }

                            void enum_registered_messages( std::ostream& ostr )
                            {
                                ostr << "... message registrations("
                                     << m_prototypes.size()
                                     << "):\n";
                                for( auto& protos : m_prototypes )
                                {
                                     ostr << "\t\t"
                                          << protos.first
                                          << "\n";
                                }
                            }



                };
                amsg_proto_factory_ptr atomic_message_proto_factory::m_instance;
                std::mutex atomic_message_proto_factory::m_mutex;
                msg_map atomic_message_proto_factory::mm;
                //--------------------------------------------------------------------------
                class atomic_message_pool
                {

                        public :

                            //ctors
                            explicit atomic_message_pool( const size_t limit_sz = 0L ) : m_deq( new msg_deq ) ,
                                                                                         m_ticker( new msg_ticker ) ,
                                                                                         m_sz { limit_sz }
                            {}
                            //dtor
                            virtual ~atomic_message_pool() = default;


                        private :

                            //attributes
                            std::unique_ptr<msg_deq>        m_deq;
                            std::unique_ptr<msg_ticker>     m_ticker;
                            size_t                          m_sz;


                        public :

                            //accessors-inspectors
                            const msg_deq_ptr dq() const noexcept { return m_deq.get(); }
                            const msg_ticker_ptr ticker() const noexcept { return m_ticker.get(); }


                            //services
                            template<typename T , typename T2>
                            void gen_messages( T msg_type , T2* schema ,  const unsigned batch )
                            {
                                if( batch > m_sz ) { return; }


                                auto factory = std::make_unique<message_factory<T,msg_deq>>( schema );
                                factory->spawn_message_n( batch , m_deq.get() );

                            }





                };



}
namespace cppfs = cpp_free_style;


