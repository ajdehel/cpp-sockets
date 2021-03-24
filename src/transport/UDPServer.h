#pragma once

#include "UDPSocket.h"

#include <vector>

#include <cstdint>

class UDPServer
{
  public:
    UDPServer();
    ~UDPServer();
    UDPServer( UDPSocket&& );
    bool Bind( int );
    bool Send( std::vector<uint8_t>&, bool blocks=true );
    bool Recv( std::vector<uint8_t>&, bool blocks=true );

  private:
    UDPSocket *_sock;

};

