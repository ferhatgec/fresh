cmake_minimum_required(VERSION 3.12)
project(fresh_example)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

get_property(INCLUDE_PATHS GLOBAL PROPERTY "FRESH_INCLUDE_PATHS")

add_executable(fresh_example example_lib.cpp)
target_include_directories(fresh_example PRIVATE ${INCLUDE_PATHS})
target_link_libraries(fresh_example PRIVATE fresh_lib)

add_custom_command(TARGET fresh_example POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/box2d_example ${CMAKE_CURRENT_BINARY_DIR}/
)
