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
  accept();
  check_timeout();
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
    }
  );
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
    }
  );
}

void HttpWorker::process_request(
  boost::beast::http::request<boost::beast::http::string_body> const &req) {
  if (req.method() == boost::beast::http::verb::get && req.target() == "/test") {
    response_.emplace();
    response_->result(boost::beast::http::status::ok);
    response_->set(boost::beast::http::field::server, std::string("Webserver "));
    response_->set(boost::beast::http::field::content_type, "text/plain");
    response_->set(boost::beast::http::field::access_control_allow_origin, "*");
    response_->body() = "C++ rules!";
    response_->prepare_payload();
    serializer_.emplace(*response_);
    boost::beast::http::async_write(
      work_socket_,
      *serializer_,
      [this](boost::beast::error_code ec, std::size_t) {
        work_socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_send, ec);
        serializer_.reset();
        response_.reset();
        accept();
      }
    );
  }
}

void HttpWorker::check_timeout() {
  if (req_timeout.expiry() <= std::chrono::steady_clock::now())
  {
    work_socket_.close();
    req_timeout.expires_at(std::chrono::steady_clock::time_point::max());
  }
  req_timeout.async_wait(
      [this](boost::beast::error_code) {
        check_timeout();
      });
}
