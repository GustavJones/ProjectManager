cmake_minimum_required(VERSION 3.15)
project(Template-Sources)

file(GLOB Template-Components "*/")

foreach(Template-Component ${Template-Components})
  if(IS_DIRECTORY ${Template-Component})
    if(EXISTS "${Template-Component}/CMakeLists.txt")
      message(STATUS "Adding source: ${Template-Component}")
      add_subdirectory(${Template-Component})
    endif()
  endif()
endforeach()
