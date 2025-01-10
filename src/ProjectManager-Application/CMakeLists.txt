cmake_minimum_required(VERSION 3.5)
project(ProjectManager-Application)

file(GLOB SOURCES "*.cpp")
add_executable(ProjectManager ${SOURCES})
target_include_directories(ProjectManager PRIVATE ../../include/ ../../external/GArgs/include/)
target_link_libraries(ProjectManager PRIVATE GArgs)

install(TARGETS ProjectManager)

file(GLOB TEMPLATES "../../templates/*")

foreach(TEMPLATE ${TEMPLATES})
  if(IS_DIRECTORY ${TEMPLATE})
    install(DIRECTORY ${TEMPLATE} DESTINATION /opt/ProjectManager/)
  endif()
endforeach()
