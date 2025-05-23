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
    Anthills() {}

    int anthill_id{};
    int number_of_rooms{};
    int number_of_ants{};

    vector<int> rooms_different_capacity;
    vector<int> capacities;

    vector<shared_ptr<Ants>> saved_ants;

    vector<shared_ptr<Rooms>> saved_rooms;
    vector<weak_ptr<Rooms>> pointer_rooms;

    void define_basic_information(
        int anthill_id, int number_of_rooms, int number_of_ants,
        vector<int> rooms_different_capacity = {}, vector<int> capacities = {}
        );

    void generate_ants();
    void generate_rooms();
    void generate_paths() const;

    void anthill_zero() const;
    void anthill_one() const;
    void anthill_two() const;
    void anthill_three() const;
    void anthill_four() const;
    void anthill_five() const;

    void reset_rooms();
    void reset_ants();
};

void anthill_zero(const vector<shared_ptr<Rooms>> *saved_rooms, const vector<weak_ptr<Rooms>> *pointer_rooms);

#endif //ANTHILLS_HPP
