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
        ants/anthills.json
        ants/anthills_paths.json
        ants/source/main.cpp
        ants/header/main.h
        ants/common/source/Ants.cpp
        ants/common/header/Ants.h
        ants/common/source/utils.cpp
        ants/common/header/utils.h
        ants/common/source/Rooms.cpp
        ants/common/header/Rooms.h
        ants/common/source/Anthills.cpp
        ants/common/header/Anthills.h)
