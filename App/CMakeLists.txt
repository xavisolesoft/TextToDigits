cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB HEADERS
    TextToDigitsConverter.hpp
)

file(GLOB SOURCES
    TextToDigitsConverter.cpp
)

add_executable (App "main.cpp" ${HEADERS} ${SOURCES})
