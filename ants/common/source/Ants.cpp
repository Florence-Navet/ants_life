//
// Created by josur on 20/05/2025.
//

#include "Ants.hpp"

bool Ants::compare_by_size::operator()(const vector<weak_ptr<Rooms> > &path_a, const vector<weak_ptr<Rooms> > &path_b) const {
    if (path_a.size() == path_b.size()) {
        int path_a_capacity = 0;
        int path_b_capacity = 0;
        for (const weak_ptr<Rooms> &room : path_a) {
            path_a_capacity += room.lock()->capacity;
        }
        for (const weak_ptr<Rooms> &room : path_b) {
            path_b_capacity += room.lock()->capacity;
        }
        return path_a_capacity > path_b_capacity;
    }
    return (path_a.size() < path_b.size());
}

void Ants::sort_found_paths() {
    if (found_paths.size() > 1) {
        sort(found_paths.begin(), found_paths.end(), compare_by_size());
    }
}

void Ants::check_paths() {
    bool ant_acted = false;

    ant_acted = check_in_or_near_dorms();
    if (ant_acted == true) {
        return;
    }

    ant_acted = check_found_paths();
    if (ant_acted == true) {
        return;
    }

    ant_acted = check_dead_end();
    if (ant_acted == true) {
        return;
    }

    ant_acted = check_for_clear_path();
    if (ant_acted == true) {
        return;
    }

    ant_action = WAIT;
}

bool Ants::check_in_or_near_dorms() {
    // Check if ant is in dorms
    const string sd_name = "Sd";

    if (current_room.lock()->name == sd_name) {

        ant_action = IN_DORMS;
        return true;
    }

    // Look for dorms near ant's current room
    for (const weak_ptr<Rooms> &searching_dorms : current_room.lock()->next_rooms) {

        if (searching_dorms.lock()->name == sd_name) {

            next_room = searching_dorms.lock();
            ant_action = FOUND_DORMS;
            return true;
        }
    }

    return false;
}

bool Ants::check_found_paths() {
    // Look for a known path that lead to the dorms

    for (vector<weak_ptr<Rooms> > &found_path: found_paths) {

        for (
            auto known_room_iterator = found_path.rbegin();
            known_room_iterator != found_path.rend();
            ++known_room_iterator) {

            for (weak_ptr<Rooms> &potential_room : current_room.lock()->next_rooms) {

                if (potential_room.lock() == known_room_iterator->lock() &&
                    potential_room.lock()->is_room_free()) {

                    if (path_from_entry.empty() == false) {

                        if (potential_room.lock() == path_from_entry.at(path_from_entry.size() - 1).lock()) {

                            if (current_room.lock()->number_of_paths == 1 ||
                                current_room.lock()->is_room_flagged_dead_end() == true ||
                                is_path_dead_end() == true) {

                                current_room.lock()->flag_as_dead_end();
                            }

                            next_room = potential_room;
                            ant_action = GO_BACK;
                            return true;
                        }
                    }
                    if (path_from_entry.empty() ||
                        potential_room.lock() != path_from_entry.at(path_from_entry.size() - 1).lock()) {

                            next_room = potential_room;
                            ant_action = MOVE_TOWARDS_DORMS;
                            return true;
                    }
                }
            }
        }
    }

    return false;
}

bool Ants::check_dead_end() {
    // Check if ant is in a dead-end and go back if possible
    if (path_from_entry.empty() == false) {

        const weak_ptr<Rooms> &entry_room = path_from_entry.at(path_from_entry.size() - 1);

        if (current_room.lock()->number_of_paths == 1 ||
            is_path_dead_end() == true ||
            current_room.lock()->is_room_flagged_dead_end() == true) {

            current_room.lock()->flag_as_dead_end();

            if (entry_room.lock()->is_room_free()) {
                // current_room.lock()->flag_as_dead_end();
                next_room = entry_room;
                ant_action = GO_BACK;
                return true;
            }

            ant_action = WAIT;
            return true;
        }
    }
    return false;
}

bool Ants::check_for_clear_path() {
    // Search for a free room ahead to explore
    for (weak_ptr<Rooms> &near_room : current_room.lock()->next_rooms) {

        for (weak_ptr<Rooms> &explored_room : explored_rooms) {

            if (near_room.lock() != explored_room.lock() &&
                near_room.lock()->is_room_free()) {

                next_room = near_room;
                ant_action = EXPLORE;
                return true;
            }
        }
    }

    return false;
}

bool Ants::is_path_dead_end() const {

    bool path_is_dead_end = true;

    if (path_from_entry.empty() == false) {

        for (weak_ptr<Rooms> &near_room : current_room.lock()->next_rooms) {

            if (near_room.lock() != path_from_entry.at(path_from_entry.size() - 1).lock()) {

                if (near_room.lock()->is_room_flagged_dead_end() == false) {

                    path_is_dead_end = false;
                }
            }
        }
    }
    return path_is_dead_end;
}

void Ants::act() {

    check_paths();

    ant_actions.at(ant_action)();

    if (ant_action != WAIT && ant_action != IN_DORMS) {
        current_room.lock()->leave_room();

        if (ant_action == GO_BACK) {
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
    } else if (ant_action == FOUND_DORMS) {
        ant_found_dorms();
    }
}

void Ants::ant_status_explore() {
    ant_status = "La fourmi " + to_string(id) + " explore en allant de la salle " +
        current_room.lock()->name + " vers la salle " + next_room.lock()->name + "\n";
}

void Ants::ant_status_move_towards_dorms () {
    ant_status = "La fourmi " + to_string(id) + " suit le chemin vers le dortoir de la salle " +
        current_room.lock()->name + " vers la salle " + next_room.lock()->name + "\n";
}

void Ants::ant_status_go_back () {
    ant_status = "La fourmi " + to_string(id) + " fait demi-tour de la salle " +
        current_room.lock()->name + " vers la salle " + next_room.lock()->name + "\n";
}

void Ants::ant_status_wait() {
    ant_status = "La fourmi " + to_string(id) + " attend en salle " +
        current_room.lock()->name + ".\n";
}

void Ants::ant_status_in_dorms() {
    ant_status = "";
}

void Ants::ant_status_found_dorms () {
    ant_status = "La fourmi " + to_string(id) + " trouve et entre dans le dortoir depuis la salle " +
        current_room.lock()->name + "\n";
}

void Ants::ant_found_dorms() {
    path_from_entry.push_back(current_room);

    if (found_paths.empty() == true) {
        found_paths.push_back(path_from_entry);
        return;
    }

    bool existing_path = false;

    for (auto vector_iterator = found_paths.begin(); vector_iterator != found_paths.end(); ++vector_iterator) {

        bool same_path = true;
        const long long unsigned vector_index = distance(found_paths.begin(), vector_iterator);

        if (found_paths.at(vector_index).size() != path_from_entry.size()) {
            continue;
        }

        for (auto weak_ptr_iterator = found_paths.at(vector_index).begin();
             weak_ptr_iterator != found_paths.at(vector_index).end();
             ++weak_ptr_iterator) {

            const long long unsigned weak_ptr_index = distance(
                found_paths.at(vector_index).begin(),
                weak_ptr_iterator
                );

            if (found_paths.at(vector_index).at(weak_ptr_index).lock() != path_from_entry.at(weak_ptr_index).lock()) {
                same_path = false;
            }
        }
        if (same_path == true) {
            existing_path = true;
        }
    }
    if (existing_path == false) {
        found_paths.push_back(path_from_entry);
        sort_found_paths();
    }
}

