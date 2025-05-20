cmake_minimum_required(VERSION 3.31)
project(ants_life)

set(CMAKE_CXX_STANDARD 14)

include_directories(ants)
include_directories(ants/common)
include_directories(ants/header)
include_directories(ants/source)

add_executable(ants_life
        ants/header/main.hpp
        ants/source/main.cpp
        ants/common/source/utils.cpp
        ants/common/header/utils.hpp
        ants/common/source/Ants.cpp
        ants/common/header/Ants.hpp
        ants/common/source/Rooms.cpp
        ants/common/header/Rooms.hpp
        ants/common/source/ants_pathfinders.cpp
        ants/common/header/ants_pathfinders.hpp)
