cmake_minimum_required(VERSION 3.20)


project(VIETTEL_TEST 
        VERSION 1.0.0
        LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(Warnings)
include(Linker)

add_executable(Test Test.c)
add_executable(priority priority.c)

target_set_warnings(priority ON ON)
target_generate_map(priority)










