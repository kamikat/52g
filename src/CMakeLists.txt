add_subdirectory(libbf/src)
target_compile_options(libbf PUBLIC -std=c++11)
target_include_directories(libbf PUBLIC libbf/src)

add_subdirectory(docopt)

add_subdirectory(core)

add_executable(mkbfidx mkbfidx.cc)
target_link_libraries(mkbfidx core)
