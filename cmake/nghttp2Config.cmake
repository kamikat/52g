find_package(PkgConfig)
pkg_search_module(OpenSSL REQUIRED openssl)
pkg_search_module(ngHTTP2 REQUIRED libnghttp2)

find_library(ngHTTP2_LOCATION NAMES ${ngHTTP2_LIBRARIES})

# Resolve OpenSSL library names to paths (fixes conflict with default ssl implementation on OS X)
foreach(name ${OpenSSL_LIBRARIES})
  find_library(${name}_LOCATION ${name} PATHS ${OpenSSL_LIBRARY_DIRS} NO_DEFAULT_PATH)
  list(APPEND OpenSSL_LIBRARIES_ ${${name}_LOCATION})
endforeach()
set(OpenSSL_LIBRARIES ${OpenSSL_LIBRARIES_})

add_library(nghttp2 UNKNOWN IMPORTED)
set_property(TARGET nghttp2 PROPERTY IMPORTED_LOCATION ${ngHTTP2_LOCATION})
set_property(TARGET nghttp2
             PROPERTY INTERFACE_INCLUDE_DIRECTORIES
               ${ngHTTP2_INCLUDE_DIRS}
               ${OpenSSL_INCLIDE_DIRS})
set_property(TARGET nghttp2
             PROPERTY INTERFACE_LINK_LIBRARIES ${OpenSSL_LIBRARIES})
