//
// Created by moskw on 09.10.2025.
//

#ifndef KASYNO_CASINO_H
#define KASYNO_CASINO_H
#include "Enums.h"
#include "Game.h"
#include "Player.h"
#include "Rng.h"
#include "RoundUI.h"


class Casino {
    Player* player;
    Game* game;
    RoundUI ui;
    Rng* random;
    int bet;
    GameState state;
public:
    Casino();
    ~Casino();
    void run();

    GameState handleMainMenu();
    GameState handleCasinoMenu();
    GameState handleGameMenu();

    CreatePlayerResult createPlayer();
    void checkLeaderboard();
    void exitCasino();
};


#endif //KASYNO_CASINO_H