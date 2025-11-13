//
// Created by moskw on 12.11.2025.
//

#include "SlotsGame.h"

SlotsGame::~SlotsGame() = default;

int SlotsGame::askForBet(int maxBalance) {
    ui.clear();
    ui.print("Your current balance is: " + std::to_string(maxBalance));

    if (maxBalance < 10) {
        ui.print("Insufficient balance! Minimum bet is 10$.");
        ui.print("Returning to Game Menu...");
        ui.waitForEnter();
        return -1;
    }

    int choice = ui.askChoice(TextRes::SLOTS_BET_OPTIONS_TITLE, TextRes::SLOTS_BET_OPTIONS);

    int newBet = 0;

    switch (static_cast<SlotsBetOptions>(choice)) {
        case SlotsBetOptions::BET_10:
            newBet = 10;
            break;
        case SlotsBetOptions::BET_20:
            newBet = 20;
            break;
        case SlotsBetOptions::BET_50:
            newBet = 50;
            break;
        case SlotsBetOptions::BET_100:
            newBet = 100;
            break;
        case SlotsBetOptions::BET_200:
            newBet = 200;
            break;
        case SlotsBetOptions::BET_500:
            newBet = 500;
            break;
        default:
            ui.print("Invalid choice! Please select a valid bet amount.");
            return askForBet(maxBalance);
    }

    if (newBet > maxBalance) {
        ui.print("Insufficient balance for this bet (" + std::to_string(newBet) + "$)!");
        ui.print("Please choose a lower amount.");
        ui.waitForEnter();
        return askForBet(maxBalance);
    }

    if (newBet > maxBalance) {
        ui.print("Invalid choice, defaulting to custom amount!");
        newBet = 10;
    }

    return newBet;
}

int SlotsGame::renderInterface(const Player& player) {
    ui.clear();
    ui.print("=== SLOTS GAME ===");
    if (slots[0] == -1) {
        ui.renderSlots( { "?", "?", "?" } );
    } else {
        ui.renderSlots( {TextRes::SLOT_SYMBOLS[slots[0]], TextRes::SLOT_SYMBOLS[slots[1]], TextRes::SLOT_SYMBOLS[slots[2]]} );
    }
    ui.print("===================");
    ui.print(player.getName() + "'s Balance: " + std::to_string(player.getBalance()));
    ui.print("Current bet: " + std::to_string(player.getCurrentBet()));
    ui.print("===================");

    int option = ui.askChoice("What would you like to do?", TextRes::SLOTS_GAME_OPTIONS);

    return option;
}

std::array<int, 3> SlotsGame::spinSlots() {
    auto getSymbol = [this]() {
        int chance = random->randInt(1, 100);
        return (chance <= 40) ? 0 : (chance <= 70) ? 1 : (chance <= 85) ? 2 :
               (chance <= 95) ? 3 : (chance <= 99) ? 4 : 5;
    };

    return {getSymbol(), getSymbol(), getSymbol()};
}

int SlotsGame::calculateScore(const std::array<int, 3>& slots,const int bet) {
    if (slots[0] == slots[1] && slots[1] == slots[2]) {
        return bet * tripletPayouts[slots[0]];
    }

    if (slots[0] == slots[1] || slots[1] == slots[2] || slots[0] == slots[2]) {
        int pairSymbol = (slots[0] == slots[1]) ? slots[0] :
                         (slots[1] == slots[2]) ? slots[1] : slots[0];
        return bet * pairPayouts[pairSymbol];
    }

    return 0;
}

GameState SlotsGame::playRound(Player &player) {
    slots = {-1, -1, -1};
    int bet = askForBet(player.getBalance());

    if (bet <= 0) {
        ui.print("Cannot continue playing. Returning to Game Menu.");
        ui.waitForEnter();
        return GameState::GAME_MENU;
    }

    player.setCurrentBet(bet);

    GameState newState = GameState::GAME_MENU;
    exit = false;

    while (!exit) {
        int option = renderInterface(player);

        switch (static_cast<SlotsOptions>(option)) {
            case SlotsOptions::SPIN: {
                if (player.getBalance() < bet) {
                    ui.print("Insufficient balance! Change bet or exit.");
                    break;
                }

                player.setCurrentBet(bet);
                player.updateBalance(-bet);
                slots = spinSlots();

                int score = calculateScore(slots, bet);

                renderInterface(player);

                ui.print("==================");
                if (score > 0) {
                    player.updateBalance(score);

                    int netProfit = score - bet;
                    player.setWinnings(player.getWinnings() + netProfit);

                    if (slots[0] == slots[1] && slots[1] == slots[2]) {
                        ui.print("🎉 JACKPOT! You won " + std::to_string(score) + "!");
                    } else {
                        ui.print("😊 You won " + std::to_string(score) + "!");
                    }
                } else {
                    ui.print("😞 No win this time. Better luck next spin!");
                }
                ui.print("==================");

                ui.print("Press Enter to continue...");
                ui.waitForEnter();
                break;
            }
            case SlotsOptions::CHANGE_BET: {
                int newBet = askForBet(player.getBalance());
                if (newBet <= 0) {
                    ui.print("Invalid bet amount. Keeping previous bet.");
                } else {
                    bet = newBet;
                    player.setCurrentBet(bet);
                }
                break;
            }
            case SlotsOptions::EXIT_TO_GAME_MENU:
                exit = true;
                newState = GameState::GAME_MENU;
                break;
            case SlotsOptions::EXIT:
                exit = true;
                newState = GameState::EXIT;
                break;
            default:
                ui.print("Invalid choice, please try again.");
                break;
        }
    }

    return newState;
}