#include "TCPServer.h"

#include <iostream>
#include <iterator>
#include <vector>

#include <csignal>

bool STOP = false;
void signal_handler( int signum )
{
  STOP = true;
}

int main(int argc, char *argv[])
{
  signal(SIGINT, signal_handler);
  std::vector<uint8_t> send_buffer, recv_buffer;
  recv_buffer.reserve( 1024 );
  send_buffer.reserve( 1024 );
  try
  {
    TCPServer server;
    server.Bind( 10001 );
    server.Listen( );
    server.Accept( );
    while ( !STOP )
    {
      if ( server.Recv( recv_buffer, false ) )
      {
        std::reverse_iterator<std::vector<uint8_t>::iterator> from (recv_buffer.end());
        std::reverse_iterator<std::vector<uint8_t>::iterator> until (recv_buffer.begin());
        for (auto ichar : recv_buffer)
          std::cout << ichar;
        std::cout << " was received" << std::endl;
        send_buffer.assign(from, until);
        if ( server.Send( send_buffer, false ) )
        {
          std::cout << "Sent." << std::endl << std::flush;
          for (auto ichar : send_buffer)
            std::cout << ichar;
          std::cout << std::endl;
        }
      }
    }
    std::cout << "Stopped." << std::endl << std::flush;
  } catch ( std::system_error &e)
  {
    std::cout << "Error Encountered: " << e.what() << std::endl;
  }
}

