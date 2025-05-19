cmake_minimum_required(VERSION 3.15)
project(ExampleCPP CXX)

file(GLOB SOURCES "*.cpp")
add_executable(ExampleCPP ${SOURCES})
target_include_directories(ExampleCPP PRIVATE ../../include)
target_link_libraries(ExampleCPP PRIVATE ExampleLibrary)
