#include <boost/beast/core/flat_buffer.hpp>
#include <string>
#include <chrono>
#include <functional>
#include <optional>

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio/ip/tcp.hpp>

#ifndef HTTP_WORKER_HPP
#define HTTP_WORKER_HPP

class HttpWorker {
 public:
  HttpWorker(HttpWorker const &) = delete;
  HttpWorker& operator=(HttpWorker const &) = delete;
  HttpWorker(
      boost::asio::ip::tcp::acceptor &acceptor
             );
  void start();
 private:
  boost::asio::ip::tcp::acceptor &acceptor_;
  boost::asio::ip::tcp::socket work_socket_;
  boost::beast::flat_buffer data_buffer_;
  
  std::optional<boost::beast::http::request_parser<boost::beast::http::string_body>> parser_;
                      
};

#endif // HTTP_WORKER_HPP
