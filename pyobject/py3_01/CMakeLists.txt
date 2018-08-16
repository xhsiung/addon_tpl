cmake_minimum_required(VERSION 2.8)

project(addon)

#apt install python3.5-dev
find_package(PythonLibs 3 REQUIRED)

include_directories(${PYTHON_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -O3 -fPIC")

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/addon.c
    ${CMAKE_CURRENT_SOURCE_DIR}/libaddon.c
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})
#add_executable(example ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${PYTHON_LIBRARIES})

#libexample.so --> example.so is addon.so
set_target_properties(addon PROPERTIES PREFIX "")
install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/mylib )
