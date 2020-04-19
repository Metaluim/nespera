cmake_minimum_required(VERSION 3.13)

project(nespera)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

if (SANITIZE)
  # TODO: cross-platform
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
endif()
# TODO: cross-platform compiler flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
# TODO: find out cross-platform way to do this
set(NESPERA_DEPS stdc++fs ${SDL2_LIBRARIES})

include_directories(${PROJECT_SOURCE_DIR}/include)

set(NESPERA_INSTALL_BIN_DIR ${CMAKE_INSTALL_PREFIX}/bin)

add_subdirectory(src)
