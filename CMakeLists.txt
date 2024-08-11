cmake_minimum_required(VERSION 3.12)
project(fresh)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INCLUDE_PATHS ./libs/SDL/include/
                  ./libs/SDL_image/include/
                  ./libs/SDL_mixer/include/
                  ./libs/SDL_ttf/include/
                  ./libs/imgui/
                  ./libs/imgui/backends/
                  ./libs/idk/idk/
                  ./include/)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release ... FORCE)
endif()

file(GLOB_RECURSE SOURCE_FILES ./include/*.hpp ./src/*.cpp)

set(SOURCE_FILES ${SOURCE_FILES}
        ./libs/imgui/imgui.cpp
        ./libs/imgui/misc/cpp/imgui_stdlib.cpp
        ./libs/imgui/imgui_demo.cpp
        ./libs/imgui/imgui_draw.cpp
        ./libs/imgui/imgui_tables.cpp
        ./libs/imgui/imgui_widgets.cpp
        ./libs/imgui/backends/imgui_impl_sdlrenderer2.cpp
        ./libs/imgui/backends/imgui_impl_sdl2.cpp
        ./libs/imgui/backends/imgui_impl_opengl3.cpp
        example/example_lib.cpp)

add_library(fresh_lib STATIC ${SOURCE_FILES})
target_include_directories(fresh_lib PRIVATE ${INCLUDE_PATHS})
target_link_libraries(fresh_lib
        ./libs/SDL/lib/x64/SDL2
        ./libs/SDL_image/lib/x64/SDL2_image
        ./libs/SDL_ttf/lib/x64/SDL2_ttf
        ./libs/SDL_mixer/lib/x64/SDL2_mixer)