#include <boost/asio.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/date_time/posix_time/posix_time_duration.hpp>
#include <iostream>

using namespace boost::asio;
using namespace boost::system;

int main() {
  io_service ioservice;
  deadline_timer timer1(ioservice);
  deadline_timer timer2(ioservice);
  deadline_timer timer3(ioservice);

  std::cout << "Timer started" << std::endl;

  timer1.expires_from_now(boost::posix_time::seconds(3));
  timer1.async_wait([](const error_code &ec){if(!ec) {std::cout << "3 sec are over" << std::endl;}});
  timer2.expires_from_now(boost::posix_time::seconds(5));
  timer2.async_wait([&](const error_code &ec){if(!ec) {
        std::cout << "5 sec are over" << std::endl;
        timer3.expires_from_now(boost::posix_time::seconds(6));
        timer3.async_wait([](const error_code &ec){if(!ec) {std::cout << "6 sec are over" << std::endl;}});
      }});
  ioservice.run();
  std::cin.get();
  return 0;
}
