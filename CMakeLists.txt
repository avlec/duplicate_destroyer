cmake_minimum_required(VERSION 3.14.5)

project(duplicate_destroyer
  VERSION 1.0.0
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

find_package(Boost 1.69 COMPONENTS filesystem REQUIRED)
find_package(OpenSSL COMPONENTS Crypto REQUIRED)
find_package(Catch2 REQUIRED)

include_directories(include)

add_executable(${CMAKE_PROJECT_NAME} app/main.cpp lib/finder.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} Boost::filesystem OpenSSL::Crypto)

add_executable(${CMAKE_PROJECT_NAME}-test app/test.cpp lib/finder.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME}-test Boost::filesystem OpenSSL::Crypto Catch2::Catch2)


