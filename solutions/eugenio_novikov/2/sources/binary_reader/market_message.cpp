#include "market_message.h"
#include <cstring>

binary_reader::market_message::market_message( std::ifstream& in )
	: msg_( NULL )
{
	in.read( reinterpret_cast< char* >( &type_ ), sizeof( type_ ) );
	in.read( reinterpret_cast< char* >( &time_ ), sizeof( time_ ) );
	in.read( reinterpret_cast< char* >( &len_ ), sizeof( len_ ) );
	msg_ = new char[ len_ ];
	in.read( msg_, len_ );
}


binary_reader::market_message::market_message( const boost::uint32_t type, const boost::uint32_t time, const char* const msg )
: type_ ( type )
, time_( time )
{
	len_ = static_cast< boost::uint32_t >( strlen( msg ) );
	msg_ = new char[ len_ ];
	memcpy( msg_, msg, len_ );
}


void binary_reader::market_message::write( std::ofstream& out ) const
{
    boost::uint32_t type_copy_ = type_;
    boost::uint32_t time_copy_ = time_;
    boost::uint32_t len_copy_ = len_;
    
	out.write( reinterpret_cast< char* >( &type_copy_ ), sizeof( type_copy_ ) );
	out.write( reinterpret_cast< char* >( &time_copy_ ), sizeof( time_copy_ ) );
	out.write( reinterpret_cast< char* >( &len_copy_ ), sizeof( len_copy_ ) );
	out.write( msg_, len_ );
}


binary_reader::market_message::~market_message()
{
	delete [] msg_;
}


boost::uint32_t binary_reader::market_message::type() const
{
	return type_;
}


boost::uint32_t binary_reader::market_message::time() const
{
	return time_;
}


boost::uint32_t binary_reader::market_message::messageSize() const
{
	return  (3 * sizeof(boost::uint32_t) + len_ * sizeof(char));
}


const char* const binary_reader::market_message::msg() const
{
	return msg_;
}
