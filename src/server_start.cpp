#include <iostream>
#include <thread>

#include <boost/asio/ip/address.hpp>

#include "web_server.hpp"

void usage() {
  std::cout << "Usage:" << std::endl
    << "  web_server <ip> <port> [<num_workers> <num_threads>]" << std::endl
    << std::endl
    << "for example:" << std::endl
    << "  web_server 127.0.0.1 31377 100 8" << std::endl
    << std::endl;;
}

int main(int argc, const char *argv[])
{
  if (argc < 3) {
    usage();
    return EXIT_FAILURE;
  }
  
  auto host = boost::asio::ip::make_address(argv[1]);
  uint16_t port = static_cast<uint16_t>(std::atoi(argv[2]));

  int numWorkers = std::thread::hardware_concurrency();
  int numThreads = std::thread::hardware_concurrency();

  if (argc == 5) {
    numWorkers = std::max<int>(1, std::atoi(argv[3])); 
    numThreads = std::max<int>(1, std::atoi(argv[4])); 
  }
  Webserver web_server(host, port, numWorkers, numThreads);
}
