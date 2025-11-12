//
// Created by moskw on 12.11.2025.
//

#ifndef KASYNO_BLACKJACKGAME_H
#define KASYNO_BLACKJACKGAME_H
#include "Game.h"

class BlackjackGame: public Game {
public:
    BlackjackGame(Rng* rng): Game("Blackjack", rng) {};
    GameState playRound(const Player& player) override;
};


#endif //KASYNO_BLACKJACKGAME_H