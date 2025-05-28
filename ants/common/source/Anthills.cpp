//
// Created by josur on 20/05/2025.
//

#include "Anthills.hpp"

void Anthills::generate_ants() {
    for (int x = 0 ; x < number_of_ants ; x++) {
        saved_ants.at(x) = make_shared<Ants>(x + 1, pointer_rooms.at(0));
    }
}

void Anthills::generate_rooms() {
    saved_rooms.at(0) = make_shared<Rooms>("Sv", number_of_ants);
    saved_rooms.at(0)->occupying_ants = number_of_ants;

    for (int x = 1 ; x <= number_of_rooms ; x++) {
        saved_rooms.at(x) = make_shared<Rooms>("S" + to_string(x));

        if (rooms_different_capacity.empty() == false) {
            auto room_capacity_iterator = find(
                rooms_different_capacity.begin(),
                rooms_different_capacity.end(), x
                );

            if (room_capacity_iterator != rooms_different_capacity.end()) {
                const long long unsigned index = distance(
                    rooms_different_capacity.begin(),
                    room_capacity_iterator
                    );
                saved_rooms.at(x)->capacity = this->different_capacities.at(index);
            }
        }
    }

    saved_rooms.at(number_of_rooms + 1) = make_shared<Rooms>("Sd", number_of_ants);

    for (auto iterator = saved_rooms.begin(); iterator != saved_rooms.end(); ++iterator) {
        const long long index = distance(saved_rooms.begin(), iterator);
        const weak_ptr<Rooms> room_ptr = saved_rooms.at(index);
        pointer_rooms.at(index) = room_ptr;
    }
}

void Anthills::generate_paths() const {

    const vector<vector<int>> anthill_zero_path = read_anthill_paths_json_file(anthill_id);

    for (int vector_index = 0; vector_index != anthill_zero_path.size(); vector_index++) {

        vector<weak_ptr<Rooms>> next_rooms;

        next_rooms.reserve(anthill_zero_path.at(vector_index).size());

        for (const int index : anthill_zero_path.at(vector_index)) {
            next_rooms.push_back(pointer_rooms.at(index));
        }

        saved_rooms.at(vector_index)->declare_paths(next_rooms);
        cout << endl;
    }

    // const vector<function<void()>> anthill_path_generation = {
    //     [this]{ anthill_zero(); },
    //     [this]{ anthill_one(); },
    //     [this]{ anthill_two(); },
    //     [this]{ anthill_three(); },
    //     [this]{ anthill_four(); },
    //     [this]{ anthill_five(); },
    //     [this]{ anthill_everything(); },
    //     [this]{ anthill_3d(); },
    //     [this]{ anthill_waiting(); },
    //     [this]{ anthill_corridors(); }
    // };
    //
    // anthill_path_generation.at(anthill_id)();
}

void Anthills::reset_rooms() {
    for (shared_ptr<Rooms> &room : saved_rooms) {
        room.reset();
    }
}

void Anthills::reset_ants() {
    for (shared_ptr<Ants> &ant : saved_ants) {
        ant.reset();
    }
}

