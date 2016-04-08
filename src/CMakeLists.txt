add_subdirectory(libbf/src)
target_compile_options(libbf PUBLIC -std=c++11)
target_include_directories(libbf PUBLIC libbf/src)

add_subdirectory(docopt)
add_subdirectory(json11)

add_subdirectory(core)

# Export executable targets to ${CMAKE_BINARY_DIR}
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(mkbfidx mkbfidx.cc)
target_link_libraries(mkbfidx core docopt)

add_executable(openidx openidx.cc)
target_link_libraries(openidx core docopt)

find_package(PkgConfig)
find_package(Boost REQUIRED COMPONENTS system)
pkg_search_module(OpenSSL REQUIRED openssl)
pkg_search_module(ngHTTP2 REQUIRED libnghttp2)
pkg_search_module(ngHTTP2_asio REQUIRED libnghttp2_asio)

# Resolve OpenSSL library names to paths (fixes conflict with default ssl implementation on OS X)
foreach(name ${OpenSSL_LIBRARIES})
  find_library(${name}_LOCATION ${name} PATHS ${OpenSSL_LIBRARY_DIRS} NO_DEFAULT_PATH)
  list(APPEND OpenSSL_LIBRARIES_ ${${name}_LOCATION})
endforeach()
set(OpenSSL_LIBRARIES ${OpenSSL_LIBRARIES_})

add_executable(servidx servidx.cc)
target_include_directories(servidx
  PRIVATE
    ${ngHTTP2_INCLUDE_DIRS}
    ${OpenSSL_INCLIDE_DIRS})
target_link_libraries(servidx core docopt)
target_link_libraries(servidx
    ${ngHTTP2_LIBRARIES}
    ${ngHTTP2_asio_LIBRARIES}
    ${OpenSSL_LIBRARIES}
    ${Boost_LIBRARIES})
