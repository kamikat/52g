cmake_minimum_required (VERSION 3.1)
project (bf52g)

add_subdirectory (libbf)
target_include_directories (libbf PUBLIC libbf/src)

add_executable (bf52g bf.cc)
set_property (TARGET bf52g PROPERTY CXX_STANDARD 11)
target_link_libraries (bf52g libbf)
