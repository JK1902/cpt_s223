# CMake version
cmake_minimum_required(VERSION 3.22.1)

# Project name
project(pa3)

# Add source files
file(GLOB SOURCES "*.cpp")

# Add header files
file(GLOB HEADERS "*.h")

# Add the executable
add_executable(pa3 ${SOURCES} ${HEADERS})
