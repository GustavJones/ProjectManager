cmake_minimum_required(VERSION 3.5)
project(ProjectManager-Application)

file(GLOB SOURCES "*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ../../include/ ../../external/GArgs/include/)
target_link_libraries(${PROJECT_NAME} PRIVATE GArgs)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
