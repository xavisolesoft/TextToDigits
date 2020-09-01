# CMakeList.txt : CMake project for TextToDigits, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

file(GLOB HEADERS
    ../App/TextToDigitsConverter.hpp
)

file(GLOB SOURCES
    ../App/TextToDigitsConverter.cpp
)

# Add source to this project's executable.
add_executable (Test "main.cpp" ${HEADERS} ${SOURCES})

include_directories(../App)

add_custom_command(
        TARGET Test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_SOURCE_DIR}/TestDataSet.txt
                ${CMAKE_CURRENT_BINARY_DIR})

# TODO: Add tests and install targets if needed.
