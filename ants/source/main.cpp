//
// Created by josur on 20/05/2025.
//

#include "main.hpp"

#include <algorithm>
#include <vector>

int main() {
    constexpr int number_of_rooms = 2;
    constexpr int number_of_ants = 2;

    vector<shared_ptr<Rooms>> saved_rooms(number_of_rooms + 2);
    saved_rooms.at(0) = make_shared<Rooms>("Sv");
    cout << saved_rooms.at(0)->name << endl;

    for (int x = 1 ; x <= number_of_rooms ; x++) {
        saved_rooms.at(x) = make_shared<Rooms>("S" + to_string(x));
        cout << saved_rooms.at(x)->name << "\n" << endl;
    }

    saved_rooms.at(number_of_rooms + 1) = make_shared<Rooms>("Sd");
    cout << saved_rooms.at(number_of_rooms + 1)->name << "\n" << endl;

    vector<shared_ptr<Ants>> saved_ants(number_of_ants);
    for (int x = 0 ; x <= number_of_ants ; x++) {
        saved_ants.at(x) = make_shared<Ants>();
    }

    for (shared_ptr<Rooms> &room : saved_rooms) {
        room.reset();
    }
    return 0;
}
