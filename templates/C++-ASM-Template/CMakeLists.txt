cmake_minimum_required(VERSION 3.15)
project(Template)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_SHARED_LIBS OFF)
option(BUILD_STATIC_LIBS ON)

if(NOT DEFINED CMAKE_ASM_COMPILER)
  message(STATUS "No CMAKE_ASM_COMPILER specified... Searching for NASM")
  find_program(ASM_COMPILER NAMES "nasm" REQUIRED)
  if(NOT DEFINED ASM_COMPILER-NOTFOUND)
    message(STATUS "Found NASM. Setting CMAKE_ASM_COMPILER")
  else()
    message(FATAL_ERROR "ASM Compiler not found")
  endif()
  set(CMAKE_ASM_COMPILER ${ASM_COMPILER})
endif()

if(NOT DEFINED CMAKE_ASM_LINKER)
  if(DEFINED CMAKE_CXX_LINKER)
    message(STATUS "Set CMAKE_ASM_LINKER to ${CMAKE_CXX_LINKER}")
    set(CMAKE_ASM_LINKER ${CMAKE_CXX_LINKER})
  elseif(DEFINED CMAKE_LINKER)
    message(STATUS "Set CMAKE_ASM_LINKER to ${CMAKE_LINKER}")
    set(CMAKE_ASM_LINKER ${CMAKE_LINKER})
  else()
    message(FATAL_ERROR "Cannot set CMAKE_ASM_LINKER because CMAKE_CXX_LINKER is not set")
  endif()
endif()

set(CMAKE_ASM_COMPILE_OBJECT "${CMAKE_ASM_COMPILER} <DEFINES> <INCLUDES> <FLAGS> -o <OBJECT> <SOURCE>" CACHE STRING "Structure of compile command" FORCE)
set(CMAKE_ASM_LINK_EXECUTABLE "${CMAKE_ASM_LINKER} <CMAKE_ASM_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>" CACHE STRING "Structure of link command" FORCE)

if(DEFINED UNIX)
  set(CMAKE_ASM_FLAGS -felf64)
elseif(DEFINED WIN32)
  set(CMAKE_ASM_FLAGS -fwin64)
endif()

message(STATUS "COMPILING WITH: ${CMAKE_ASM_COMPILE_OBJECT}")
message(STATUS "LINKING WITH: ${CMAKE_ASM_LINK_EXECUTABLE}")

include(GNUInstallDirs)
set(CMAKE_INSTALL_RPATH "$ORIGIN/${CMAKE_INSTALL_LIBDIR} ${CMAKE_INSTALL_FULL_LIBDIR}")
message(STATUS "Using default install RPATH of: ${CMAKE_INSTALL_RPATH}")

file(GLOB SUBMODULES "external/*")

foreach(SUBMODULE ${SUBMODULES})
  if(IS_DIRECTORY ${SUBMODULE})
    if(EXISTS "${SUBMODULE}/CMakeLists.txt")
      message(STATUS "Adding submodule: ${SUBMODULE}")
      add_subdirectory(${SUBMODULE})
    endif()
  endif()
endforeach()

add_subdirectory(src)
