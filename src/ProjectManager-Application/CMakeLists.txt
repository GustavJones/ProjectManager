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
      file(TO_CMAKE_PATH $ENV{HOMEDRIVE}$ENV{HOMEPATH}/${APPLICATION_NAME} INSTALL_PATH)
      install(DIRECTORY ${TEMPLATE} DESTINATION ${INSTALL_PATH})
      message(STATUS "Template install location: ${INSTALL_PATH}")
    else()
      install(DIRECTORY ${TEMPLATE} DESTINATION $ENV{HOME}/ProjectManager/)
      message(STATUS "Template install location: $ENV{HOME}/ProjectManager/")
    endif()
  endif()
endforeach()
