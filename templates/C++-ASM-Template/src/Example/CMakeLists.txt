cmake_minimum_required(VERSION 3.15)
project(Example ASM)

file(GLOB SOURCES "*.asm")
add_executable(Example ${SOURCES})
target_link_libraries(Example PRIVATE ExampleLibrary)
