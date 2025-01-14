cmake_minimum_required(VERSION 3.10)
project(TaskManager)
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(Crow CONFIG REQUIRED)

include_directories(include)

add_executable(TaskManager Main.cpp)
target_link_libraries(TaskManager PRIVATE Crow::Crow asio::asio)

