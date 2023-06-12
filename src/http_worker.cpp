#include "http_worker.hpp"

HttpWorker::HttpWorker(
      boost::asio::ip::tcp::acceptor &acceptor)
  : acceptor_(acceptor)
  , work_socket_(acceptor_.get_executor())
  {
}

void HttpWorker::start() {
  
}
