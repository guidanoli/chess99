cmake_minimum_required(VERSION 3.13.3)
project(chess99)

add_definitions(-DROOT="${CMAKE_CURRENT_LIST_DIR}")

add_subdirectory(src)
add_subdirectory(tests)
