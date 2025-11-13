//
// Created by moskw on 12.11.2025.
//

#ifndef KASYNO_ROULETTEGAME_H
#define KASYNO_ROULETTEGAME_H
#include "Game.h"

class RouletteGame: public Game {

public:
    RouletteGame(Rng* rng): Game("Roulette", rng) {};
    ~RouletteGame();
    GameState playRound(Player& player) override;
};


#endif //KASYNO_ROULETTEGAME_H