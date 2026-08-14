cmake_minimum_required(VERSION 3.15)

project(RaymarchedSphere LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_executable(raymarched_sphere ${SOURCES})
target_include_directories(raymarched_sphere PRIVATE src)

if(MSVC)
    target_compile_options(raymarched_sphere PRIVATE /W4 /permissive-)
else()
    target_compile_options(raymarched_sphere PRIVATE -Wall -Wextra -Wpedantic)
endif()
