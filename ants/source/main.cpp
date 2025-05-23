//
// Created by josur on 20/05/2025.
//

#include "main.hpp"

vector<vector<weak_ptr<Rooms>>> Ants::found_paths(3);

int main() {
    Anthills anthill;

    constexpr long chosen_anthill = 5;

    switch (chosen_anthill) {
        case 0:
            anthill.define_basic_information(
                0, 2,2
                );
            break;
        case 1:
            anthill.define_basic_information(
                1, 2,2
                );
            break;
        case 2:
            anthill.define_basic_information(
                2, 2,5
                );
            break;
        case 3:
            anthill.define_basic_information(
                3, 4, 5
                );
            break;
        case 4:
            anthill.define_basic_information(
                4, 6, 10,
                {1, 4},
                {2, 2}
                );
            break;
        case 5:
            anthill.define_basic_information(
                5, 14, 50,
                {1, 2, 3, 4, 5, 6, 7, 8, 13, 14},
                {8, 4, 2, 4, 2, 4, 2, 5, 4, 2}
                );
            break;
        default:
            return 1;
    }

    anthill.generate_rooms();

    anthill.generate_paths();

    anthill.generate_ants();

    bool ants_home = false;
    long int rounds = 0;

    while (!ants_home) {
        rounds++;

        cout << "Etape " << rounds << endl;

        for (const shared_ptr<Ants>& ant : anthill.saved_ants) {
            ant->act();
            cout << ant->ant_status << endl;
        }
        if (anthill.saved_rooms.at(anthill.number_of_rooms + 1)->occupying_ants == anthill.number_of_ants) {
            ants_home = true;
            cout << "Toutes les fourmies sont rentrees au dortoir !!\n Fourmilliere finie en " <<
                rounds << " etapes !" << endl;
        }
    }

    anthill.reset_rooms();
    anthill.reset_ants();

    return 0;
}