cmake_minimum_required(VERSION 3.0.0)

project(addon)

set(CMAKE_CXX_FLAGS "-DUSE_LIBUV -std=c++11 -O3 -shared -fPIC -static-libstdc++ -static-libgcc -s")
set(SRC addon.cpp  emitter.cpp)

##$npm install nan
##-I
include_directories(. /usr/local/include/node ${CMAKE_CURRENT_SOURCE_DIR}/node_modules/nan) 

##-L
link_directories(.)

##library
add_library(${PROJECT_NAME} SHARED ${SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")

##-l  do not need "-l"
target_link_libraries(${PROJECT_NAME} )
