cmake_minimum_required(VERSION 3.15)

project(RaymarchedSphere LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE GRAPHICS_SOURCES CONFIGURE_DEPENDS src/*.cpp)
list(FILTER GRAPHICS_SOURCES EXCLUDE REGEX "/main(_image|_video)?\\.cpp$")

find_package(Threads REQUIRED)

add_library(graphics_core STATIC ${GRAPHICS_SOURCES})
target_include_directories(graphics_core PUBLIC src)
target_compile_definitions(graphics_core PUBLIC
    GRAPHICS_RENDER_DIR="${CMAKE_SOURCE_DIR}/renders"
)
target_link_libraries(graphics_core PUBLIC Threads::Threads)

add_executable(render_image src/main_image.cpp)
target_link_libraries(render_image PRIVATE graphics_core)

add_executable(render_video src/main_video.cpp)
target_link_libraries(render_video PRIVATE graphics_core)

if(MSVC)
    target_compile_options(graphics_core PRIVATE /W4 /permissive-)
    target_compile_options(render_image PRIVATE /W4 /permissive-)
    target_compile_options(render_video PRIVATE /W4 /permissive-)
else()
    target_compile_options(graphics_core PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(render_image PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(render_video PRIVATE -Wall -Wextra -Wpedantic)
endif()
