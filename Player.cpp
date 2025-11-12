//
// Created by moskw on 08.10.2025.
//

#include "Player.h"

Player::Player() : name("Guest"), balance(0) {}

Player::Player(const std::string& name,const int& balance)
    : name(name), balance(balance) {}

std::string Player::getName() const {
    return this->name;
}

int Player::getBalance() const {
    return this->balance;
}

int Player::getWinnings() const {
    return this->winnings;
}

int Player::getCurrentBet() const {
    return this->currentBet;
}

void Player::setName(const std::string& newName) {
    name = newName;
}

void Player::setBalance(const int& newBalance) {
    balance = newBalance;
}

void Player::updateBalance(const int& amount) {
    balance += amount;
}

void Player::setWinnings(const int& newWinnings) {
    winnings = newWinnings;
}

void Player::setCurrentBet(const int& newBet) {
    currentBet = newBet;
}
