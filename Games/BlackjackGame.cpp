//
// Created by moskw on 12.11.2025.
//

#include "BlackjackGame.h"

BlackjackGame::BlackjackGame(Rng &rng): Game("Blackjack", rng) {};

BlackjackGame::~BlackjackGame() = default;

void BlackjackGame::animateRound(const Player &player) {
    ui.print("Placeholder for animate round");
}

int BlackjackGame::askForBet(int maxBalance) {
    ui.print("Placeholder for ask for bet");
    return 0;
}

int BlackjackGame::calculateScore(int bet) {
    ui.print("Placeholder for calculate score");
    return 0;
}

void BlackjackGame::displayPayouts() const {
    ui.print("Placeholder for display payouts");
}

int BlackjackGame::renderInterface(const Player &player) {
    ui.print("Placeholder for render interface");
    return 0;
}


GameState BlackjackGame::playRound(Player &player) {
    (void)player; // tymczasowa implementacja - nic nie robi

    ui.print("Blackjack game is under construction.");
    ui.waitForEnter();

    return GameState::GAME_MENU;
}