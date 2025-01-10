cmake_minimum_required(VERSION 3.5)
project(Template-Sources)

file(GLOB Template-Components "*/")

foreach(Template-Component ${Template-Components})
  if(IS_DIRECTORY ${Template-Component})
    add_subdirectory(${Template-Component})
  endif()
endforeach()
