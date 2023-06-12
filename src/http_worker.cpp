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

void HttpWorker::read_request() {}
void HttpWorker::process_request() {}
void HttpWorker::check_timeout() {}
