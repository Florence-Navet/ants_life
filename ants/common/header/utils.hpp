//
// Created by josur on 20/05/2025.
//

#ifndef UTILS_HPP
#define UTILS_HPP

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

typedef struct {
    int id;
    int number_of_ants;
    int number_of_rooms;
    vector<int> rooms_different_capacity;
    vector<int> different_capacities;
} anthill_basic_information;

const array<string, 9> anthill_names = {
    "anthill_1",
    "anthill_2",
    "anthill_3",
    "anthill_4",
    "anthill_5",
    "anthill_6",
    "anthill_3d",
    "anthill_everything",
    "anthill_waiting"
};

anthill_basic_information read_anthill_json_file(int anthill_index);

vector<vector<int>> read_anthill_paths_json_file(int anthill_index);


#if defined(ANTS_HPP) & !defined(ANTS_INCLUDED)
    #define ANTS_INCLUDED

    #include "Rooms.hpp"

#endif //ANTS_INCLUDED

#if defined(MAIN_HPP) & !defined(MAIN_INCLUDED)
    #define MAIN_INCLUDED

    #include "Rooms.hpp"
    #include "Ants.hpp"
    #include "Anthills.hpp"

#endif //MAIN_INCLUDED

#if defined(ANTHILLS_HPP) & !defined(ANTHILLS_INCLUDED)
    #define ANTHILLS_INCLUDED

    #include "Ants.hpp"
    #include "Rooms.hpp"

#endif //ANTHILLS_INCLUDED

#endif //UTILS_HPP
