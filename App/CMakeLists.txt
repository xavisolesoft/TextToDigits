# CMakeList.txt : CMake project for TextToDigits, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB HEADERS
    ../App/TextToDigitsConverter.hpp
)

file(GLOB SOURCES
    ../App/TextToDigitsConverter.cpp
)

# Add source to this project's executable.
add_executable (App "main.cpp" ${HEADERS} ${SOURCES})

# TODO: Add tests and install targets if needed.
