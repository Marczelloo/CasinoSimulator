//
// Created by moskw on 12.11.2025.
//

#include "RouletteGame.h"
#include <array>
#include <algorithm>
#include <thread>
#include <chrono>

#include "../ExitHelper.h"

constexpr std::array<int, 8> ROULETTE_PAYOUT_MULTIPLIERS = {
    2,  // RED
    2,  // BLACK
    35, // GREEN
    35, // NUMBER
    2,  // ODD
    2,  // EVEN
    2,  // LOW
    2   // HIGH
};

RouletteGame::RouletteGame(Rng &rng): Game("Roulette", rng),
    lastScore(-1),
    betType(RouletteBetType::BET_RED),
    betNumber(-1),
    wheel(initWheel()),
    prevTiles(),
    spunTile(-1) {};

RouletteGame::~RouletteGame() = default;

RouletteTileType RouletteGame::getColorForNumber(int number) const {
    if (number == 0) return RouletteTileType::GREEN;

    static const std::array<int, 18> redNumbers = {
        1, 3, 5, 7, 9, 12, 14, 16, 18,
        19, 21, 23, 25, 27, 30, 32, 34, 36
    };

    if (std::find(redNumbers.begin(), redNumbers.end(), number) != redNumbers.end()) {
        return RouletteTileType::RED;
    } else {
        return RouletteTileType::BLACK;
    }
}

std::vector<RouletteTile> RouletteGame::initWheel() {
    static const std::vector<int> numbers = {
        0, 32, 15, 19, 4, 21, 2, 25,
        17, 34, 6, 27, 13, 36, 11, 30,
        8, 23, 10, 5, 24, 16, 33, 1,
        20, 14, 31, 9, 22, 18, 29, 7,
        28, 12, 35, 3, 26
    };

    std::vector<RouletteTile> wheel;
    wheel.reserve(numbers.size());

    for (int n : numbers) {
        wheel.emplace_back(RouletteTile{
            getColorForNumber(n),
            n
        });
    }

    return wheel;
}

int RouletteGame::spinWheel() {
    int n = static_cast<int>(wheel.size());
    return random.randInt(0, n - 1);
}

void RouletteGame::animateSpin(const Player& player, int resultIndex) {
    int n = static_cast<int>(wheel.size());
    if (n == 0) return;

    int startIndex = (spunTile >= 0 && spunTile < n)
                        ? spunTile
                        : random.randInt(0, n - 1);

    int extraRounds = random.randInt(2, 4);

    int delta = (resultIndex - startIndex + n) % n;
    int totalSteps = extraRounds * n + delta;

    float minDelayMs = 15.0f;
    float MaxDelaysMs = 180.0f;

    for (int step = 0; step <= totalSteps; ++step) {
        int currentIndex = (startIndex + step) % n;

        RoundUI::clear();

        ui.renderWheel(wheel, currentIndex);
        std::vector<std::string> info;
        info.emplace_back(player.getName() + "'s Balance: " + std::to_string(player.getBalance()));
        info.emplace_back("Current bet: " + std::to_string(player.getCurrentBet()) + " - " +
                       TextRes::ROULETTE_BET_TYPES[static_cast<int>(betType)]);
        info.emplace_back("");
        info.emplace_back("Spinning the wheel...");
        ui.drawBox("", info);

        float t = (totalSteps > 0)
                        ? static_cast<float>(step) / static_cast<float>(totalSteps)
                        : 1.0f;

        float delay = minDelayMs + (MaxDelaysMs - minDelayMs) * (t * t);

        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(delay)));
    }

    spunTile = resultIndex;
}

int RouletteGame::askForBet(const int maxBalance) {
    RoundUI::clear();
    ui.print("Your current balance is: " + std::to_string(maxBalance));

    if (maxBalance < 1) {
        ui.print("Insufficient balance! Minimum bet is 1$.");
        ui.print("Returning to Game Menu...");
        ui.waitForEnter();
        return -1;
    }

    int choice = ui.askChoice(TextRes::ROULETTE_BET_OPTIONS_TITLE, TextRes::ROULETTE_BET_TYPES);

    RouletteBetType newBetType;

    switch (static_cast<RouletteBetType>(choice)) {
        case RouletteBetType::BET_RED:
            newBetType = RouletteBetType::BET_RED;
            break;
        case RouletteBetType::BET_BLACK:
            newBetType = RouletteBetType::BET_BLACK;
            break;
        case RouletteBetType::BET_GREEN:
            newBetType = RouletteBetType::BET_GREEN;
            break;
        case RouletteBetType::BET_NUMBER: {
                newBetType = RouletteBetType::BET_NUMBER;
                std::string prompt = "Enter the number you want to bet on (0-36): ";
                int input = ui.askInput(prompt, 0, 36);
                if (input < 0 || input > 36) {
                    ui.print("Invalid number!");
                    return askForBet(maxBalance);
                } else {
                    betNumber = input;
                }
            }
            break;
        case RouletteBetType::BET_ODD:
            newBetType = RouletteBetType::BET_ODD;
            break;
        case RouletteBetType::BET_EVEN:
            newBetType = RouletteBetType::BET_EVEN;
            break;
        case RouletteBetType::BET_LOW:
            newBetType = RouletteBetType::BET_LOW;
            break;
        case RouletteBetType::BET_HIGH:
            newBetType = RouletteBetType::BET_HIGH;
            break;
        default:
            ui.print("Invalid choice! Please select a valid bet type.");
            return askForBet(maxBalance);
    }

    choice = ui.askChoice(TextRes::BET_SELECT_TITLE, TextRes::BET_SELECT_OPTIONS);

    int newBetAmount = 0;

    switch  (static_cast<BetOptions>(choice)) {
        case BetOptions::BET_ALL_IN:
            newBetAmount = maxBalance;
            break;
        case BetOptions::BET_HALF:
            newBetAmount = maxBalance / 2;
            break;
        case BetOptions::BET_QUARTER:
            newBetAmount = maxBalance / 4;
            break;
        case BetOptions::BET_CUSTOM: {
            ui.print("Custom bet amount selected.");
            std::string prompt = "Enter your bet amount (1 - " + std::to_string(maxBalance) + "): ";
            int input = ui.askInput(prompt, 1, maxBalance);
            if (input < 1 || input > maxBalance) {
                ui.print("Invalid bet amount!");
                return askForBet(maxBalance);
            } else {
                newBetAmount = input;
            }
            break;
        }
        default:
            ui.print("Invalid choice! Please select a valid bet type.");
            return askForBet(maxBalance);
    }

    betType = newBetType;

    return newBetAmount;
}

int RouletteGame::calculateScore(int selectedTile, int bet) {
    const RouletteTile& tile = wheel[selectedTile];

    bool win = false;

    switch (betType) {
        case RouletteBetType::BET_RED:
            win = (tile.color == RouletteTileType::RED);
            if (!win) ui.print("No win for BET_RED");
            break;
        case RouletteBetType::BET_BLACK:
            win = (tile.color == RouletteTileType::BLACK);
            if (!win) ui.print("No win for BET_BLACK");
            break;
        case RouletteBetType::BET_GREEN:
            win = (tile.color == RouletteTileType::GREEN);
            if (!win) ui.print("No win for BET_GREEN");
            break;
        case RouletteBetType::BET_NUMBER:
            win = (tile.number == betNumber);
            if (!win) ui.print("No win for BET_NUMBER");
            break;
        case RouletteBetType::BET_ODD:
            win = (tile.number != 0 && tile.number % 2 == 1);
            if (!win) ui.print("No win for BET_ODD");
            break;
        case RouletteBetType::BET_EVEN:
            win = (tile.number != 0 && tile.number % 2 == 0);
            if (!win) ui.print("No win for BET_EVEN");
            break;
        case RouletteBetType::BET_LOW:
            win = (tile.number >= 1 && tile.number <= 18);
            if (!win) ui.print("No win for BET_LOW");
            break;
        case RouletteBetType::BET_HIGH:
            win = (tile.number >= 19 && tile.number <= 36);
            if (!win) ui.print("No win for BET_HIGH");
            break;
        default:
            ui.print("Invalid bet type for score calculation!");
            return 0;
    }

    if (!win) {
        return 0;
    }

    int multiplier = ROULETTE_PAYOUT_MULTIPLIERS[static_cast<int>(betType)];
    return bet * multiplier;
}

void RouletteGame::displayPayouts() const {
    RoundUI::clear();

    std::vector<std::string> payoutInfo;
    payoutInfo.reserve(TextRes::ROULETTE_BET_TYPES.size() + 2);

    for (std::size_t i = 0; i < TextRes::ROULETTE_BET_TYPES.size(); ++i) {
        const std::string& type = TextRes::ROULETTE_BET_TYPES[i];
        int multiplier = ROULETTE_PAYOUT_MULTIPLIERS[i];

        std::string line = type + " ->  x" + std::to_string(multiplier);
        payoutInfo.emplace_back(std::move(line));
    }

    ui.drawBox("=== PAYOUTS TABLE ===", payoutInfo);
    ui.waitForEnter("Press ENTER to return");
}

int RouletteGame::renderInterface(const Player &player) {
    RoundUI::clear();

    ui.renderWheel(wheel, spunTile);

    std::vector<std::string> info;
    info.emplace_back(player.getName() + "'s Balance: " + std::to_string(player.getBalance()));
    info.emplace_back("Current bet: " + std::to_string(player.getCurrentBet()) + " - " +
                   TextRes::ROULETTE_BET_TYPES[static_cast<int>(betType)] +
                   (betType == RouletteBetType::BET_NUMBER ?
                       (" [" + std::to_string(betNumber) + "]") : ""));

    if (lastScore >= 0) {
        if (lastScore > 0) {
            info.emplace_back("You won " + std::to_string(lastScore) + "!");
        } else {
            info.emplace_back("No win this time. Better luck next spin!");
        }
    }

    if (!errorMessage.empty()) {
        info.emplace_back("");
        info.emplace_back("Error: " + errorMessage);
        errorMessage.clear();
    }

    ui.drawBox("", info);

    int option = ui.askChoice("What would you like to do?",
                              TextRes::ROULETTE_GAME_OPTIONS,
                              false);

    return option;
}

GameState RouletteGame::playRound(Player &player) {

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

        switch (static_cast<RouletteOptions>(option)) {
            case RouletteOptions::SPIN: {
                if (player.getBalance() < bet) {
                    errorMessage = "Insufficient balance to place the bet.";
                    break;
                }

                player.setCurrentBet(bet);
                player.updateBalance(-bet);

                int resultIndex = spinWheel();
                animateSpin(player, resultIndex);
                spunTile = resultIndex;

                lastScore = calculateScore(spunTile, bet);

                if (lastScore > 0) {
                    player.updateBalance(lastScore);
                    int netProfit = lastScore - bet;
                    player.setWinnings(player.getWinnings() + netProfit);
                }

                break;
            }
            case RouletteOptions::CHANGE_BET: {
                int newBet = askForBet(player.getBalance());

                if (newBet <= 0) {
                    errorMessage = "Invalid bet amount. Keeping previous bet.";
                } else {
                    bet = newBet;
                    player.setCurrentBet(bet);
                }
                break;
            }
            case RouletteOptions::VIEW_PAYOUTS: {
                displayPayouts();
                break;
            }
            case RouletteOptions::EXIT_TO_GAME_MENU: {
                exit = true;
                newState = GameState::GAME_MENU;
                break;
            }
            case RouletteOptions::EXIT: {
                if (confirmExitAndSave(ui, player)) {
                    exit = true;
                    newState = GameState::EXIT;
                } else {
                    errorMessage = "Exit cancelled.";
                }
                break;
            }
            default:
                errorMessage = "Invalid choice, please try again.";
                break;
        }
    }

    return newState;
}