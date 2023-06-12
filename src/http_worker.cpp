#include "http_worker.hpp"
#include <chrono>

HttpWorker::HttpWorker(
    boost::asio::ip::tcp::acceptor &acceptor,
    std::chrono::seconds timeout)
  : acceptor_(acceptor)
  , timeout_(timeout)
  , work_socket_(acceptor_.get_executor())
  , req_timeout(acceptor_.get_executor(),(std::chrono::steady_clock::time_point::max)())
  {
}

void HttpWorker::start() {
  
}

void HttpWorker::accept() {
  boost::beast::error_code ec;
  work_socket_.close(ec);
  data_buffer_.consume(data_buffer_.size());
  acceptor_.async_accept(
      work_socket_,
      [this](boost::beast::error_code ec) {
        if (ec) {
          accept();
        }
        else {
          req_timeout.expires_after(timeout_);
          read_request();
        }
      });
}

void HttpWorker::read_request() {
  parser_.emplace();
  boost::beast::http::async_read(
      work_socket_,
      data_buffer_,
      *parser_,
      [this](boost::beast::error_code ec, std::size_t) {
        if (ec) {
          accept();
        }
        else {
          process_request(parser_->get());
        }
      });
}
void HttpWorker::process_request(
    boost::beast::http::request<boost::beast::http::string_body> const &req) {}
void HttpWorker::check_timeout() {}
