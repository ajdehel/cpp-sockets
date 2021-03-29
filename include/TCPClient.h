#pragma once

#include "TCPSocket.h"

#include <vector>

#include <cstdint>

class TCPClient
{
  public:
    TCPClient();
    ~TCPClient();
    TCPClient( TCPClient&& );
    bool Connect( std::string, int );
    bool Send( std::vector<uint8_t>&, bool blocks=true );
    bool Recv( std::vector<uint8_t>&, bool blocks=true );

  private:
    TCPSocket *_sock;

};

