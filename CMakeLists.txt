cmake_minimum_required(VERSION 3.31)
project(mandelbrott)

set(CMAKE_CXX_STANDARD 26)

if(WIN32)
    add_compile_definitions(SFML_DYNAMIC)
endif()

find_package(SFML 3 COMPONENTS System Window Graphics Audio Network REQUIRED)

add_executable(mandelbrott main.cpp)

target_link_libraries(mandelbrott PRIVATE SFML::Graphics SFML::Audio SFML::Network)
