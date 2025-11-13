//
// Created by moskw on 12.11.2025.
//

#ifndef KASYNO_SLOTSGAME_H
#define KASYNO_SLOTSGAME_H
#include "Game.h"
#include <array>

class SlotsGame: public Game {
private:
    int askForBet(int maxBalance) override;
    std::array<int, 3> slots = {-1, -1, -1};
    std::array<int, 3> spinSlots();
    int renderInterface(const Player& player) override;
    int calculateScore(const std::array<int, 3>& slots, const int bet);
    const int tripletPayouts[6] = {3, 5, 10, 20, 50, 100}; // Cherry...Seven
    const int pairPayouts[6] = {1, 1, 2, 2, 3, 5};
public:
    SlotsGame(Rng* rng): Game("Slots", rng) {};
    ~SlotsGame();
    GameState playRound(Player& player) override;
};


#endif //KASYNO_SLOTSGAME_H