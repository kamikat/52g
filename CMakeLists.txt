project(52g CXX)

cmake_minimum_required(VERSION 3.2)

add_subdirectory(libbf/src)
target_compile_options(libbf PUBLIC -std=c++11)
target_include_directories(libbf PUBLIC libbf/src)

add_subdirectory(core)

add_executable(mkbfidx mkbfidx.cc)
target_link_libraries(mkbfidx core)

add_subdirectory(test)
