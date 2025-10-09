cmake_minimum_required(VERSION 3.15)
project(ExampleLibrary ASM_NASM)

file(GLOB SOURCES "*.nasm")

add_library(ExampleLibrary STATIC ${SOURCES})
target_include_directories(ExampleLibrary PRIVATE ../../include/)
