//
// Created by moskw on 7.12.2025.
//

#ifndef KASYNO_EXITHELPER_H
#define KASYNO_EXITHELPER_H

#include "RoundUI.h"
#include "Player.h"
#include "FileHandler.h"

inline bool confirmExitAndSave(RoundUI& ui, Player& player) {
    const int response = ui.askChoice(
        "Are you sure you want to exit the casino?",
        {"Yes", "No"}
    );

    if (response != 0) {
        ui.print("Exit cancelled.");
        return false;
    }

    ui.print("Exiting...");

    LeaderboardEntry entry{player.getName(), player.getBalance()};
    FileHandler::addEntry(entry);

    return true;
}

#endif //KASYNO_EXITHELPER_H