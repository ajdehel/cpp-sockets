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

    bool Sendto( const std::vector<uint8_t>&,
                 const std::string&, const int,
                 bool blocks=true );
    bool Recvfrom( std::vector<uint8_t>&,
                   std::string&, int&,
                   bool blocks=true );

  private:
    UDPSocket *_sock;

};

