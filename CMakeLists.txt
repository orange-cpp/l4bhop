cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(OMATH_STATIC_MSVC_RUNTIME_LIBRARY ON)
project(l4bhop)

add_library(l4bhop MODULE src/main.cpp)

set(CMAKE_SHARED_MODULE_PREFIX "")

add_subdirectory(src/utils)
add_subdirectory(src/SDK)
add_subdirectory(extlibs)
target_link_libraries(l4bhop PRIVATE minhook xorstr omath::omath)
target_link_options(${PROJECT_NAME} PRIVATE /MAP)
