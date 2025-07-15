cmake_minimum_required(VERSION 3.15)
project(Example ASM_NASM)

file(GLOB SOURCES "*.nasm")
# set_source_files_properties(${SOURCES} PROPERTIES LANGUAGE ASM_NASM)

add_executable(Example ${SOURCES})
target_link_libraries(Example PRIVATE ExampleLibrary)
