cmake_minimum_required(VERSION 3.13)

set(SRCs_NESPERA nespera.cpp)
set(SRCs_LOADER loader.cpp)

set(SRCs_FORMATS_LIB
  iNES.cpp
)

add_library(formats STATIC ${SRCs_FORMATS_LIB})
target_link_libraries(formats ${NESPERA_DEPS})

add_executable(nespera ${SRCs_NESPERA})
add_executable(loader ${SRCs_LOADER})

target_link_libraries(loader formats ${NESPERA_DEPS})

install(TARGETS nespera DESTINATION ${NESPERA_INSTALL_BIN_DIR})
