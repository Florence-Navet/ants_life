//
// Created by josur on 20/05/2025.
//

#ifndef ANTHILLS_HPP
#define ANTHILLS_HPP

#include "utils.hpp"

class Rooms;
class Ants;

class Anthills {
public:
    explicit Anthills(const anthill_basic_information& anthill_info) :
        anthill_id(anthill_info.id),
        number_of_rooms(anthill_info.number_of_rooms),
        number_of_ants(anthill_info.number_of_ants),
        rooms_different_capacity(anthill_info.rooms_different_capacity),
        different_capacities(anthill_info.different_capacities) {

        this->saved_rooms.resize(number_of_rooms + 2);
        this->pointer_rooms.resize(number_of_rooms + 2);
        this->saved_ants.resize(number_of_ants);

        generate_rooms();
        generate_ants();
        generate_paths();
    };

    ~Anthills() {
        reset_ants();
        reset_rooms();
    }

    int anthill_id{};
    int number_of_rooms{};
    int number_of_ants{};

    vector<int> rooms_different_capacity;
    vector<int> different_capacities;

    vector<shared_ptr<Ants>> saved_ants;

    vector<shared_ptr<Rooms>> saved_rooms;
    vector<weak_ptr<Rooms>> pointer_rooms;

    void generate_ants();
    void generate_rooms();
    void generate_paths() const;

    void anthill_zero() const;
    void anthill_one() const;
    void anthill_two() const;
    void anthill_three() const;
    void anthill_four() const;
    void anthill_five() const;

    void anthill_everything() const;
    void anthill_3d() const;
    void anthill_waiting() const;

    void anthill_corridors() const;

    void reset_rooms();
    void reset_ants();
};

#endif //ANTHILLS_HPP
