cmake_minimum_required(VERSION 3.30)
project(EPet)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)

include_directories(.)
include_directories(${SDL2_INCLUDE_DIRS}
    #    ${EPet_SOURCE_DIR}/src
    #    ${EPet_SOURCE_DIR}/utils
    #    ${EPet_SOURCE_DIR}/engine
)

find_package(SDL2 REQUIRED)

file(GLOB SOURCES
        src/main.cpp
        "src/*/*.h"
        "src/*/*.hpp"
        "src/*/*.cpp"
)

add_executable(EPet ${SOURCES})

include_directories(${SOURCE_FILES})
target_link_libraries(EPet ${SDL2_LIBRARY})