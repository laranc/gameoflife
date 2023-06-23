cmake_minimum_required(VERSION 3.18)

project(gameoflife LANGUAGES C)

file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/src/**")
set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/src/")

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCES}
)
target_include_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_INCLUDE}/**
    /usr/include/raylib/
    /usr/include/
)

find_package(raylib 4.2 REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    m
    raylib
)

target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")
