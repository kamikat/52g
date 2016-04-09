include(${CMAKE_CURRENT_LIST_DIR}/nghttp2Config.cmake)

find_package(Boost REQUIRED COMPONENTS system)
find_package(PkgConfig)
pkg_search_module(ngHTTP2_asio REQUIRED libnghttp2_asio)

find_library(ngHTTP2_asio_LOCATION NAMES ${ngHTTP2_asio_LIBRARIES})

add_library(nghttp2_asio UNKNOWN IMPORTED)
set_property(TARGET nghttp2_asio PROPERTY IMPORTED_LOCATION ${ngHTTP2_asio_LOCATION})
set_property(TARGET nghttp2
             PROPERTY INTERFACE_INCLUDE_DIRECTORIES
               ${ngHTTP2_asio_INCLUDE_DIRS})
set_property(TARGET nghttp2_asio PROPERTY INTERFACE_LINK_LIBRARIES nghttp2 ${Boost_LIBRARIES})
set_property(TARGET nghttp2_asio APPEND PROPERTY INTERFACE_COMPILE_OPTIONS -std=c++11)
