cmake_minimum_required(VERSION 3.10)
project(MyTextEditor)

set(CMAKE_CXX_STANDARD 17)
include_directories(include)

# Find and include GLFW
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})

# Find OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# Include libRocket
add_subdirectory(libRocket)
include_directories(libRocket/Include)

file(GLOB SOURCES "src/*.cpp")

add_executable(MyTextEditor ${SOURCES})

target_link_libraries(MyTextEditor ${GLFW_LIBRARIES} OpenGL::GL RocketCore RocketControls RocketDebugger)
