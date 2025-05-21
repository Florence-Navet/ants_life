//
// Created by josur on 20/05/2025.
//

#ifndef ROOMS_HPP
#define ROOMS_HPP

#include "utils.hpp"

namespace ants_life {

class Rooms {
public:
    string name;
    int number_of_paths = 0;
    // Rooms **next_rooms{};
    explicit Rooms(string name) : name(std::move(name)) {}
    Rooms(const Rooms&) = delete;
    ~Rooms() = default;
    Rooms& operator=(const Rooms&) = delete;

    // void declare_number_of_paths(const int number_of_paths) {
    //     next_rooms = new Rooms*[number_of_paths];
    // }

};

} // ants_life

#endif //ROOMS_HPP
