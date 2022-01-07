cmake_minimum_required(VERSION 3.1)

project(Lab2)

file(GLOB SOURCES ../src/*.c)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

set(CMAKE_C_COMPILER /bin/gcc)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_FLAGS "-Wall -Wextra -fopenmp")
set(CMAKE_C_FLAGS_RELEASE "-DNDEBUG -Ofast -flto -march=native -mtune=native")
set(CMAKE_C_FLAGS_DEBUG "-Og -g -DDEBUG")

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ../include)
