//
// Created by josur on 20/05/2025.
//

#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <utility>
#include <memory>
#include <algorithm>
#include <vector>
#include <functional>
#include <nlohmann/json.hpp>
#include <fstream>

using namespace std;
using namespace nlohmann;

typedef struct
{
    int id;
    int number_of_ants;
    int number_of_rooms;
    vector<int> rooms_different_capacity;
    vector<int> different_capacities;
} anthill_basic_information;

const array<string, 10> anthill_names = {
    "anthill_0",
    "anthill_1",
    "anthill_2",
    "anthill_3",
    "anthill_4",
    "anthill_5",
    "anthill_3d",
    "anthill_everything",
    "anthill_waiting",
    "anthill_corridors"};

anthill_basic_information read_anthill_json_file(int anthill_index);

vector<vector<int>> read_anthill_paths_json_file(int anthill_index);

#if defined(ANTS_H) & !defined(ANTS_INCLUDED)
#define ANTS_INCLUDED

#include "Rooms.h"

#endif // ANTS_INCLUDED

#if defined(MAIN_H) & !defined(MAIN_INCLUDED)
#define MAIN_INCLUDED

#include "Rooms.h"
#include "Ants.h"
#include "Anthills.h"

#endif // MAIN_INCLUDED

#if defined(ANTHILLS_H) & !defined(ANTHILLS_INCLUDED)
#define ANTHILLS_INCLUDED

#include "Ants.h"
#include "Rooms.h"

#endif // ANTHILLS_INCLUDED

#endif // UTILS_HPP
