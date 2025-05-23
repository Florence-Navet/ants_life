//
// Created by josur on 20/05/2025.
//

#include "Ants.hpp"

int Ants::check_paths() {
    // return -1 : wait, 0 : go back, 1 : explore, 2 : move towards dorms, 3 : found dorms, 4: wait in dorms, no print

    string sd_name = "Sd";

    if (current_room.lock()->name == sd_name) {
        return 4;
    }

    const auto dorms_iterator = find_if(
        current_room.lock()->next_rooms.begin(),
        current_room.lock()->next_rooms.end(),
        [&sd_name](const weak_ptr<Rooms> &room) {
            return room.lock()->name == sd_name;
        });

    if (dorms_iterator != current_room.lock()->next_rooms.end()) {
        this->next_room = *dorms_iterator;
        return 3;
    }

    for (vector<weak_ptr<Rooms> > &found_path: found_paths) {
        const auto room_to_dorms_iterator = find_if(
            found_path.begin(),
            found_path.end(),
            [this](const weak_ptr<Rooms> &room) {
                const auto potential_room = find_if(
                    current_room.lock()->next_rooms.begin(),
                    current_room.lock()->next_rooms.end(),
                    [&room](const weak_ptr<Rooms> &explorable_room) {
                        return room.lock() == explorable_room.lock();
                });
                if (potential_room != current_room.lock()->next_rooms.end()) {
                    return room.lock()->is_room_free();
                }
                return false;
            });
        if (room_to_dorms_iterator != found_path.end()) {
            next_room = *room_to_dorms_iterator;
            return 2;
        }
    }

    const auto free_room_iterator = find_if(
        current_room.lock()->next_rooms.begin(),
        current_room.lock()->next_rooms.end(),
        [this](const weak_ptr<Rooms> &room) {

            const auto iterator = find_if(
                explored_rooms.begin(),
                explored_rooms.end(),
                [&room](const weak_ptr<Rooms> &explore_room) {
                    return room.lock() == explore_room.lock();
                });

            if (iterator != explored_rooms.end()) {
                return false;
            }
            return room.lock()->is_room_free();
        });

    if (free_room_iterator != current_room.lock()->next_rooms.end()) {
        this->next_room = *free_room_iterator;
        return 1;
    }

    if (path_from_entry.empty() == false && current_room.lock()->next_rooms.size() == 1) {
        const auto entry_iterator = path_from_entry.end() - 1;
        const long long unsigned index = distance(path_from_entry.begin(), entry_iterator);
        if (path_from_entry.at(index).lock()->is_room_free()) {
            next_room = *entry_iterator;
            return 0;
        }
    }

    return -1;
}

void Ants::act() {
    ant_action = check_paths();

    if (ant_action == -1 || ant_action == 4) {
        ant_wait();
    }else {
        ant_move();

        if (ant_action == 3) {
            path_from_entry.push_back(current_room);
            for (auto vector_iterator = found_paths.begin(); vector_iterator != found_paths.end(); ++vector_iterator) {
                const long long unsigned vector_index = distance(found_paths.begin(), vector_iterator);
                bool path_different = false;
                for (auto weak_ptr_iterator = found_paths.at(vector_index).begin(); weak_ptr_iterator != found_paths.at(vector_index).end(); ++weak_ptr_iterator) {
                    const long long unsigned weak_ptr_index = distance(found_paths.at(vector_index).begin(), weak_ptr_iterator);
                    if (found_paths.at(vector_index).at(weak_ptr_index).lock() != path_from_entry.at(weak_ptr_index).lock()) {
                        path_different = true;
                        break;
                    }
                }
                if (path_different == true) {
                    found_paths.push_back(path_from_entry);
                    break;
                }
            }
        }
    }
    //debug for ant 48
    if (id == 48) {
        cout << endl;
    }
}

void Ants::ant_move() {
    ant_status = "La fourmi " + to_string(id) + " se deplace de la salle " +
        current_room.lock()->name + " vers la salle " + next_room.lock()->name + "\n";

    current_room.lock()->leave_room();

    if (ant_action == 0) {
        path_from_entry.pop_back();
    } else {
        path_from_entry.push_back(current_room);
    }

    bool room_explored = false;
    for (weak_ptr<Rooms> &room : explored_rooms) {
        if (current_room.lock() == room.lock()) {
            room_explored = true;
            break;
        }
    }
    if (room_explored == false) {
        explored_rooms.push_back(current_room);
    }

    next_room.lock()->enter_room();
    current_room = next_room;
}

void Ants::ant_wait() {
    if (ant_action == 4) {
        ant_status = "";
    } else {
        ant_status = "La fourmi " + to_string(id) + " attend en salle " + current_room.lock()->name + ".\n";
    }
}
