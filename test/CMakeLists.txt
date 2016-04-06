add_executable(hasher hasher.cc)
target_link_libraries(hasher libbf)
target_compile_options(hasher PRIVATE -std=c++11)
