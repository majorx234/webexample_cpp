#include "web_server.hpp"

Webserver::Webserver(boost::asio::ip::address host, uint16_t port,
                     int num_workers, int num_threads)
  : host_(host)
  , port_(port_)
  , num_workers_(num_workers)
  , num_threads_(num_threads_)
  , ioc_(num_workers)
  , acceptor_(ioc_, {host_, port_})
{
  
}
