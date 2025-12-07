//
// Created by moskw on 12.11.2025.
//

#ifndef KASYNO_BLACKJACKGAME_H
#define KASYNO_BLACKJACKGAME_H
#include "Game.h"

class BlackjackGame: public Game {
    int askForBet(int maxBalance) override;
    int renderInterface(const Player& player) override;
    int calculateScore(int bet);
    void displayPayouts() const override;
    void animateRound(const Player& player);

public:
    BlackjackGame(Rng &rng);
    ~BlackjackGame();
    GameState playRound(Player& player) override;
};


#endif //KASYNO_BLACKJACKGAME_H