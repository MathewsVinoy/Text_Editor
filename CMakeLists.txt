cmake_minimum_required(VERSION 3.10)
project(MyTextEditor)

set(CMAKE_CXX_STANDARD 17)

# Include your own header files
include_directories(include)

# Find and include GLEW
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_directories(${GLEW_LIBRARY_DIRS})


# Find and include OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

# libRocket
# If you already built libRocket separately, you don't need add_subdirectory(libRocket).
# You should just link to the installed RocketCore, RocketControls libraries.

# If you built libRocket manually and installed it to /usr/local/, you can do:
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

# Collect all your source files
file(GLOB SOURCES "src/*.cpp")

# Define the executable
add_executable(MyTextEditor ${SOURCES})

# Link libraries
target_link_libraries(MyTextEditor
    ${GLFW_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${OPENGL_LIBRARIES}
    RocketCore
    RocketControls
    RocketDebugger
    freetype
)

