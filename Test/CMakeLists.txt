# CMakeList.txt : CMake project for TextToDigits, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB HEADERS
    ../App/TextToDigitsConverter.hpp
    ../App/Token.hpp
    ../App/Parser.hpp
    ../App/TextToDigitsConverterContext.hpp
)

file(GLOB SOURCES
    ../App/TextToDigitsConverter.cpp
    ../App/Token.cpp
    ../App/Parser.cpp
)

add_executable (Test "main.cpp" ${HEADERS} ${SOURCES})

include_directories(../App)
