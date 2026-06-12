cmake_minimum_required(VERSION 3.31)
project(mandelbrott)

set(CMAKE_CXX_STANDARD 26)

add_executable(mandelbrott main.cpp)
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_ROOT "./SFML-3.0.2/lib/cmake/SFML")
find_package(SFML COMPONENTS System Window Graphics Audio Network REQUIRED)
include_directories(./SFML-3.0.2/include)
target_link_libraries(mandelbrott  SFML::System SFML::Window SFML::Graphics SFML::Audio SFML::Network)