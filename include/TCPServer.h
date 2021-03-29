#pragma once

#include "TCPSocket.h"

#include <vector>

#include <cstdint>

class TCPServer
{
  public:
    TCPServer();
    ~TCPServer();
    TCPServer( TCPSocket&& );
    bool Bind( int );
    bool Listen();
    bool Accept();
    bool Send( std::vector<uint8_t>&, bool blocks=true );
    bool Recv( std::vector<uint8_t>&, bool blocks=true );

  private:
    TCPSocket *_recv_sock;
    TCPSocket *_conn_sock;

};

