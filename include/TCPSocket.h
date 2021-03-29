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

    bool operator=( TCPSocket&& );

    bool Bind( int );
    bool Listen( int backlog );
    bool Connect( std::string, int );
    TCPSocket Accept( void );

    bool Send( const std::vector<uint8_t>&, const std::vector<Msgflag_E>& );
    bool Recv( std::vector<uint8_t>&, const std::vector<Msgflag_E>& );

  private:
    TCPSocket( Socket&& );
    TCPSocket( int fd );

};
