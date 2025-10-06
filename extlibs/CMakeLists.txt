add_subdirectory(minhook)
add_subdirectory(omath)
project(xorstr)
add_library(xorstr INTERFACE)

target_include_directories(xorstr INTERFACE xorstr/include)