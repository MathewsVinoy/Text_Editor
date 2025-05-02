cmake_minimum_required(VERSION 3.10)
project(TextEditor)

set(CMAKE_CXX_STANDARD 11)

# Add WebView library
add_subdirectory(webview)

# Include directories
include_directories(webview)

# Add executable
add_executable(MyTextEditor src/main.cpp src/MyRenderInterface.cpp src/keyHandling.cpp)

# Link WebView library
target_link_libraries(MyTextEditor webview)
