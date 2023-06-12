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

add_library(http_worker
  ${HTTP_WORKER_SRC}
)
target_include_directories(http_worker
	PRIVATE ${PROJECT_INCLUDE_DIRS}
	PUBLIC ${Boost_INCLUDE_DIRS}	
)
target_link_libraries(http_worker
	${Boost_LIBRARIES}
)
