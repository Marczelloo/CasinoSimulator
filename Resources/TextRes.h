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

    constexpr const char* GAME_SELECT_TITLE = "GAME SELECTION";

    const std::vector<std::string> GAME_SELECT_OPTIONS = {
        "SLOTS",
        "ROULETE",
        "BLACKJACK",
        "Return to Casino Menu",
        "Exit"
    };

    constexpr const char* BET_SELECT_TITLE = "SELECT YOUR BET";

    const std::vector<std::string> BET_SELECT_OPTIONS = {
        "All-in",
        "50% of balance",
        "25% of balance",
        "Custom amount"
    };

    constexpr const char* AFTER_GAME_TITLE = "WHAT WOULD YOU LIKE TO DO NEXT?";

    const std::vector<std::string> AFTER_GAME_OPTIONS = {
        "Play another round",
        "Change bet",
        "Play another game",
        "Return to Game Menu",
        "Return to Casino Menu",
        "Exit"
    };

    const std::vector<std::string> SLOT_SYMBOLS = {
        "🍒", "🍋", "🔔", "⭐", "7️⃣", "🍀"
    };
}

#endif //KASYNO_TEXTRES_H