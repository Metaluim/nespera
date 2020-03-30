cmake_minimum_required(VERSION 3.13)

set(SRCs nespera.cpp)

add_executable(nespera ${SRCs})
install(TARGETS nespera DESTINATION ${NESPERA_INSTALL_BIN_DIR})
