add_executable(hasher_test hasher.cc)
target_link_libraries(hasher_test libbf)
target_compile_options(hasher_test PRIVATE -std=c++11)
