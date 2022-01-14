cmake_minimum_required(VERSION 2.8)

project(Lab2)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

if(MSVC)
    set(CMAKE_C_FLAGS "/W4 /D_CRT_SECURE_NO_DEPRECATE")
    set(CMAKE_C_FLAGS_DEBUG "/DEBUG /Od /DDEBUG /D_DEBUG /DLOG")
    set(CMAKE_C_FLAGS_RELEASE "/Ox /GL /LTCG /DNDEBUG")
else()
    set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic -Wfloat-equal")
    set(CMAKE_C_FLAGS_DEBUG "-Og -g -DDEBUG -DLOG -DVLA")
    set(CMAKE_C_FLAGS_RELEASE "-Ofast -DNDEBUG -mtune=native -march=native -fopenmp -fprofile-use")
    set(CMAKE_LINK_FLAGS_RELEASE "-flto -fopenmp -fprofile-use")
endif()

file(GLOB SOURCES ../src/*.c)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ../include)
set_target_properties(${PROJECT_NAME} PROPERTIES 
                      RUNTIME_OUTPUT_DIRECTORY ../bin)

