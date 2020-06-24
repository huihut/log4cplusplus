cmake_minimum_required(VERSION 3.6)
project(logtest)

set(TARGET_NAME logtest)

set(INCLUDE_DIRECTORY
	${PROJECT_ROOT_DIR}/log4cplusplus/include
)

include_directories(${INCLUDE_DIRECTORY})

add_executable(${TARGET_NAME}
	main.cc
)

target_link_libraries(${TARGET_NAME} log4cplusplus)