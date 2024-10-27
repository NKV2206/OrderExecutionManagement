cmake_minimum_required(VERSION 3.10)
project(OrderExecutionSystem)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(OrderExecutionSystem src/main.cpp src/api_client.cpp src/ordermanager.cpp)
find_package(CURL REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)
target_link_libraries(OrderExecutionSystem PRIVATE nlohmann_json::nlohmann_json)

