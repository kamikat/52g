project(52g CXX)

cmake_minimum_required(VERSION 3.2)

add_subdirectory(src)
add_subdirectory(core)

add_executable(mkbfidx mkbfidx.cc)
target_link_libraries(mkbfidx core)

add_subdirectory(test)
