#include "web_server.hpp"

Webserver::Webserver(boost::asio::ip::address host, uint16_t port,
                     int num_workers, int num_threads)
  : host_(host)
  , port_(port)
  , num_workers_(num_workers)
  , num_threads_(num_threads)
  , ioc_(num_workers)
  , acceptor_(ioc_, {host_, port_})
{
  for (int i = 0; i < num_workers_; i++) {
    workers_.emplace_back(acceptor_);
    workers_.back().start();
  }
  threads_.reserve(size_t(num_threads_));
}

void Webserver::start() {
  boost::asio::io_context &ioc_ref = ioc_;
  for (auto i = 0; i < num_threads_-1; ++i) {
    threads_.emplace_back( [&ioc_ref] { ioc_ref.run(); });
  }
  std::cout << "webserver with " << num_workers_ << " workers in " << std::endl;
  std::cout << "            in " << num_threads_ << " threads" << std::endl;
  std::cout << " listening on " << host_ << ':' << port_  << std::endl;
  ioc_.run();
}

Webserver::~Webserver() {
  for (auto &t : threads_) {
    t.join();
  }
}
