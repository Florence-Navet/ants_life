//
// Created by josur on 20/05/2025.
//

#include "main.hpp"

vector<vector<weak_ptr<Rooms>>> Ants::found_paths;

int main() {

    constexpr long chosen_anthill = 1;

    const anthill_basic_information anthill_info = read_anthill_json_file(chosen_anthill);

    const Anthills anthill(anthill_info);

    bool ants_home = false;
    long int rounds = 0;

    while (!ants_home) {
        rounds++;

        cout << "Etape " << rounds << endl;

        for (const shared_ptr<Ants>& ant : anthill.saved_ants) {
            ant->act();
            if (ant->ant_action != Ants::IN_DORMS) {
                cout << ant->ant_status << endl;
            }
        }
        if (anthill.saved_rooms.at(anthill.number_of_rooms + 1)->occupying_ants == anthill.number_of_ants) {
            ants_home = true;
            cout << "Toutes les fourmies sont rentrees au dortoir !!\n Fourmilliere finie en " <<
                rounds << " etapes !" << endl;
        }
        if (rounds > 500) {
            cout << "Les fourmis ne rentreront jamais au dortoirs...." << endl;
            return 5;
        }
    }

    return 0;
}