cmake_minimum_required(VERSION 3.16)

project(BearJPEG VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(bearjpeg
    src/main.cpp
)

target_include_directories(bearjpeg PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_options(bearjpeg PRIVATE -Wall -Wextra -Wpedantic)
