cmake_minimum_required(VERSION 3.16)

if(NOT DEFINED APP_NAME)
    set(APP_NAME cardputer-prog-desktop)
endif()

project(${APP_NAME})

# set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)

pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)

# message(STATUS "CMAKE_SOURCE_DIR is: ${CMAKE_SOURCE_DIR}")

file(GLOB_RECURSE SOURCES
    ${CMAKE_SOURCE_DIR}/../../core/src/*.cpp
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

add_executable(${APP_NAME} ${SOURCES})

add_custom_command(
    TARGET ${APP_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E rm -rf "${CMAKE_CURRENT_BINARY_DIR}/assets"
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
            "${CMAKE_CURRENT_SOURCE_DIR}/assets" 
            "${CMAKE_CURRENT_BINARY_DIR}/assets"
    COMMENT "Cleaning and syncing assets directory..."
)

target_include_directories(${APP_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/../../core/include
    ${CMAKE_SOURCE_DIR}/src
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
)

target_compile_options(${APP_NAME} PRIVATE
    ${SDL2_CFLAGS_OTHER}
)

target_link_libraries(${APP_NAME}
    ${SDL2_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
)
