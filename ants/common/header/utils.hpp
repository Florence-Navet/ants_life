//
// Created by josur on 20/05/2025.
//

#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <string>
#include <utility>
#include <memory>
#include <algorithm>
#include <vector>

using namespace std;

#if defined(ANTS_HPP) & !defined(ANTS_INCLUDED)
    #define ANTS_INCLUDED
    #include "Rooms.hpp"
#endif //ANTS_INCLUDED

#if defined(MAIN_HPP) & !defined(MAIN_INCLUDED)
    #define MAIN_INCLUDED
    #include "Rooms.hpp"
    #include "Ants.hpp"
    #include "Anthills.hpp"
#endif //MAIN_INCLUDED

#if defined(ANTHILLS_HPP) & !defined(ANTHILLS_INCLUDED)
    #define ANTHILLS_INCLUDED
    #include "Ants.hpp"
    #include "Rooms.hpp"
#endif //ANTHILLS_INCLUDED

#endif //UTILS_HPP
