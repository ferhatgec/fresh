cmake_minimum_required(VERSION 3.21)
project(fresh_lib)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  add_compile_options(/Zc:__cplusplus)
endif()

include(FetchContent)

set(FETCHCONTENT_QUIET FALSE)
set(FRE2D_BUILD_EXAMPLE OFF CACHE INTERNAL OFF)

option(BUILD_EXAMPLE "Build example to see if fresh works correctly" ON)
option(FRESH_UPDATES_DISCONNECTED "Do not check for updates every build" ON)
option(FRESH_DO_NOT_FETCH_LIBRARIES "Do not fetch libraries, good for making changes to dependencies" OFF)

set(FETCHCONTENT_UPDATES_DISCONNECTED_box2d ${FRESH_UPDATES_DISCONNECTED})
set(FETCHCONTENT_UPDATES_DISCONNECTED_colorized ${FRESH_UPDATES_DISCONNECTED})
set(FETCHCONTENT_UPDATES_DISCONNECTED_imgui ${FRESH_UPDATES_DISCONNECTED})
set(FETCHCONTENT_UPDATES_DISCONNECTED_fre2d ${FRESH_UPDATES_DISCONNECTED})
set(FETCHCONTENT_UPDATES_DISCONNECTED_miniaudio ${FRESH_UPDATES_DISCONNECTED})
set(FETCHCONTENT_UPDATES_DISCONNECTED_glfw ${FRESH_UPDATES_DISCONNECTED})

set(FETCHCONTENT_FULLY_DISCONNECTED_box2d ${FRESH_DO_NOT_FETCH_LIBRARIES})
set(FETCHCONTENT_FULLY_DISCONNECTED_colorized ${FRESH_DO_NOT_FETCH_LIBRARIES})
set(FETCHCONTENT_FULLY_DISCONNECTED_imgui ${FRESH_DO_NOT_FETCH_LIBRARIES})
set(FETCHCONTENT_FULLY_DISCONNECTED_fre2d ${FRESH_DO_NOT_FETCH_LIBRARIES})
set(FETCHCONTENT_FULLY_DISCONNECTED_miniaudio ${FRESH_DO_NOT_FETCH_LIBRARIES})
set(FETCHCONTENT_FULLY_DISCONNECTED_glfw ${FRESH_DO_NOT_FETCH_LIBRARIES})

FetchContent_Declare(
  box2d
  GIT_REPOSITORY https://github.com/erincatto/box2d.git
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/box2d
  GIT_TAG origin/main
  GIT_SHALLOW TRUE
)
set(BOX2D_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(box2d)

FetchContent_Declare(
  colorized
  GIT_REPOSITORY https://github.com/ferhatgec/colorized.git
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/colorized
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(colorized)
FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG origin/docking
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(imgui)
FetchContent_Declare(
  idk
  GIT_REPOSITORY https://github.com/ferhatgec/idk.git
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/idk
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(idk)
FetchContent_Declare(
  fre2d
  GIT_REPOSITORY https://github.com/ferhatgec/fre2d.git
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/fre2d
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(fre2d)
FetchContent_Declare(
  miniaudio
  GIT_REPOSITORY https://github.com/mackron/miniaudio
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/miniaudio
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(miniaudio)
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.4
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(glfw)

get_property(FRE2D_INCLUDE_PATHS GLOBAL PROPERTY "FRE2D_INCLUDE_PATHS")

# TODO: Replace every SDL2 functions using FRE2D if any no class matches
# with SDL functions like circle drawing; then implement them in fre2d then
# come back again.
set(INCLUDE_PATHS
  "${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/"
  "${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/backends/"
  "${CMAKE_CURRENT_SOURCE_DIR}/libs/idk/idk/"
  "${CMAKE_CURRENT_SOURCE_DIR}/libs/box2d/include/"
  "${CMAKE_CURRENT_SOURCE_DIR}/libs/colorized/"
  "${CMAKE_CURRENT_SOURCE_DIR}/libs/fre2d/"
  "${CMAKE_CURRENT_SOURCE_DIR}/libs/fre2d/include/"
  "${CMAKE_CURRENT_SOURCE_DIR}/libs/miniaudio/"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/"
  "${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw/include/"
  ${FRE2D_INCLUDE_PATHS})

set_property(GLOBAL PROPERTY FRESH_INCLUDE_PATHS ${INCLUDE_PATHS})

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

set(SOURCE_FILES ${SOURCE_FILES}
  ${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/imgui.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/misc/cpp/imgui_stdlib.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/imgui_demo.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/imgui_draw.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/imgui_tables.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/imgui_widgets.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/backends/imgui_impl_opengl3.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/example/example_lib.cpp)

add_library(fresh_lib STATIC ${SOURCE_FILES})
target_include_directories(fresh_lib PUBLIC ${INCLUDE_PATHS})
target_link_libraries(fresh_lib PUBLIC glfw box2d fre2d_lib)

if(BUILD_EXAMPLE)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/example/)
endif()
