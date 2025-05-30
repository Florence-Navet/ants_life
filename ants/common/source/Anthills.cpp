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
}

void Anthills::start_finding_dorms() {

    bool first_found_dorms = false;

    while (!ants_home) {
        rounds++;

        cout << "Etape " << rounds << endl;

        for (const shared_ptr<Ants>& ant : saved_ants) {
            ant->act();
            if (ant->ant_action != Ants::IN_DORMS) {
                cout << ant->ant_status << endl;
            }
        }
        if (saved_rooms.at(number_of_rooms + 1)->occupying_ants > 0 && first_found_dorms == false) {
            first_found_dorms = true;
            first_round_in_dorms = rounds;
        }
        if (saved_rooms.at(number_of_rooms + 1)->occupying_ants == number_of_ants) {
            ants_home = true;
            cout << "Toutes les fourmies sont rentrees au dortoir !!\n Fourmilliere finie en " <<
                rounds << " etapes !" << endl;
        }
        if (rounds > 500) {
            cout << "Les fourmis ne rentreront jamais au dortoirs...." << endl;
            return;
        }
    }
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

