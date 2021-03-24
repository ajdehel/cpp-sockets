
#include "TCPServer.h"

#include <utility>

/******************************************************************************/
TCPServer::TCPServer( )
  : _conn_sock{nullptr}
  , _recv_sock{nullptr}
{
  _recv_sock = new TCPSocket( );
}

/******************************************************************************/
TCPServer::TCPServer( TCPSocket&& socket )
  : _conn_sock{nullptr}
  , _recv_sock{nullptr}
{
  _recv_sock = new TCPSocket( std::move(socket) );
}

/******************************************************************************/
TCPServer::~TCPServer()
{
  if (nullptr != _recv_sock)
  {
    _recv_sock->Close();
    delete _recv_sock;
  }
  if (nullptr != _conn_sock)
  {
    _conn_sock->Close();
    delete _conn_sock;
  }
}

/******************************************************************************/
bool TCPServer::Listen( void )
{
  return _recv_sock->Listen( 5 );
}

/******************************************************************************/
bool TCPServer::Bind( int port )
{
  return _recv_sock->Bind( port );
}

/******************************************************************************/
bool TCPServer::Accept( void )
{
  _conn_sock = new TCPSocket( _recv_sock->Accept() );
  return _conn_sock->get_fd() > 0;
}

/******************************************************************************/
bool TCPServer::Send( std::vector<uint8_t>& data, bool blocks )
{
  std::vector<Msgflag_E> flags;
  if (!blocks)
    flags.push_back(Msgflag_E::dont_wait);
  return _conn_sock->Send( data, flags );
}

/******************************************************************************/
bool TCPServer::Recv( std::vector<uint8_t>& data, bool blocks )
{
  std::vector<Msgflag_E> flags;
  if (!blocks)
    flags.push_back(Msgflag_E::dont_wait);
  return _conn_sock->Recv( data, flags );
}


