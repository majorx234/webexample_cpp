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
      boost::asio::ip::tcp::acceptor &acceptor,
      std::chrono::seconds timeout
             );
  void start();
  void accept();
  void read_request();
  void process_request(boost::beast::http::request<boost::beast::http::string_body> const &req);
  void check_timeout();
 private:
  boost::asio::ip::tcp::acceptor &acceptor_;
  boost::asio::ip::tcp::socket work_socket_;
  boost::beast::flat_buffer data_buffer_;

  std::optional<boost::beast::http::request_parser<boost::beast::http::string_body>> parser_;
  boost::asio::basic_waitable_timer<std::chrono::steady_clock> req_timeout;
  std::optional<boost::beast::http::response<boost::beast::http::string_body>> response_;
  std::optional<boost::beast::http::response_serializer<boost::beast::http::string_body>> serializer_;

  std::chrono::seconds timeout_;
};

#endif // HTTP_WORKER_HPP
