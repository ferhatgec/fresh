cmake_minimum_required(VERSION 3.21)
project(fresh_lib)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  add_compile_options(/Zc:__cplusplus)
endif()

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
option(BUILD_EXAMPLE "Build example to see if fresh works correctly" ON)

FetchContent_Declare(
  box2d
  GIT_REPOSITORY https://github.com/erincatto/box2d.git
  SOURCE_DIR ${CMAKE_SOURCE_DIR}/libs/box2d
  GIT_TAG origin/main
  GIT_SHALLOW TRUE
)
set(BOX2D_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(box2d)

FetchContent_Declare(
  colorized
  GIT_REPOSITORY https://github.com/ferhatgec/colorized.git
  SOURCE_DIR ${CMAKE_SOURCE_DIR}/libs/colorized
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(colorized)
FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG origin/docking
  SOURCE_DIR ${CMAKE_SOURCE_DIR}/libs/imgui
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(imgui)
FetchContent_Declare(
  idk
  GIT_REPOSITORY https://github.com/ferhatgec/idk.git
  SOURCE_DIR ${CMAKE_SOURCE_DIR}/libs/idk
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(idk)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)

set(INCLUDE_PATHS ${CMAKE_SOURCE_DIR}/libs/imgui/
                  ${CMAKE_SOURCE_DIR}/libs/imgui/backends/
                  ${CMAKE_SOURCE_DIR}/libs/idk/idk/
                  ${CMAKE_SOURCE_DIR}/libs/box2d/include/
                  ${CMAKE_SOURCE_DIR}/libs/colorized/
                  ${CMAKE_SOURCE_DIR}/include/)

set_property(GLOBAL PROPERTY FRESH_INCLUDE_PATHS ${INCLUDE_PATHS})

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/include/*.hpp ${CMAKE_SOURCE_DIR}/src/*.cpp)

set(SOURCE_FILES ${SOURCE_FILES}
  ${CMAKE_SOURCE_DIR}/libs/imgui/imgui.cpp
  ${CMAKE_SOURCE_DIR}/libs/imgui/misc/cpp/imgui_stdlib.cpp
  ${CMAKE_SOURCE_DIR}/libs/imgui/imgui_demo.cpp
  ${CMAKE_SOURCE_DIR}/libs/imgui/imgui_draw.cpp
  ${CMAKE_SOURCE_DIR}/libs/imgui/imgui_tables.cpp
  ${CMAKE_SOURCE_DIR}/libs/imgui/imgui_widgets.cpp
  ${CMAKE_SOURCE_DIR}/libs/imgui/backends/imgui_impl_opengl3.cpp
  ${CMAKE_SOURCE_DIR}/example/example_lib.cpp)

set(SOURCE_FILES ${SOURCE_FILES}
  ${CMAKE_SOURCE_DIR}/libs/imgui/backends/imgui_impl_sdlrenderer2.cpp
  ${CMAKE_SOURCE_DIR}/libs/imgui/backends/imgui_impl_sdl2.cpp)

add_library(fresh_lib STATIC ${SOURCE_FILES})
target_include_directories(fresh_lib PRIVATE ${INCLUDE_PATHS})

function(Fresh_CopyRequiredDLLs target)
  if(WIN32)
    # adding both Debug and Release builds.
    add_custom_command(TARGET ${target} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_DIR}/../bin/SDL2d.dll ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>
      COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_ttf_DIR}/../bin/SDL2_ttfd.dll ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>
      COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_image_DIR}/../bin/SDL2_imaged.dll ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>
      COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_mixer_DIR}/../bin/SDL2_mixerd.dll ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>
      COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_DIR}/../bin/SDL2.dll ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>
      COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_ttf_DIR}/../bin/SDL2_ttf.dll ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>
      COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_image_DIR}/../bin/SDL2_image.dll ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>
      COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_mixer_DIR}/../bin/SDL2_mixer.dll ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>
    )
  endif()

  target_link_libraries(${target} PRIVATE
    SDL2::SDL2main
    SDL2::SDL2
    SDL2_image::SDL2_image
    SDL2_ttf::SDL2_ttf
    SDL2_mixer::SDL2_mixer)
endfunction()

target_link_libraries(fresh_lib PRIVATE box2d)
Fresh_CopyRequiredDLLs(fresh_lib)

if(BUILD_EXAMPLE)
  add_subdirectory(${CMAKE_SOURCE_DIR}/example/)
endif()
