cmake_minimum_required(VERSION 3.2)
project(project)

set(CMAKE_CXX_STANDARD 23)
set(BUILD_SHARED_LIBS FALSE)#!!
include(FetchContent)

FETCHCONTENT_DECLARE(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
)
FETCHCONTENT_MAKEAVAILABLE(SFML)
add_executable(project main.cpp board.cpp board.h piece.h player.cpp player.h hexagon.cpp hexagon.h)
target_link_libraries(project PRIVATE sfml-system sfml-window
        sfml-graphics)