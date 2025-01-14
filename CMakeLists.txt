cmake_minimum_required(VERSION 3.15)
project(TaskManager)
set(CMAKE_CXX_STANDARD 23)

find_package(Crow CONFIG REQUIRED)

include_directories(include)

add_executable(TaskManager src/Main.cpp)
target_link_libraries(TaskManager PRIVATE Crow::Crow asio::asio)

