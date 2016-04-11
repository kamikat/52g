add_subdirectory(libbf/src)
target_compile_options(libbf PUBLIC -std=c++11)
target_include_directories(libbf PUBLIC libbf/src)

add_subdirectory(docopt)
add_subdirectory(core)

# Export executable targets to ${CMAKE_BINARY_DIR}
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(mkbfidx mkbfidx.cc)
target_link_libraries(mkbfidx core docopt)

add_executable(openidx openidx.cc)
target_link_libraries(openidx core docopt)
