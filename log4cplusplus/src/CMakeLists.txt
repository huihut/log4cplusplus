cmake_minimum_required(VERSION 3.6)
project(log4cplusplus)

set(CMAKE_CXX_STANDARD 17)

add_definitions(-DLOG4CPLUSPLUS_EXPORT)
add_definitions(-DUNICODE -D_UNICODE)

set(INCLUDE_DIRECTORY
	${PROJECT_ROOT_DIR}/log4cplusplus/include
	${PROJECT_ROOT_DIR}/log4cplus/include
)

include_directories(${INCLUDE_DIRECTORY})

add_library(log4cplusplus SHARED 
    log4cplusplusimp.cpp
    log4cplusplusimp.h
)

target_link_libraries(log4cplusplus debug log4cplusUD optimized log4cplusU)