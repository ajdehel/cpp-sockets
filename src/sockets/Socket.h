#pragma once

#include "SocketFlags.h"

#include <string>
#include <vector>

#include <arpa/inet.h>
#include <sys/socket.h>

class Socket
{
  public:
    Socket( Domain_E, Type_E, Protocol_E );
    ~Socket();
    Socket( const Socket& ) = delete;
    Socket( Socket&& );

    bool operator=( Socket&& );

    bool Close( void );
    bool Listen( int backlog );

    const int  get_fd() const;
    const int  get_bound_port() const;
    const bool is_bound() const;
    const bool is_open() const;

  protected:
    Socket( int fd );
    void set_bound_port( int );

    bool Bind( sockaddr *addr, socklen_t len );
    bool Connect( sockaddr *addr, socklen_t len );
    Socket Accept( sockaddr *addr, socklen_t *len );

    int Send( const void *buf, size_t len, const std::vector<Msgflag_E>& );
    int Sendto( const void *buf, size_t len, const sockaddr *, socklen_t, const std::vector<Msgflag_E>& );

    int Recv( void *buf, size_t len, const std::vector<Msgflag_E>& );
    int Recvfrom( void *buf, size_t len, sockaddr *, socklen_t *, const std::vector<Msgflag_E>& );

  private:
    int  _fd;
    int  _bound_port;
    bool _opened, _closed;

};
