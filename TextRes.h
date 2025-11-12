//
// Created by moskw on 09.10.2025.
//

#ifndef KASYNO_TEXTRES_H
#define KASYNO_TEXTRES_H
#include <string>
#include <vector>

namespace TextRes {
    constexpr const char* MAIN_MENU_TITLE = "CASINO MAIN MENU";
    constexpr const char* LEADERBOARD_TITLE = "LEADERBOARD (TOP 100 PLAYERS)";

    const std::vector<std::string> MAIN_MENU_OPTIONS = {
        "Create player",
        "Check leaderboard",
        "Exit",
    };

    constexpr const char* CASINO_TITLE = "CASINO";
    constexpr const char* CASINO_PLAYER = "Current player: ";
    constexpr const char* CASINO_BALANCE = "Current balance: ";

    const std::vector<std::string> CASINO_OPTIONS = {
        "Select game",
        "Check leaderboard",
        "Return to Main Menu",
        "Exit"
    };

    constexpr const char* GAME_SELECT_TITLE = "SELECT A GAME";

    const std::vector <std::string> GAMES_OPTIONS = {
        "BLACKJACK",
        "SLOTS",
        "ROULETE",
    };
}

#endif //KASYNO_TEXTRES_H