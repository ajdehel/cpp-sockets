
#include "UDPClient.h"

#include <utility>

/******************************************************************************/
UDPClient::UDPClient( )
  : _sock{nullptr}
{
  _sock = new UDPSocket( );
}

/******************************************************************************/
UDPClient::UDPClient( UDPSocket&& socket )
  : _sock{nullptr}
{
  _sock = new UDPSocket( std::move(socket) );
}

/******************************************************************************/
UDPClient::~UDPClient()
{
  if (nullptr != _sock)
  {
    _sock->Close();
    delete _sock;
  }
}

/******************************************************************************/
bool UDPClient::Sendto( const std::vector<uint8_t> &data,
                        const std::string &address, const int port,
                        bool blocks )
{
  std::vector<Msgflag_E> flags;
  if (!blocks)
    flags.push_back(Msgflag_E::dont_wait);
  return _sock->Sendto( data, address, port, flags );
}

/******************************************************************************/
bool UDPClient::Recvfrom( std::vector<uint8_t> &data,
                          std::string &address, int &port,
                          bool blocks )
{
  std::vector<Msgflag_E> flags;
  if (!blocks)
    flags.push_back(Msgflag_E::dont_wait);
  return _sock->Recvfrom( data, address, port, flags );
}


