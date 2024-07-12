cmake_minimum_required(VERSION 3.22)
project(life-game)

set(CMAKE_C_STANDARD 11)

file(GLOB SOURCES
        src/*.h
        src/*.c
)

add_executable(${PROJECT_NAME} ${SOURCES} main.c
        src/game.c)

# --- SDL2 SETUP ---
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
set(SDL2_PATH "SDL2/x86_64-w64-mingw32")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES})