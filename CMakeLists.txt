cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

project(webexamples_cpp)

find_package(Boost 1.81.0 REQUIRED)

set(PROJECT_INCLUDE_DIRS
  include
)

set(HTTP_WORKER_SRC
	src/http_worker.cpp
	include/http_worker.hpp
)

set(WEB_SERVER_SRC
	src/web_server.cpp
	src/server_start.cpp
	include/web_server.hpp
)

set(BOOST_ASIO_TIMER_EXAMPLE_SRC
  src/boost_asio_timer_example.cpp
)

add_library(http_worker)
target_sources(http_worker
	PRIVATE
	${HTTP_WORKER_SRC}
)
target_include_directories(http_worker
	PRIVATE ${PROJECT_INCLUDE_DIRS}
	PUBLIC ${Boost_INCLUDE_DIRS}	
)
target_link_libraries(http_worker
	${Boost_LIBRARIES}
)

add_executable(web_server)
target_sources(web_server
	PRIVATE
  ${WEB_SERVER_SRC}
)
target_include_directories(web_server
	PRIVATE ${PROJECT_INCLUDE_DIRS}
	PUBLIC ${Boost_INCLUDE_DIRS}
)
target_link_libraries(web_server
	${Boost_LIBRARIES}
	http_worker
)

add_executable(boost_asio_timer_example)
target_sources(boost_asio_timer_example
	PRIVATE
  ${BOOST_ASIO_TIMER_EXAMPLE_SRC}
)
target_include_directories(boost_asio_timer_example
	PRIVATE ${PROJECT_INCLUDE_DIRS}
	PUBLIC ${Boost_INCLUDE_DIRS}
)
target_link_libraries(boost_asio_timer_example
	${Boost_LIBRARIES}
)
