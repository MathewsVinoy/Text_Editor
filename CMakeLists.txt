cmake_minimum_required(VERSION 3.10)
project(MyTextEditor)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

file(GLOB SOURCES "src/*.cpp")

add_executable(MyTextEditor ${SOURCES})
target_link_libraries(MyTextEditor ${SDL2_LIBRARIES})
