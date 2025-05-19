cmake_minimum_required(VERSION 3.15)
project(ExampleLibrary ASM)

file(GLOB SOURCES "*.asm")
add_library(ExampleLibrary STATIC ${SOURCES})
