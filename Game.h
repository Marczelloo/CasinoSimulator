//
// Created by moskw on 08.10.2025.
//

#ifndef KASYNO_GAME_H
#define KASYNO_GAME_H
#include <string>

#include "Player.h"
#include "Rng.h"


class Game {
    std::string name;
    Rng* random;
public:
    virtual void playRound(const Player& player, int bet) = 0;
};


#endif //KASYNO_GAME_H