cmake_minimum_required(VERSION 3.31)
project(mandelbrott)

set(CMAKE_CXX_STANDARD 26)

set(SFML_BUILD_EXAMPLES OFF CACHE INTERNAL "")
set(SFML_BUILD_DOC OFF CACHE INTERNAL "")

include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY "https://github.com/SFML/SFML.git"
        GIT_TAG        "3.0.2"
        TLS_VERIFY     OFF
)
FetchContent_MakeAvailable(SFML)

add_executable(mandelbrott main.cpp)

# В режиме FetchContent библиотеки собираются прямо внутри проекта
# Поэтому линкуем их БЕЗ двоеточий (sfml-graphics вместо SFML::Graphics)
target_link_libraries(mandelbrott PRIVATE sfml-graphics sfml-audio sfml-network)
