//
// Created by moskw on 10.10.2025.
//

#pragma once

#ifndef KASYNO_ENUMS_H
#define KASYNO_ENUMS_H

enum class GameState {
    MAIN_MENU = 0,
    CASINO_MENU,
    GAME_MENU,
    EXIT,
};

enum class MainMenuOptions {
    MENU_CREATE_PLAYER = 0,
    MENU_CHECK_LEADERBOARD,
    MENU_EXIT,
};

enum class CreatePlayerResult {
    Ok = 0,
    Retry,
    Exit,
};

enum class CasinoOptions {
    CASINO_SELECT_GAME = 0,
    CASINO_CHECK_LEADERBOARD,
    CASINO_RETURN_TO_MAIN_MENU,
    CASINO_EXIT,
};

#endif //KASYNO_ENUMS_H