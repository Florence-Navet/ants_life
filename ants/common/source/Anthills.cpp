//
// Created by josur on 20/05/2025.
//

#include "Anthills.hpp"

void  Anthills::define_basic_information(const int anthill_id,
        const int number_of_rooms, const int number_of_ants,
        vector<int> rooms_different_capacity, vector<int> capacities) {
    this->anthill_id = anthill_id;
    this->number_of_rooms = number_of_rooms;
    this->number_of_ants = number_of_ants;
    this->rooms_different_capacity = move(rooms_different_capacity);
    this->capacities = move(capacities);

    this->saved_rooms.resize(number_of_rooms + 2);
    this->pointer_rooms.resize(number_of_rooms + 2);
    this->saved_ants.resize(number_of_ants);
};

void Anthills::generate_ants() {
    for (int x = 0 ; x < number_of_ants ; x++) {
        saved_ants.at(x) = make_shared<Ants>(x + 1, pointer_rooms.at(0));
    }
}

void Anthills::generate_rooms() {
    saved_rooms.at(0) = make_shared<Rooms>("Sv", number_of_ants);
    saved_rooms.at(0)->occupying_ants = number_of_ants;

    for (int x = 1 ; x <= number_of_rooms ; x++) {
        saved_rooms.at(x) = make_shared<Rooms>("S" + to_string(x));

        if (rooms_different_capacity.empty() == false) {
            auto room_capacity_iterator = find(
                rooms_different_capacity.begin(),
                rooms_different_capacity.end(), x
                );

            if (room_capacity_iterator != rooms_different_capacity.end()) {
                const long long unsigned index = distance(
                    rooms_different_capacity.begin(),
                    room_capacity_iterator
                    );
                saved_rooms.at(x)->capacity = capacities.at(index);
            }
        }
    }

    saved_rooms.at(number_of_rooms + 1) = make_shared<Rooms>("Sd", number_of_ants);

    for (auto iterator = saved_rooms.begin(); iterator != saved_rooms.end(); ++iterator) {
        const long long index = distance(saved_rooms.begin(), iterator);
        const weak_ptr<Rooms> room_ptr = saved_rooms.at(index);
        pointer_rooms.at(index) = room_ptr;
    }
}

void Anthills::generate_paths() const {
    switch (this->anthill_id) {

            case 0:
            anthill_zero();
            break;

            case 1:
            anthill_one();
            break;

            case 2:
            anthill_two();
            break;

            case 3:
            anthill_three();
            break;

            case 4:
            anthill_four();
            break;

            case 5:
            anthill_five();
            break;

        default:
            return;
    }
}

void Anthills::anthill_zero() const {
    const vector<weak_ptr<Rooms>> sv_next_rooms = {pointer_rooms.at(1)};
    saved_rooms.at(0)->declare_paths(sv_next_rooms);

    const vector<weak_ptr<Rooms>> s1_next_rooms = {pointer_rooms.at(0), pointer_rooms.at(2)};
    saved_rooms.at(1)->declare_paths(s1_next_rooms);

    const vector<weak_ptr<Rooms>> s2_next_rooms = {pointer_rooms.at(1), pointer_rooms.at(3)};
    saved_rooms.at(2)->declare_paths(s2_next_rooms);

    const vector<weak_ptr<Rooms>> sd_next_rooms = {pointer_rooms.at(2)};
    saved_rooms.at(3)->declare_paths(sd_next_rooms);
    cout << endl;
}

void Anthills::anthill_one() const {
    const vector<weak_ptr<Rooms>> sv_next_rooms = {pointer_rooms.at(1), pointer_rooms.at(2)};
    saved_rooms.at(0)->declare_paths(sv_next_rooms);

    const vector<weak_ptr<Rooms>> s1_next_rooms = {pointer_rooms.at(0), pointer_rooms.at(3)};
    saved_rooms.at(1)->declare_paths(s1_next_rooms);

    const vector<weak_ptr<Rooms>> s2_next_rooms = {pointer_rooms.at(0), pointer_rooms.at(3)};
    saved_rooms.at(2)->declare_paths(s2_next_rooms);

    const vector<weak_ptr<Rooms>> sd_next_rooms = {pointer_rooms.at(1), pointer_rooms.at(2)};
    saved_rooms.at(3)->declare_paths(sd_next_rooms);
}

void Anthills::anthill_two() const {
    const vector<weak_ptr<Rooms>> sv_next_rooms = {pointer_rooms.at(1), pointer_rooms.at(3)};
    saved_rooms.at(0)->declare_paths(sv_next_rooms);

    const vector<weak_ptr<Rooms>> s1_next_rooms = {pointer_rooms.at(0), pointer_rooms.at(2)};
    saved_rooms.at(1)->declare_paths(s1_next_rooms);

    const vector<weak_ptr<Rooms>> s2_next_rooms = {pointer_rooms.at(1), pointer_rooms.at(3)};
    saved_rooms.at(2)->declare_paths(s2_next_rooms);

    const vector<weak_ptr<Rooms>> sd_next_rooms = {pointer_rooms.at(0), pointer_rooms.at(2)};
    saved_rooms.at(3)->declare_paths(sd_next_rooms);
}

void Anthills::anthill_three() const {
    const vector<weak_ptr<Rooms>> sv_next_rooms = {pointer_rooms.at(1)};
    saved_rooms.at(0)->declare_paths(sv_next_rooms);

    const vector<weak_ptr<Rooms>> s1_next_rooms = {pointer_rooms.at(0), pointer_rooms.at(2),
        pointer_rooms.at(4)};
    saved_rooms.at(1)->declare_paths(s1_next_rooms);

    const vector<weak_ptr<Rooms>> s2_next_rooms = {pointer_rooms.at(1), pointer_rooms.at(3)};
    saved_rooms.at(2)->declare_paths(s2_next_rooms);

    const vector<weak_ptr<Rooms>> s3_next_rooms = {pointer_rooms.at(2)};
    saved_rooms.at(3)->declare_paths(s3_next_rooms);

    const vector<weak_ptr<Rooms>> s4_next_rooms = {pointer_rooms.at(1), pointer_rooms.at(5)};
    saved_rooms.at(4)->declare_paths(s4_next_rooms);

    const vector<weak_ptr<Rooms>> sd_next_rooms = {pointer_rooms.at(4)};
    saved_rooms.at(5)->declare_paths(sd_next_rooms);
}

void Anthills::anthill_four() const {
    const vector<weak_ptr<Rooms>> sv_next_rooms = {pointer_rooms.at(1)};
    saved_rooms.at(0)->declare_paths(sv_next_rooms);

    const vector<weak_ptr<Rooms>> s1_next_rooms = {pointer_rooms.at(0), pointer_rooms.at(2),
        pointer_rooms.at(3)};
    saved_rooms.at(1)->declare_paths(s1_next_rooms);

    const vector<weak_ptr<Rooms>> s2_next_rooms = {pointer_rooms.at(1), pointer_rooms.at(4)};
    saved_rooms.at(2)->declare_paths(s2_next_rooms);

    const vector<weak_ptr<Rooms>> s3_next_rooms = {pointer_rooms.at(1), pointer_rooms.at(4)};
    saved_rooms.at(3)->declare_paths(s3_next_rooms);

    const vector<weak_ptr<Rooms>> s4_next_rooms = {pointer_rooms.at(2), pointer_rooms.at(3),
        pointer_rooms.at(5), pointer_rooms.at(6)};
    saved_rooms.at(4)->declare_paths(s4_next_rooms);

    const vector<weak_ptr<Rooms>> s5_next_rooms = {pointer_rooms.at(4), pointer_rooms.at(7)};
    saved_rooms.at(5)->declare_paths(s5_next_rooms);

    const vector<weak_ptr<Rooms>> s6_next_rooms = {pointer_rooms.at(4), pointer_rooms.at(7)};
    saved_rooms.at(6)->declare_paths(s6_next_rooms);

    const vector<weak_ptr<Rooms>> sd_next_rooms = {pointer_rooms.at(5), pointer_rooms.at(6)};
    saved_rooms.at(7)->declare_paths(sd_next_rooms);
}

void Anthills::anthill_five() const {
    const vector<weak_ptr<Rooms>> sv_next_rooms = {pointer_rooms.at(1)};
    saved_rooms.at(0)->declare_paths(sv_next_rooms);

    const vector<weak_ptr<Rooms>> s1_next_rooms = {pointer_rooms.at(0), pointer_rooms.at(2),
        pointer_rooms.at(6)};
    saved_rooms.at(1)->declare_paths(s1_next_rooms);

    const vector<weak_ptr<Rooms>> s2_next_rooms = {pointer_rooms.at(1), pointer_rooms.at(3),
        pointer_rooms.at(5)};
    saved_rooms.at(2)->declare_paths(s2_next_rooms);

    const vector<weak_ptr<Rooms>> s3_next_rooms = {pointer_rooms.at(2), pointer_rooms.at(4)};
    saved_rooms.at(3)->declare_paths(s3_next_rooms);

    const vector<weak_ptr<Rooms>> s4_next_rooms = {pointer_rooms.at(3), pointer_rooms.at(5),
        pointer_rooms.at(15)};
    saved_rooms.at(4)->declare_paths(s4_next_rooms);

    const vector<weak_ptr<Rooms>> s5_next_rooms = {pointer_rooms.at(2), pointer_rooms.at(4)};
    saved_rooms.at(5)->declare_paths(s5_next_rooms);

    const vector<weak_ptr<Rooms>> s6_next_rooms = {pointer_rooms.at(1), pointer_rooms.at(7),
        pointer_rooms.at(8)};
    saved_rooms.at(6)->declare_paths(s6_next_rooms);

    const vector<weak_ptr<Rooms>> s7_next_rooms = {pointer_rooms.at(2), pointer_rooms.at(9),
        pointer_rooms.at(10)};
    saved_rooms.at(7)->declare_paths(s7_next_rooms);

    const vector<weak_ptr<Rooms>> s8_next_rooms = {pointer_rooms.at(6), pointer_rooms.at(11),
        pointer_rooms.at(12)};
    saved_rooms.at(8)->declare_paths(s8_next_rooms);

    const vector<weak_ptr<Rooms>> s9_next_rooms = {pointer_rooms.at(7), pointer_rooms.at(14)};
    saved_rooms.at(9)->declare_paths(s9_next_rooms);

    const vector<weak_ptr<Rooms>> s10_next_rooms = {pointer_rooms.at(7), pointer_rooms.at(14),
        pointer_rooms.at(5), pointer_rooms.at(6)};
    saved_rooms.at(10)->declare_paths(s10_next_rooms);

    const vector<weak_ptr<Rooms>> s11_next_rooms = {pointer_rooms.at(8), pointer_rooms.at(12),
        pointer_rooms.at(13)};
    saved_rooms.at(11)->declare_paths(s11_next_rooms);

    const vector<weak_ptr<Rooms>> s12_next_rooms = {pointer_rooms.at(8), pointer_rooms.at(11),
        pointer_rooms.at(13)};
    saved_rooms.at(12)->declare_paths(s12_next_rooms);

    const vector<weak_ptr<Rooms>> s13_next_rooms = {pointer_rooms.at(11), pointer_rooms.at(12),
        pointer_rooms.at(15)};
    saved_rooms.at(13)->declare_paths(s13_next_rooms);

    const vector<weak_ptr<Rooms>> s14_next_rooms = {pointer_rooms.at(9), pointer_rooms.at(10),
        pointer_rooms.at(15)};
    saved_rooms.at(14)->declare_paths(s14_next_rooms);

    const vector<weak_ptr<Rooms>> sd_next_rooms = {pointer_rooms.at(13), pointer_rooms.at(14),
        pointer_rooms.at(4)};
    saved_rooms.at(15)->declare_paths(sd_next_rooms);
}

void Anthills::reset_rooms() {
    for (shared_ptr<Rooms> &room : saved_rooms) {
        room.reset();
    }
}

void Anthills::reset_ants() {
    for (shared_ptr<Ants> &ant : saved_ants) {
        ant.reset();
    }
}

