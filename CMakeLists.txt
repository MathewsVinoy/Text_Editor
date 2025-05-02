cmake_minimum_required(VERSION 3.10)
project(MyTextEditor)

set(CMAKE_CXX_STANDARD 17)

# Include your own header files
include_directories(include)

# Find and include GLEW
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

# Find and include OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# Find and include GLFW
find_package(glfw3 3.3 REQUIRED)
include_directories(${GLFW3_INCLUDE_DIRS})

# Find and include GTK+
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

# Find and include WebKit2GTK
pkg_check_modules(WEBKIT2GTK REQUIRED webkit2gtk-4.1)
include_directories(${WEBKIT2GTK_INCLUDE_DIRS})
link_directories(${WEBKIT2GTK_LIBRARY_DIRS})


file(GLOB SOURCES "src/*.cpp")

# Define the executable
add_executable(MyTextEditor ${SOURCES})

# Link libraries
target_link_libraries(MyTextEditor
    glfw
    ${GLEW_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${GTK3_LIBRARIES}
    ${WEBKIT2GTK_LIBRARIES}

    freetype
)
