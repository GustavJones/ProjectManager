cmake_minimum_required(VERSION 3.5)
project(ProjectManager)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

add_subdirectory("external/GArgs")

add_subdirectory("src/ProjectManager-Application")
