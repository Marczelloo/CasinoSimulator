//
// Created by moskw on 09.10.2025.
//

#include "Casino.h"

#include "Enums.h"
#include "FileHandler.h"
#include "TextRes.h"

Casino::Casino() {
    random = new Rng();
    game = nullptr;
    player = nullptr;
    state = GameState::MAIN_MENU;
    bet = 0;
}

Casino::~Casino() {
    if (player != nullptr) {
        delete player;
    }

    if (game != nullptr) {
        delete game;
    }

    if (random != nullptr) {
        delete random;
    }

    if (state != GameState::EXIT) {
        exitCasino();
    }

    if (bet != 0) {
        bet = 0;
    }
}

void Casino::run() {
    state = GameState::MAIN_MENU;

    while (state != GameState::EXIT) {
        switch (state) {
            case GameState::MAIN_MENU:
                state = handleMainMenu();
                break;
            case GameState::CASINO_MENU:
                state = handleCasinoMenu();
                break;
            case GameState::GAME_MENU:
                state = handleGameMenu();
                break;
            default:
                ui.print("Invalid State, Quiting!");
                state = GameState::EXIT;
                break;
        }
    }

    exitCasino();
}

GameState Casino::handleMainMenu() {
    int option = ui.askChoice(TextRes::MAIN_MENU_TITLE, TextRes::MAIN_MENU_OPTIONS);

    switch (static_cast<MainMenuOptions>(option)) {
        case MainMenuOptions::MENU_CREATE_PLAYER: {
            auto res = createPlayer();
            if (res == CreatePlayerResult::Ok) return GameState::CASINO_MENU;
            if (res == CreatePlayerResult::Retry) return GameState::MAIN_MENU;
            return GameState::EXIT;
        }
        case MainMenuOptions::MENU_CHECK_LEADERBOARD:
            checkLeaderboard();
            return GameState::MAIN_MENU;
        case MainMenuOptions::MENU_EXIT:
            exitCasino();
            return GameState::MAIN_MENU;
        default:
            ui.print("Invalid choice");
            return GameState::MAIN_MENU;
    }
}

CreatePlayerResult Casino::createPlayer() {
    const std::string name = ui.ask("Enter your name: ");

    const int minBalance = 500;
    const int maxBalance = 2000;

    const int balance = random->randInt(minBalance, maxBalance);

    if (player != nullptr) {
        delete player;
    }

    player = new Player(name, balance);

    if (player->getName().empty() || player->getBalance() < 0) {
        ui.print("Error: Invalid player data");
        delete player;
        player = nullptr;
        return CreatePlayerResult::Retry;
    }

    ui.print("Player created successfully!");
    ui.print("Name: " + player->getName());
    ui.print("Balance: " + std::to_string(player->getBalance()));

    return CreatePlayerResult::Ok;
}

void Casino::checkLeaderboard() {
    auto entries = FileHandler::loadLeaderboard("leaderboard.txt");

    if (entries.empty()) ui.print("Leaderboard is empty.");
    else ui.leaderboard(TextRes::LEADERBOARD_TITLE, entries);

    ui.waitForEnter("Press ENTER to return");

    return;
}

void Casino::exitCasino() {
    if (player != nullptr) {
        LeaderboardEntry entry{player->getName(), player->getBalance()};
        FileHandler::addEntry(entry);
    }
}

GameState Casino::handleCasinoMenu() {
    int option = ui.askChoice(TextRes::CASINO_TITLE, TextRes::CASINO_OPTIONS);

    switch (static_cast<CasinoOptions>(option)) {
        case CasinoOptions::CASINO_SELECT_GAME:
            return GameState::GAME_MENU;
        case CasinoOptions::CASINO_CHECK_LEADERBOARD:
            checkLeaderboard();
            return GameState::CASINO_MENU;
        case CasinoOptions::CASINO_RETURN_TO_MAIN_MENU:
            return GameState::MAIN_MENU;
        case CasinoOptions::CASINO_EXIT:
            exitCasino();
            return GameState::EXIT;
        default:
            ui.print("Invalid choice");
            return GameState::CASINO_MENU;
    }

}

GameState Casino::handleGameMenu() {


    ui.print("Game menu handler");

    return GameState::CASINO_MENU;
}

