cmake_minimum_required(VERSION 4.0)
project(8552Tutorial)

set(CMAKE_CXX_STANDARD 20)

# Set SDL3 include and lib paths
if (WIN32)
    set(SDL3_PATH "D:/Apps/sdl3")
    set(SDL3_IMAGE_PATH "D:/Apps/sdl3-image")
    include_directories(
        ${SDL3_PATH}/include
        ${SDL3_IMAGE_PATH}/include
    )
    link_directories(
        ${SDL3_PATH}/lib
        ${SDL3_IMAGE_PATH}/lib
    )
endif()

add_executable(
    8552Tutorial
    main.cpp
    Game.cpp
)

target_link_libraries(
    8552Tutorial
    SDL3
    SDL3_image
)