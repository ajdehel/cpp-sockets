
#include "UDPServer.h"

#include <utility>

/******************************************************************************/
UDPServer::UDPServer( )
  : _sock{nullptr}
{
  _sock = new UDPSocket( );
}

/******************************************************************************/
UDPServer::UDPServer( UDPSocket&& socket )
  : _sock{nullptr}
{
  _sock = new UDPSocket( std::move(socket) );
}

/******************************************************************************/
UDPServer::~UDPServer()
{
  if (nullptr != _sock)
  {
    _sock->Close();
    delete _sock;
  }
}

/******************************************************************************/
bool UDPServer::Bind( int port )
{
  return _sock->Bind( port );
}

/******************************************************************************/
bool UDPServer::Sendto( const std::vector<uint8_t> &data,
                        const std::string &address, const int port,
                        bool blocks )
{
  std::vector<Msgflag_E> flags;
  if (!blocks)
    flags.push_back(Msgflag_E::dont_wait);
  return _sock->Sendto( data, address, port, flags );
}

/******************************************************************************/
bool UDPServer::Recvfrom( std::vector<uint8_t> &data,
                          std::string &address, int &port,
                          bool blocks )
{
  std::vector<Msgflag_E> flags;
  if (!blocks)
    flags.push_back(Msgflag_E::dont_wait);
  return _sock->Recvfrom( data, address, port, flags );
}


