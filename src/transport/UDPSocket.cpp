
#include "UDPSocket.h"

#include <cstring>

/******************************************************************************/
UDPSocket::UDPSocket()
  : Socket(Domain_E::inet, Type_E::dgram, Protocol_E::Default)
{ }

/******************************************************************************/
UDPSocket::UDPSocket( UDPSocket&& sock)
  : Socket(std::move(sock))
{
}

/******************************************************************************/
UDPSocket::UDPSocket( Socket&& sock)
  : Socket(std::move(sock))
{
}

/******************************************************************************/
UDPSocket::UDPSocket( int fd )
  : Socket(fd)
{ }

/******************************************************************************/
UDPSocket::~UDPSocket()
{
  Close();
}

/******************************************************************************/
bool UDPSocket::Bind( int port )
{
  sockaddr_in servaddr;
  std::memset( &servaddr, 0, sizeof(servaddr) );
  servaddr.sin_family      = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port        = htons(port);
  return Socket::Bind( (sockaddr*)&servaddr, sizeof(servaddr) );
}

/******************************************************************************/
bool UDPSocket::Sendto( const std::vector<uint8_t> &buffer,
                        const std::string &address, const int &port,
                        const std::vector<Msgflag_E>& flags )
{
  sockaddr_in dst_addr;
  in_addr inet_address;
  if ( 0 == inet_aton(address.c_str(), &inet_address) )
    return false;
  dst_addr.sin_family      = AF_INET;
  dst_addr.sin_addr.s_addr = inet_address.s_addr;
  dst_addr.sin_port        = htons(port);
  return Socket::Sendto( buffer.data(), buffer.capacity(),
                         (sockaddr*)&dst_addr, sizeof(dst_addr),
                         flags );
}

/******************************************************************************/
bool UDPSocket::Recvfrom( std::vector<uint8_t> &buffer, std::string &address, int &port,
               const std::vector<Msgflag_E>& flags )
{
  buffer.resize(buffer.capacity());
  sockaddr_in dst_addr;
  socklen_t dst_len;
  int bytes = Socket::Recvfrom( buffer.data(), buffer.capacity(),
                                (sockaddr*)&dst_addr, &dst_len,
                                flags);
  if ( 0 > bytes )
  {
    buffer.resize(0);
    return false;
  }
  else
  {
    std::string tmp (inet_ntoa(dst_addr.sin_addr));
    address.swap( tmp );
    port = ntohs( dst_addr.sin_port );
    return true;
  }
}

