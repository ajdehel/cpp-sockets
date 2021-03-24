#pragma once

#include "Socket.h"

#include <string>
#include <vector>

class TCPSocket : public Socket
{
  public:
    TCPSocket();
    ~TCPSocket();
    TCPSocket( const TCPSocket& ) = delete;
    TCPSocket( TCPSocket&& );
    TCPSocket( Socket&& );

    bool operator=( TCPSocket&& );

    bool Bind( int );
    bool Connect( std::string, int );
    TCPSocket Accept( void );

    bool Send( std::vector<uint8_t>& );
    bool Send( std::vector<uint8_t>&, const std::vector<Msgflag_E>& );

    bool Recv( std::vector<uint8_t>& );
    bool Recv( std::vector<uint8_t>&, const std::vector<Msgflag_E>& );

  private:
    TCPSocket( int fd );

};
