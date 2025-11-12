//
// Created by moskw on 09.10.2025.
//

#ifndef KASYNO_CASINO_H
#define KASYNO_CASINO_H
#include "Resources/Enums.h"
#include "Games/Game.h"
#include "Player.h"
#include "Rng.h"
#include "RoundUI.h"


class Casino {
    Player* player;
    Game* game;
    RoundUI ui;
    Rng* random;
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