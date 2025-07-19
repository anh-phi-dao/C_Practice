cmake_minimum_required(VERSION 3.20)


project(VIETTEL_TEST 
        VERSION 1.0.0
        LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(Test Test.c)
add_executable(priority priority.c)


