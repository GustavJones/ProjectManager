cmake_minimum_required(VERSION 3.15)
project(ExampleLibrary ASM_NASM)

file(GLOB SOURCES "*.nasm")
# set_source_files_properties(${SOURCES} PROPERTIES LANGUAGE ASM_NASM)

add_library(ExampleLibrary STATIC ${SOURCES})
