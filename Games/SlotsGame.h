//
// Created by moskw on 12.11.2025.
//

#ifndef KASYNO_SLOTSGAME_H
#define KASYNO_SLOTSGAME_H
#include "Game.h"

class SlotsGame: public Game {
private:
    int spinSlots();
    void displayResult(int slot1, int slot2, int slot3);
public:
    SlotsGame(Rng* rng): Game("Slots", rng) {};
    GameState playRound(const Player& player) override;
};


#endif //KASYNO_SLOTSGAME_H