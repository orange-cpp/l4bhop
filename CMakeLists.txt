cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 26)


project(l4bhop)

add_library(l4bhop MODULE src/main.cpp)

set(CMAKE_SHARED_MODULE_PREFIX "")

add_subdirectory(src/utils)
add_subdirectory(src/SDK)
add_subdirectory(extlibs/minhook)
add_subdirectory(extlibs/code-virtualizer-sdk)

target_link_libraries(l4bhop PRIVATE minhook d3d9 cv-sdk)
target_compile_definitions(l4bhop PRIVATE CV_X32_INSERT_VIA_INLINE)