cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(OMATH_STATIC_MSVC_RUNTIME_LIBRARY ON)
project(l4bhop)

add_library(l4bhop MODULE src/main.cpp)

set(CMAKE_SHARED_MODULE_PREFIX "")

add_subdirectory(src/SDK)

find_package(minhook CONFIG REQUIRED)
find_package(omath CONFIG REQUIRED)
target_link_libraries(l4bhop PRIVATE minhook::minhook omath::omath)


target_include_directories(${PROJECT_NAME} PRIVATE vmprotect_sdk/include)
target_link_directories(${PROJECT_NAME} PRIVATE vmprotect_sdk/lib)
target_link_options(${PROJECT_NAME} PRIVATE /MAP)