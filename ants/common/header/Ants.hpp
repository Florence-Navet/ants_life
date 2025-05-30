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

    vector<weak_ptr<Rooms>> explored_rooms;
    vector<weak_ptr<Rooms>> path_from_entry;

    int ant_action = 0;

    string ant_status;

    enum ant_action {
        WAIT,
        GO_BACK,
        EXPLORE,
        MOVE_TOWARDS_DORMS,
        FOUND_DORMS,
        IN_DORMS
    };

    vector<function<void()>> ant_actions;

    static vector<vector<weak_ptr<Rooms>>> found_paths;

    struct compare_by_size {
        bool operator() (const vector<weak_ptr<Rooms>> &path_a, const vector<weak_ptr<Rooms>> &path_b) const;
    };

    static void sort_found_paths();

    explicit Ants(const int id, const weak_ptr<Rooms> &current_room) : id(id), current_room(current_room) {
        explored_rooms.push_back(current_room);

        ant_actions = {
            [this] { ant_status_wait(); },
            [this] { ant_status_go_back(); },
            [this] { ant_status_explore(); },
            [this] { ant_status_move_towards_dorms(); },
            [this] { ant_status_found_dorms(); },
            [this] { ant_status_in_dorms(); }
        };
    };

    bool is_path_dead_end() const;

    void act();

    void check_paths();
    bool check_found_paths();
    bool check_dead_end();
    bool check_in_or_near_dorms();
    bool check_for_clear_path();

    void ant_status_explore();
    void ant_status_move_towards_dorms ();
    void ant_status_go_back ();
    void ant_status_wait();
    void ant_status_in_dorms();
    void ant_status_found_dorms ();

    void ant_found_dorms();
};

#endif //ANTS_HPP
