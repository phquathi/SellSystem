cmake_minimum_required(VERSION 3.23)
project(SmartCar_v1)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

add_executable(SmartCar_v1 main.cpp)
target_link_libraries(SmartCar_v1 ${GTK3_LIBRARIES})
