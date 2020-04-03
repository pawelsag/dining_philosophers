cmake_minimum_required(VERSION 3.10)
project(dining_philosophers)

set(target so_app)

set(CMAKE_CXX_STANDARD 17)
set(COMMON_FLAGS "-Wall -Wextra")
find_package(Curses REQUIRED)
add_definitions(${COMMON_FLAGS})

include_directories(${CURSES_INCLUDE_DIR})
include_directories(app)
add_subdirectory(app)

add_executable(${target} main.cpp ${app_src})
target_link_libraries(${target} fmt pthread ${CURSES_LIBRARIES}) 
