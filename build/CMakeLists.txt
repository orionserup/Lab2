cmake_minimum_required(VERSION 2.8)

project(Lab2)

set(SOURCE_DIR ../src)
file(GLOB SOURCES ${SOURCE_DIR}/*.c)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ../include)

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 99)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD_REQUIRED True)

if(MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES 
        COMPILE_FLAGS "/W4 /D_CRT_SECURE_NO_DEPRECATE"
        COMPILE_FLAGS_DEBUG "/DEBUG /Od /DDEBUG /D_DEBUG"
        COMPILE_FLAGS_RELEASE "/Ox /GL /LTCG /DNDEBUG"
    )
else()
    set_target_properties(${PROJECT_NAME} PROPERTIES
        COMPILE_FLAGS "-Wall -Wextra -pedantic"
        COMPILE_FLAGS_DEBUG "-Og -g -DDEBUG"
        COMPILE_FLAGS_RELEASE "-Ofast -DNDEBUG -mtune=native -march=native -fprofile-use -fopenmp"
        LINK_FLAGS_RELEASE "-flto -fprofile-use -fopenmp"
    )
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES 
                      RUNTIME_OUTPUT_DIRECTORY ../bin)

