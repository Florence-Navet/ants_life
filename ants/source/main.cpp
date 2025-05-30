//
// Created by josur on 20/05/2025.
//

#include "main.h"

vector<vector<weak_ptr<Rooms>>> Ants::found_paths;

int main()
{
    // anthill 0-5, 6 : 3d, 7 : everything, 8 : waiting, 9 : corridors

    constexpr long chosen_anthill = 5;

    const anthill_basic_information anthill_info = read_anthill_json_file(chosen_anthill);

    Anthills anthill(anthill_info);

    anthill.start_finding_dorms();

    return 0;
}