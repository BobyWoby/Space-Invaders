cmake_minimum_required(VERSION 4.0)
project(Space-Invaders)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) #This makes neovim aware of the headers

add_subdirectory(vendored/SDL_ttf EXCLUDE_FROM_ALL)
add_subdirectory(vendored/SDL_image EXCLUDE_FROM_ALL)
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

file(GLOB IMGUI_SOURCES 
    vendored/imgui/*.cpp
)

file(GLOB IMGUI_HEADERS
    vendored/imgui/*.h
)

# Include the ImGui files
add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC vendored/imgui)
include_directories(vendored/imgui)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE 
    src/main.cpp
    src/Game.cpp
    src/Player.cpp
    src/Entity.cpp
    src/Bullet.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL3::SDL3
    SDL3_ttf::SDL3_ttf
    SDL3_image::SDL3_image
    imgui
)
install(TARGETS ${PROJECT_NAME} RUNTIME)

# Copy assets folder to build dir
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/assets"
    "${CMAKE_CURRENT_BINARY_DIR}/assets"
)
