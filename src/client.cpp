#include "TCPClient.h"

#include <iostream>
#include <iterator>
#include <string>
#include <sstream>
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
  TCPClient client;
  std::vector<uint8_t> send_buffer, recv_buffer;
  recv_buffer.resize( 1024 );
  send_buffer.resize( 1024 );
  std::string input_buffer;
  try
  {
    client.Connect( std::string("127.0.0.1"), 10001 );
  } catch ( std::system_error &e )
  {
    std::cout << "Could not connect: " << e.what() << std::endl;
    return 1;
  }
    while ( !STOP )
    {
      std::cin >> input_buffer;
      send_buffer.assign( input_buffer.begin(), input_buffer.end() );
      try
      {
        if ( !client.Send( send_buffer, false ) )
        {
          std::cout << "Could not send." << std::endl;
        }
      } catch ( std::system_error &e )
      {
        std::cout << "Fatal Error in Send: " << e.what() << std::endl;
        return 1;
      }
      try
      {
        while ( !client.Recv( recv_buffer, false ) && !STOP ) { }
      } catch ( std::system_error &e )
      {
        std::cout << "Fatal Error in Recv: " << e.what() << std::endl;
        return 1;
      }

      input_buffer.assign( recv_buffer.begin(), recv_buffer.end() );
      std::cout << input_buffer << std::endl << std::flush;
    }
    std::cout << "Stopped." << std::endl << std::flush;
    return 0;
}

