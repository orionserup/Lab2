cmake_minimum_required(VERSION 2.8)

project(Lab2)

set(SOURCE_DIR ../src)
file(GLOB SOURCES ${SOURCE_DIR}/*.c)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ../include)

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD_REQUIRED True)

if(MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES 
        COMPILE_FLAGS "/W4 /openmp"
        COMPILE_DEFINITIONS "_CRT_SECURE_NO_DEPRECATE"
        COMILE_FLAGS_DEBUG "/DEBUG /DDEBUG /D_DEBUG /Od"
        COMPILE_FLAGS_RELEASE "/Ox /GL /LTCG"
    )
else()
    set_target_properties(${PROJECT_NAME} PROPERTIES
        COMPILE_FLAGS "-Wall -Wextra -pedantic -fopenmp"
        COMPILE_FLAGS_DEBUG "-DDEBUG -Og -g"
        COMPILE_FLAGS_RELEASE "-flto -DNDEBUG -Ofast -mtune=native -march=native -fprofile-use"
        LINK_FLAGS "-flto -fopenmp"
    )
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES 
                      RUNTIME_OUTPUT_DIRECTORY ../bin)

