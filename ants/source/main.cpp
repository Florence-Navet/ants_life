//
// Created by josur on 20/05/2025.
//

#include "main.hpp"

int main() {
    constexpr int number_of_rooms = 2;
    constexpr int number_of_ants = 2;

    vector<shared_ptr<Rooms>> saved_rooms(number_of_rooms + 2);
    vector<weak_ptr<Rooms>> pointer_rooms(number_of_rooms + 2);

    saved_rooms.at(0) = make_shared<Rooms>("Sv");
    cout << saved_rooms.at(0)->name << endl;

    for (int x = 1 ; x <= number_of_rooms ; x++) {
        saved_rooms.at(x) = make_shared<Rooms>("S" + to_string(x));
        cout << saved_rooms.at(x)->name << "\n" << endl;
    }

    saved_rooms.at(number_of_rooms + 1) = make_shared<Rooms>("Sd");
    cout << saved_rooms.at(number_of_rooms + 1)->name << "\n" << endl;

    for (auto iteration = saved_rooms.begin(); iteration != saved_rooms.end(); ++iteration) {
        const long long index = distance(saved_rooms.begin(), iteration);
        const weak_ptr<Rooms> room_ptr = saved_rooms.at(index);
        pointer_rooms.at(index) = room_ptr;
    }

    const vector<weak_ptr<Rooms>> sv_next_rooms = {pointer_rooms.at(1)};
    saved_rooms.at(0)->declare_paths(sv_next_rooms);
    cout << saved_rooms.at(0)->next_rooms.at(0).lock()->name << "\n" << endl;

    const vector<weak_ptr<Rooms>> s1_next_rooms = {pointer_rooms.at(0), pointer_rooms.at(2)};
    saved_rooms.at(1)->declare_paths(sv_next_rooms);

    const vector<weak_ptr<Rooms>> s2_next_rooms = {pointer_rooms.at(1), pointer_rooms.at(3)};
    saved_rooms.at(2)->declare_paths(sv_next_rooms);

    const vector<weak_ptr<Rooms>> sd_next_rooms = {pointer_rooms.at(2)};
    saved_rooms.at(3)->declare_paths(sv_next_rooms);

    vector<shared_ptr<Ants>> saved_ants(number_of_ants);
    for (int x = 0 ; x < number_of_ants ; x++) {
        saved_ants.at(x) = make_shared<Ants>(x, pointer_rooms.at(0));
    }

    for (shared_ptr<Rooms> &room : saved_rooms) {
        room.reset();
    }
    return 0;
}
