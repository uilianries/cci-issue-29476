cmake_minimum_required(VERSION 3.24)
project(wayland_egl_example LANGUAGES C)

find_package(wayland CONFIG REQUIRED)
find_package(egl CONFIG REQUIRED)

add_executable(${CMAKE_PROJECT_NAME} main.c)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE wayland::wayland-client wayland::wayland-egl egl::egl)
