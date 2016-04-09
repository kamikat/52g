add_executable(hasher_test hasher.cc)
target_link_libraries(hasher_test libbf)
target_compile_options(hasher_test PRIVATE -std=c++11)

include(${CMAKE_SOURCE_DIR}/cmake/nghttp2_asioConfig.cmake)

add_executable(hello_world hello_world.cc)
target_link_libraries(hello_world nghttp2_asio)
