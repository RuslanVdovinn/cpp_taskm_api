cmake_minimum_required(VERSION 3.15.0)
project(TaskManager VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_TOOLCHAIN_FILE "D:cpp/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
set(CMAKE_PREFIX_PATH "D:/cpp/vcpkg/installed/x64-windows")
set(CMAKE_MODULE_PATH "D:/cpp/vcpkg/installed/x64-windows/share")

message("CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")
message("CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")
set(VCPKG_TARGET_TRIPLET "x64-windows-static")


find_package(Crow REQUIRED)

include_directories(include)

add_executable(TaskManager Main.cpp)
target_link_libraries(TaskManager PRIVATE Crow::Crow)

