cmake_minimum_required(VERSION 3.15)
project(TaskManager)
set(CMAKE_CXX_STANDARD 23)

if (WIN32)
    add_definitions(-D_WIN32_WINNT=0x0601)
endif()

find_package(Crow CONFIG REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(TaskManager src/Main.cpp)
target_link_libraries(TaskManager PRIVATE Crow::Crow asio::asio)

