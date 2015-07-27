cmake_minimum_required(VERSION 2.8.11)

project(UriCodec)
add_library(${PROJECT_NAME} STATIC UriCodec.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
