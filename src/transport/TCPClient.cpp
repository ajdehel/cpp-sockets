
#include "TCPClient.h"

/******************************************************************************/
TCPClient::TCPClient( )
 : _sock{nullptr}
{
  _sock = new TCPSocket();
}

/******************************************************************************/
TCPClient::~TCPClient( )
{
  if (nullptr != _sock)
  {
    _sock->Close();
    delete _sock;
  }
}

/******************************************************************************/
bool TCPClient::Connect( std::string address, int port )
{
  return _sock->Connect( address, port );
}

/******************************************************************************/
bool TCPClient::Send( std::vector<uint8_t>& data, bool blocks )
{
  std::vector<Msgflag_E> flags;
  if (!blocks)
    flags.push_back(Msgflag_E::dont_wait);
  return _sock->Send( data, flags );
}

/******************************************************************************/
bool TCPClient::Recv( std::vector<uint8_t>& data, bool blocks )
{
  std::vector<Msgflag_E> flags;
  if (!blocks)
    flags.push_back(Msgflag_E::dont_wait);
  return _sock->Recv( data, flags );
}

