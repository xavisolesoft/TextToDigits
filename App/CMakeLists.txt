cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB HEADERS
    TextToDigitsConverter.hpp
    Parser.hpp
    Token.hpp
    TextToDigitsConverterContext.hpp
)

file(GLOB SOURCES
    TextToDigitsConverter.cpp
    Parser.cpp
    Token.cpp
)

add_executable (App "main.cpp" ${HEADERS} ${SOURCES})
