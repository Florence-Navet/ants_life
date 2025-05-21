//
// Created by josur on 20/05/2025.
//

#ifndef ANTS_HPP
#define ANTS_HPP

#include "utils.hpp"

class Rooms;

class Ants {
public:
    int id;
    weak_ptr<Rooms> current_room;
    vector<shared_ptr<Rooms>> explored_rooms;

    explicit Ants(const int id, const weak_ptr<Rooms> &current_room) : id(id), current_room(current_room) {};

};

#endif //ANTS_HPP
