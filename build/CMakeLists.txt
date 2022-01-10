cmake_minimum_required(VERSION 3.10)

project(Lab2 VERSION 1.0)

file(GLOB SOURCES ../src/*.c)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ../include)

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)

if(MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES 
        COMPILE_FLAGS "/W4"
        COMILE_FLAGS_DEBUG "/DEBUG /DDEBUG /D_DEBUG /Od"
        COMPILE_FLAGS_RELEASE "/Ox /GL /LTCG"
    )
else()
    set_target_properties(${PROJECT_NAME} PROPERTIES
        COMPILE_FLAGS "-Wall -Wextra -pedantic"
        COMPILE_FLAGS_DEBUG "-DDEBUG -Og -g"
        COMPILE_FLAGS_RELEASE "-flto -DNDEBUG -Ofast -mtune=native -march=native"
    )
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES 
                      RUNTIME_OUTPUT_DIRECTORY ../bin)
