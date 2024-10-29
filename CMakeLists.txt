cmake_minimum_required(VERSION 3.10)
project(OrderExecutionSystem)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(OrderExecutionSystem src/main.cpp src/api_client.cpp src/order_manager.cpp)
find_package(CURL REQUIRED)
target_link_libraries(OrderExecutionSystem CURL::libcurl)