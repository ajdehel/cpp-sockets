#pragma once

#include <vector>

#include <sys/socket.h>

/******************************************************************************/
enum class Domain_E
{
  unix=AF_UNIX,
  local=AF_LOCAL,
  inet=AF_INET,
  inet6=AF_INET6,
  ipx=AF_IPX,
  netlink=AF_NETLINK,
  x25=AF_X25,
  ax25=AF_AX25,
  atmpvc=AF_ATMPVC,
  appletalk=AF_APPLETALK,
  packet=AF_PACKET
};

/******************************************************************************/
enum class Type_E
{
  stream=SOCK_STREAM,
  dgram=SOCK_DGRAM,
  seqpacket=SOCK_SEQPACKET,
  raw=SOCK_RAW,
  rdm=SOCK_RDM,
  packet=SOCK_PACKET
};

/******************************************************************************/
enum class Protocol_E
{
  Default=0
};

/******************************************************************************/
enum class Sockopt_E
{
  accept_connection=SO_ACCEPTCONN,
  bind_to_device=SO_BINDTODEVICE,
  broadcast=SO_BROADCAST,
  bsd_compatibility=SO_BSDCOMPAT,
  debug=SO_DEBUG,
  domain=SO_DOMAIN,
  error=SO_ERROR,
  dont_route=SO_DONTROUTE,
  keep_alive=SO_KEEPALIVE,
  linger=SO_LINGER,
  mark=SO_MARK,
  out_of_band_in_line=SO_OOBINLINE,
  pass_credentials=SO_PASSCRED,
  peer_credentials=SO_PEERCRED,
  priority=SO_PRIORITY,
  protocol=SO_PROTOCOL,
  recv_buf_size=SO_RCVBUF,
  recv_buf_size_force=SO_RCVBUFFORCE,
  recv_low_watermark=SO_RCVLOWAT,
  send_low_watermark=SO_SNDLOWAT,
  recv_timeout=SO_RCVTIMEO,
  send_timeout=SO_SNDTIMEO,
  reuse_address=SO_REUSEADDR,
  send_buf_size=SO_SNDBUF,
  send_buf_size_force=SO_SNDBUFFORCE,
  timestamp=SO_TIMESTAMP,
  type=SO_TYPE
};

enum class Msgflag_E
{
  confirm=MSG_CONFIRM,
  dont_route=MSG_DONTROUTE,
  dont_wait=MSG_DONTWAIT,
  end_of_record=MSG_EOR,
  send_more=MSG_MORE,
  no_signal=MSG_NOSIGNAL,
  out_of_band=MSG_OOB
};

template<typename T> int to_int( std::vector<T> flags );
template<typename T> std::vector<T> to_vector( int );






