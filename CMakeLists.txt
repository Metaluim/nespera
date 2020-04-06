cmake_minimum_required(VERSION 3.13)

project(nespera)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

if (SANITIZE)
  # TODO: cross-platform
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
endif()

# TODO: cross-platform compiler flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

include_directories(${PROJECT_SOURCE_DIR}/include)
#include_directories(${PROJECT_SOURCE_DIR}/include/apu)
#include_directories(${PROJECT_SOURCE_DIR}/include/cpu)
#include_directories(${PROJECT_SOURCE_DIR}/include/formats)
#include_directories(${PROJECT_SOURCE_DIR}/include/io)
#include_directories(${PROJECT_SOURCE_DIR}/include/ppu)
#include_directories(${PROJECT_SOURCE_DIR}/include/render)

# TODO: find out cross-platform way to do this
set(NESPERA_DEPS stdc++fs)

set(NESPERA_INSTALL_BIN_DIR ${CMAKE_INSTALL_PREFIX}/bin)

add_subdirectory(src)
