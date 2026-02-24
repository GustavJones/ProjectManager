cmake_minimum_required(VERSION 3.20)
project(ProjectManager VERSION 1.0.0)

if(NOT CMAKE_BUILD_TYPE)
  set(DEFAULT_BUILD_TYPE "Debug")
  message(STATUS "Set the build type to `${DEFAULT_BUILD_TYPE}` as none was specified.")
  set(CMAKE_BUILD_TYPE ${DEFAULT_BUILD_TYPE} CACHE STRING "Chooce the build type." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
  "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()
message(STATUS "Project Manager Build Type: ${CMAKE_BUILD_TYPE}")

enable_language(ASM_NASM)
string(REPLACE "<CMAKE_ASM_NASM_COMPILER>" "<CMAKE_C_COMPILER>" CMAKE_ASM_NASM_LINK_EXECUTABLE ${CMAKE_ASM_NASM_LINK_EXECUTABLE})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

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

include("src/sources.cmake")
