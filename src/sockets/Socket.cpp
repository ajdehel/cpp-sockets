
#include "Socket.h"

#include <iostream>
#include <system_error>

#include <cerrno>

#include <unistd.h>

/******************************************************************************/
Socket::Socket( Domain_E domain, Type_E type, Protocol_E protocol )
  : _opened{false}
  , _closed{false}
  , _bound_port{-1}
  , _fd{-1}
{
  int domain_   = static_cast<int>(domain);
  int type_     = static_cast<int>(type);
  int protocol_ = static_cast<int>(protocol);
  _fd = socket(domain_, type_, protocol_);
  if (-1 == _fd)
    throw std::system_error(std::error_code(errno, std::system_category()));
  _opened = true;
}

/******************************************************************************/
Socket::Socket( Socket&& sock )
  : _opened{false}
  , _closed{false}
  , _bound_port{-1}
  , _fd{-1}
{
  if (_fd > 0)
    throw std::system_error(std::make_error_code(std::errc::connection_already_in_progress));
  _fd = sock.get_fd();
  if (-1 == _fd)
    throw std::system_error(std::error_code(errno, std::system_category()));
  _opened = true;
  sock._fd = 0;
  sock._closed = true;
}

/******************************************************************************/
Socket::Socket( int fd )
  : _opened{true}
  , _closed{false}
  , _bound_port{-1}
  , _fd{fd}
{ }

/******************************************************************************/
bool Socket::operator=( Socket&& sock)
{
  if (_fd > 0)
    throw std::system_error(std::make_error_code(std::errc::connection_already_in_progress));
  _fd = sock.get_fd();
  if (-1 == _fd)
    throw std::system_error(std::error_code(errno, std::system_category()));
  _opened = true;
  sock._fd = 0;
  sock._closed = true;
}

/******************************************************************************/
Socket::~Socket()
{
  Close();
}

/******************************************************************************/
bool Socket::Close( void )
{
  if (_opened)
  {
    if (_closed)
    {
      return true;
    }
    if (-1 == close(_fd))
    {
      throw std::system_error(std::error_code(errno, std::system_category()));
    }
    else
    {
      _closed = true;
    }
    return _closed;
  }
  else
  {
    return false;
  }
}

/******************************************************************************/
bool Socket::Bind( sockaddr *addr, socklen_t len )
{
  if ( 0 != bind(_fd, addr, len) )
    throw std::system_error(std::error_code(errno, std::system_category()));
  return true;
}

/******************************************************************************/
bool Socket::Listen( int backlog )
{
  if ( 0 != listen(_fd, backlog) )
    throw std::system_error(std::error_code(errno, std::system_category()));
  return true;
}

/******************************************************************************/
bool Socket::Connect( sockaddr *addr, socklen_t len )
{
  if ( 0 != connect(_fd, addr, len) )
    throw std::system_error(std::error_code(errno, std::system_category()));
  return true;
}

/******************************************************************************/
Socket Socket::Accept( sockaddr *addr, socklen_t *len )
{
  int connfd = accept(_fd, addr, len);
  if ( -1 == connfd )
    throw std::system_error(std::error_code(errno, std::system_category()));
  Socket connsock( connfd );
  return connsock;
}

/******************************************************************************/
int Socket::Send( const void *buf, const size_t len,
                  const std::vector<Msgflag_E> &flags )
{
  int flags_ = to_int<Msgflag_E>(flags);
  int bytes = send(_fd, buf, len, flags_);
  if (0 > bytes)
  {
    std::errc ec = static_cast<std::errc>(errno);
    std::error_code error = std::make_error_code( ec );
    switch ( ec )
    {
      case std::errc::resource_unavailable_try_again :
        break;
      default :
        throw std::system_error(error);
    }
  }
  std::cout << bytes << std::endl;
  return bytes;
}

/******************************************************************************/
int Socket::Sendto( const void *buf, size_t len,
                    const sockaddr *addr, socklen_t addr_len,
                    const std::vector<Msgflag_E>& flags)
{
  int flags_ = to_int<Msgflag_E>( flags );
  int bytes = sendto( _fd, buf, len, flags_, addr, addr_len );
  if (0 > bytes)
  {
    std::errc ec = static_cast<std::errc>(errno);
    std::error_code error = std::make_error_code( ec );
    switch ( ec )
    {
      case std::errc::resource_unavailable_try_again :
        break;
      default :
        throw std::system_error(error);
    }
  }
  return bytes;
}

/******************************************************************************/
int Socket::Recv( void *buf, size_t len, const std::vector<Msgflag_E> &flags )
{
  int flags_ = to_int<Msgflag_E>(flags);
  int bytes = recv(_fd, buf, len, flags_);
  if (0 > bytes)
  {
    std::errc ec = static_cast<std::errc>(errno);
    std::error_code error = std::make_error_code( ec );
    switch ( ec )
    {
      case std::errc::resource_unavailable_try_again :
        break;
      default :
        throw std::system_error(error);
    }
  }
  return bytes;
}

/******************************************************************************/
int Socket::Recvfrom( void *buf, size_t len,
                      sockaddr *addr, socklen_t *addr_len,
                      const std::vector<Msgflag_E> &flags )
{
  int flags_ = to_int<Msgflag_E>(flags);
  int bytes = recv(_fd, buf, len, flags_);
  if (0 > bytes)
  {
    std::errc ec = static_cast<std::errc>(errno);
    std::error_code error = std::make_error_code( ec );
    switch ( ec )
    {
      case std::errc::resource_unavailable_try_again :
        break;
      default :
        throw std::system_error(error);
    }
  }
  return bytes;
}

/******************************************************************************/
const int Socket::get_fd() const
{
  return _fd;
}

/******************************************************************************/
void Socket::set_bound_port( int port )
{
  _bound_port = port;
}

/******************************************************************************/
const int Socket::get_bound_port() const
{
  return _bound_port;
}

/******************************************************************************/
const bool Socket::is_bound() const
{
  return _bound_port > 0;
}

/******************************************************************************/
const bool Socket::is_open() const
{
  return _opened && !_closed;
}
