#pragma once

#include "Socket.h"

#include <string>
#include <vector>

class UDPSocket : public Socket
{
  public:
    UDPSocket();
    ~UDPSocket();
    UDPSocket( const UDPSocket& ) = delete;
    UDPSocket( UDPSocket&& );
    UDPSocket( Socket&& );

    bool operator=( UDPSocket&& );

    bool Bind( int );

    bool Sendto( std::vector<uint8_t>&, const std::string &, const int & );
    bool Sendto( std::vector<uint8_t>&,
                 const std::string &, const int &,
                 const std::vector<Msgflag_E>& );

    bool Recvfrom( std::vector<uint8_t>&, std::string &, int & );
    bool Recvfrom( std::vector<uint8_t>&,
                   std::string &, int &,
                   const std::vector<Msgflag_E>& );

  private:
    UDPSocket( int fd );

};
