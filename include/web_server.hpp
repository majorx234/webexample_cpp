#ifndef WEB_SERVER_HPP
#define WEB_SERVER_HPP

#include <list>

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/address.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdint>

#include "http_worker.hpp"

class Webserver {
 public:
  Webserver(
      boost::asio::ip::address host,
      uint16_t port,
      int num_workers,
      int num_threads);
 private:
  boost::asio::ip::address host_;
  uint16_t port_;
  int num_workers_;
  int num_threads_;
  boost::asio::io_context ioc_;
  boost::asio::ip::tcp::acceptor acceptor_;
  std::list<HttpWorker> workers_;
};

#endif // WEB_SERVER_HPP
