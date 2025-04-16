cmake_minimum_required(VERSION 3.15)
project(ProjectManager-Application)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(APPLICATION_NAME ProjectManager)

file(GLOB SOURCES "*.cpp")
add_executable(${APPLICATION_NAME} ${SOURCES})
target_compile_definitions(${APPLICATION_NAME} PRIVATE -DAPPLICATION_NAME="${APPLICATION_NAME}")
target_include_directories(${APPLICATION_NAME} PRIVATE ../../include/ ../../external/GArgs/include/)
target_link_libraries(${APPLICATION_NAME} PRIVATE GArgs)

install(TARGETS ${APPLICATION_NAME})

file(GLOB TEMPLATES "../../templates/*")

foreach(TEMPLATE ${TEMPLATES})
  if(IS_DIRECTORY ${TEMPLATE})
    if(WIN32)
      install(DIRECTORY ${TEMPLATE} DESTINATION $ENV{HOMEDRIVE}$ENV{HOMEPATH}/${APPLICATION_NAME}/)
      message(STATUS "Template install location: $ENV{HOMEDRIVE}$ENV{HOMEPATH}/${APPLICATION_NAME}/")
    else()
      install(DIRECTORY ${TEMPLATE} DESTINATION $ENV{HOME}/ProjectManager/)
      message(STATUS "Template install location: $ENV{HOME}/ProjectManager/")
    endif()
  endif()
endforeach()
