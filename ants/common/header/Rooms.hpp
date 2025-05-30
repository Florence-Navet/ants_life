//
// Created by josur on 20/05/2025.
//

#ifndef ROOMS_HPP
#define ROOMS_HPP

#include <utility>

#include "utils.hpp"

class Ants;
class Anthills;

class Rooms {
public:
    string name;
    int capacity;
    unsigned long long number_of_paths = 0;
    vector<weak_ptr<Rooms>> next_rooms;
    int occupying_ants = 0;
    bool flagged_as_dead_end = false;

    explicit Rooms(string name, const int capacity = 1) : name(move(name)), capacity(capacity){}

    void declare_paths(const vector<weak_ptr<Rooms>> &next_rooms) {
        this->next_rooms = next_rooms;
        this->number_of_paths = next_rooms.size();
    }

    bool is_room_free() const {
        return capacity - occupying_ants > 0;
    }

    bool is_room_flagged_dead_end() const {
        return flagged_as_dead_end;
    }

    void flag_as_dead_end() {
        flagged_as_dead_end = true;
    }

    void enter_room() {
        occupying_ants++;
    }
    void leave_room() {
        occupying_ants--;
    }

};

#endif //ROOMS_HPP