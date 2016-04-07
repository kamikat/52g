add_library(core bloom_filter.cc util.cc)
target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options(core PUBLIC -std=c++11) # FIXME transive usage requirement
target_link_libraries(core PUBLIC libbf)
