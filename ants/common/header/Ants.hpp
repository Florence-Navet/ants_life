//
// Created by josur on 20/05/2025.
//

#ifndef ANTS_HPP
#define ANTS_HPP

#include "utils.hpp"

class Rooms;
class Anthills;

class Ants {
public:
    int id;
    weak_ptr<Rooms> current_room;
    weak_ptr<Rooms> next_room;
    string ant_status;

    vector<weak_ptr<Rooms>> explored_rooms;
    vector<weak_ptr<Rooms>> path_from_entry;

    static vector<vector<weak_ptr<Rooms>>> found_paths;

    explicit Ants(const int id, const weak_ptr<Rooms> &current_room) : id(id), current_room(current_room) {};

    int check_paths();

    void act();

    void ant_move(bool went_back=false);

    void ant_wait(bool wait_in_dorms=false);
};

#endif //ANTS_HPP
