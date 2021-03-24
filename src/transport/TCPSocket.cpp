
#include "TCPSocket.h"

#include <iostream>

#include <cstring>

/******************************************************************************/
TCPSocket::TCPSocket()
  : Socket(Domain_E::inet, Type_E::stream, Protocol_E::Default)
{ }

/******************************************************************************/
TCPSocket::TCPSocket( TCPSocket&& sock)
  : Socket(std::move(sock))
{
}

/******************************************************************************/
TCPSocket::TCPSocket( Socket&& sock)
  : Socket(std::move(sock))
{
}

/******************************************************************************/
TCPSocket::TCPSocket( int fd )
  : Socket(fd)
{ }

/******************************************************************************/
TCPSocket::~TCPSocket()
{
  Close();
}

/******************************************************************************/
bool TCPSocket::Bind( int port )
{
  sockaddr_in servaddr;
  std::memset( &servaddr, 0, sizeof(servaddr) );
  servaddr.sin_family      = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port        = htons(port);
  return Socket::Bind( (sockaddr*)&servaddr, sizeof(servaddr) );
}

/******************************************************************************/
bool TCPSocket::Connect( std::string address, int port )
{
  sockaddr_in connaddr;
  in_addr inet_address;
  if ( 0 == inet_aton(address.c_str(), &inet_address) )
    return false;
  connaddr.sin_family      = AF_INET;
  connaddr.sin_addr.s_addr = inet_address.s_addr;
  connaddr.sin_port        = htons(port);
  return Socket::Connect( (sockaddr*)&connaddr, sizeof(connaddr) );
}

/******************************************************************************/
TCPSocket TCPSocket::Accept( void )
{
  sockaddr_in client;
  socklen_t len = sizeof(client);
  TCPSocket connsock( Socket::Accept((sockaddr*)&client, &len) );
  connsock.set_bound_port( ntohs(client.sin_port) );
  return connsock;
}

/******************************************************************************/
bool TCPSocket::Send( std::vector<uint8_t> &buffer, const std::vector<Msgflag_E> &flags )
{
  int bytes = Socket::Send( buffer.data(), buffer.size(), flags );
  return 0 <= bytes;
}

/******************************************************************************/
bool TCPSocket::Recv( std::vector<uint8_t> &buffer, const std::vector<Msgflag_E> &flags )
{
  buffer.resize(buffer.capacity());
  int bytes = Socket::Recv( buffer.data(), buffer.capacity(), flags );
  if (0 > bytes)
  {
    buffer.resize(0);
    return false;
  }
  else
  {
    buffer.resize( bytes );
    return true;
  }
}

