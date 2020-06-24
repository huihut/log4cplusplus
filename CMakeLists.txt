cmake_minimum_required(VERSION 3.6)
project(log4cplusplus)

set(CMAKE_CXX_STANDARD 17)
set(PROJECT_ROOT_DIR ${PROJECT_SOURCE_DIR})

if(WIN32)
  link_directories(${PROJECT_ROOT_DIR}/bin/)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_ROOT_DIR}/bin")
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_ROOT_DIR}/bin")
endif(WIN32)

add_subdirectory(log4cplus)
add_subdirectory(log4cplusplus)
add_subdirectory(tests)