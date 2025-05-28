//
// Created by josur on 20/05/2025.
//

#include "utils.hpp"

anthill_basic_information read_anthill_json_file(const int anthill_index) {

    anthill_basic_information anthill;

    ifstream anthill_info_file("../ants/anthills.json");

    basic_json<> data = json::parse(anthill_info_file);

    basic_json<> chosen_anthill_data = data.at(anthill_names.at(anthill_index));

    anthill.id = chosen_anthill_data.at("id");
    anthill.number_of_rooms = chosen_anthill_data.at("number_of_rooms");
    anthill.number_of_ants = chosen_anthill_data.at("number_of_ants");

    for (const auto &data_vector_units : chosen_anthill_data.at("rooms_different_capacity")) {
        anthill.rooms_different_capacity.push_back(data_vector_units);
    }

    for (const auto &data_vector_unit : chosen_anthill_data.at("different_capacities")) {
        anthill.different_capacities.push_back(data_vector_unit);
    }

    return anthill;
}

vector<vector<int>> read_anthill_paths_json_file(const int anthill_index) {

    vector<vector<int>> anthill_paths;

    ifstream anthill_paths_file("../ants/anthills_paths.json");

    basic_json<> data = json::parse(anthill_paths_file);

    basic_json<> chosen_anthill_data = data.at(anthill_names.at(anthill_index));

    anthill_paths.resize(chosen_anthill_data.size());

    int vector_index = 0;

    for (const basic_json<>& paths_vector : chosen_anthill_data) {

        anthill_paths.at(vector_index).reserve(paths_vector.size());

        for (const int room_index : paths_vector) {

            anthill_paths.at(vector_index).push_back(room_index);
        }

        vector_index++;
    }

    return anthill_paths;
}