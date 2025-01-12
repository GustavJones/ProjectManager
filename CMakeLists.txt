cmake_minimum_required(VERSION 3.15)
project(ProjectManager)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

add_subdirectory("external/GArgs")

add_subdirectory("src/ProjectManager-Application")
