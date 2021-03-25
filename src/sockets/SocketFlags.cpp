
#include "SocketFlags.h"

/******************************************************************************/
template<class T>
int to_int ( std::vector<T> flags )
{
  int flags_ = 0;
  for ( T flag : flags )
  {
    flags_ |= static_cast<int>(flag);
  }
  return flags_;
}
template int to_int<Type_E>( std::vector<Type_E> flags );
template int to_int<Protocol_E>( std::vector<Protocol_E> flags );
template int to_int<Sockopt_E>( std::vector<Sockopt_E> flags );
template int to_int<Msgflag_E>( std::vector<Msgflag_E> flags );

/******************************************************************************/
template<class T>
std::vector<T> to_vector ( int flags )
{
  std::vector<T> flags_;
  for ( unsigned int i_flag = 1; i_flag < (1 << 31); i_flag <<= 1 )
  {
    flags_.push_back( static_cast<T>(i_flag & flags) );
  }
  return flags_;
}
template std::vector<Type_E> to_vector<Type_E>( int flags );
template std::vector<Protocol_E> to_vector<Protocol_E>( int flags );
template std::vector<Sockopt_E> to_vector<Sockopt_E>( int flags );
template std::vector<Msgflag_E> to_vector<Msgflag_E>( int flags );
