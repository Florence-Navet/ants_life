cmake_minimum_required(VERSION 3.31)
project(ants_life)

set(CMAKE_CXX_STANDARD 14)

include_directories(ants)
include_directories(ants/source)
include_directories(ants/header)
include_directories(ants/common)
include_directories(ants/common/header)
include_directories(ants/common/source)

add_executable(ants_life
        ants/source/main.cpp
        ants/header/main.hpp
        ants/common/source/Ants.cpp
        ants/common/header/Ants.hpp
        ants/common/source/utils.cpp
        ants/common/header/utils.hpp
        ants/common/source/Rooms.cpp
        ants/common/header/Rooms.hpp
        ants/common/source/Anthills.cpp
        ants/common/header/Anthills.hpp)
