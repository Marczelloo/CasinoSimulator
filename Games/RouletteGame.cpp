//
// Created by moskw on 12.11.2025.
//

#include "RouletteGame.h"

RouletteGame::~RouletteGame() = default;

GameState RouletteGame::playRound(Player &player) {
    (void)player; // tymczasowa implementacja - nic nie robi

    ui.print("Roulette game is under construction.");
    ui.waitForEnter();

    return GameState::GAME_MENU;
}