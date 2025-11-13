//
// Created by moskw on 12.11.2025.
//

#include "BlackjackGame.h"

BlackjackGame::~BlackjackGame() = default;

GameState BlackjackGame::playRound(Player &player) {
    (void)player; // tymczasowa implementacja - nic nie robi

    ui.print("Blackjack game is under construction.");
    ui.waitForEnter();

    return GameState::GAME_MENU;
}