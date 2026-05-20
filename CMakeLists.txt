cmake_minimum_required(VERSION 3.10)
project(OLPA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options("/utf-8")
endif()

set(SOURCES
    main.cpp
    grouper.cpp
    grouper.h

)


add_executable(${PROJECT_NAME} ${SOURCES})

file(COPY objects.txt DESTINATION "./")


