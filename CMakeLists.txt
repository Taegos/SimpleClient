cmake_minimum_required (VERSION 3.8)
set(EXTERNAL ${CMAKE_SOURCE_DIR}/external)

project (SimpleClient)

add_subdirectory(consoleclient)
add_subdirectory(src)