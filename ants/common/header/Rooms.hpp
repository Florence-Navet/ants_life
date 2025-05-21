//
// Created by josur on 20/05/2025.
//

#ifndef ROOMS_HPP
#define ROOMS_HPP

#include "utils.hpp"

class Rooms {
public:
    string name;
    int capacity;
    unsigned long long number_of_paths = 0;
    std::vector<weak_ptr<Rooms>> next_rooms;
    int occupying_ants;

    explicit Rooms(string name, const int capacity = 1) : name(move(name)), capacity(capacity){}
    // Rooms(const Rooms&) = delete;
    // ~Rooms() = default;
    // Rooms& operator=(const Rooms&) = delete;

    void declare_paths(const vector<weak_ptr<Rooms>> &next_rooms) {
        this->next_rooms = next_rooms;
        this->number_of_paths = next_rooms.size();
    }

};

#endif //ROOMS_HPP
