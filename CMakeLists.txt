project(52g CXX)

cmake_minimum_required(VERSION 3.2)

# Export all executable targets to ${CMAKE_BINARY_DIR}
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(src)
add_subdirectory(test)
