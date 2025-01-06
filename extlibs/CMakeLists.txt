add_subdirectory(code-virtualizer-sdk)
add_subdirectory(minhook)

project(xorstr)
add_library(xorstr INTERFACE)
target_include_directories(xorstr INTERFACE xorstr/include)