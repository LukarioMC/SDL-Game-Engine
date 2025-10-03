# ------------------
# Setup project parameters
# ------------------
cmake_minimum_required(VERSION 4.0)
project(8552Tutorial)

set(CMAKE_CXX_STANDARD 20)

# ------------------
# Setup includes & library paths
# ------------------
if (WIN32)
    set(SDL3_PATH "D:/Apps/sdl3")
    set(SDL3_IMAGE_PATH "D:/Apps/sdl3-image")
    include_directories(
        ${SDL3_PATH}/include
        ${SDL3_IMAGE_PATH}/include
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/src/ecs
        ${PROJECT_SOURCE_DIR}/src/ecs/system
        ${PROJECT_SOURCE_DIR}/src/utils
    )
    link_directories(
        ${SDL3_PATH}/lib
        ${SDL3_IMAGE_PATH}/lib
    )
endif()

# ---------------------
# Source files
# ---------------------
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
    ${GLAD_PATH}/src/glad.c   # compile GLAD into exe
)

# ---------------------
# Create executable & link libraries
# ---------------------
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(
    ${PROJECT_NAME}
    SDL3
    SDL3_image
)