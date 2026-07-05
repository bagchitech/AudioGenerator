cmake_minimum_required(VERSION 3.10)
project(audiogen C)

set(CMAKE_C_STANDARD 11)

# Enable strict warnings
if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Where to find headers
include_directories(include)

# What to build
add_executable(audiogen
    src/main.c
    src/audiogenerator.c
)

target_link_libraries(audiogen m)