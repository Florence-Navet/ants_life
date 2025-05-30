//
// Created by josur on 20/05/2025.
//

#ifndef ANTHILLS_H
#define ANTHILLS_H

#include "utils.h"

class Rooms;
class Ants;

class Anthills
{
public:
    explicit Anthills(const anthill_basic_information &anthill_info) : anthill_id(anthill_info.id),
                                                                       number_of_rooms(anthill_info.number_of_rooms),
                                                                       number_of_ants(anthill_info.number_of_ants),
                                                                       rooms_different_capacity(anthill_info.rooms_different_capacity),
                                                                       different_capacities(anthill_info.different_capacities)
    {

        this->saved_rooms.resize(number_of_rooms + 2);
        this->pointer_rooms.resize(number_of_rooms + 2);
        this->saved_ants.resize(number_of_ants);

        generate_rooms();
        generate_ants();
        generate_paths();
    };

    ~Anthills()
    {
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

    bool ants_home = false;
    long int rounds = 0;
    long int first_round_in_dorms = 0;

    void start_finding_dorms();

    void reset_rooms();
    void reset_ants();
};

#endif // ANTHILLS_HPP
