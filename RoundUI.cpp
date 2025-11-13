//
// Created by moskw on 08.10.2025.
//

#include "RoundUI.h"

#include <iostream>
#include <ostream>
#include <algorithm>
#include <limits>
#include <bits/this_thread_sleep.h>

RoundUI::RoundUI() {}

RoundUI::~RoundUI() {}

std::string RoundUI::trim(std::string str) {
    auto first = str.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return "";
    auto last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, last - first + 1);
}

void RoundUI::print(const std::string &text) {
    std::cout << text << std::endl;
}

int RoundUI::askChoice(const std::string &prompt, const std::vector<std::string> &options) {
    if (prompt.empty()) {
        std::cout << "Your prompt for choice windows is empty " << std::endl;
        return -1;
    }

    if (options.empty()) {
        std::cout << "Your choices are empty" << std::endl;
        return -1;
    }

    std::string answer;
    int choice;

    std::cout << prompt << std::endl;
    for (int i = 0; i < static_cast<int>(options.size()); i++) {
        std::cout << i + 1 << ". " << options[i] << std::endl;
    }

    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, answer)) {
            std::cout << "\nInput closed\n";
            return -1;
        }

        if (answer.empty()) {
            std::cout << "Choose from 1-" << options.size() << std::endl;
            continue;
        }

        answer = trim(answer);

        try {
            choice  = std::stoi(answer);
        } catch (const std::invalid_argument& e) {
            std::cout << "Invalid option" << std::endl;
            continue;
        } catch (const std::out_of_range& e) {
            std::cout << "Out of range" << std::endl;
            continue;
        }

        if (choice < 1 || choice > static_cast<int>(options.size())) {
            std::cout << "Invalid choice" << std::endl;
        } else {
            return choice - 1;
        }
    }
}

std::string RoundUI::ask(const std::string &prompt) {
    if (prompt.empty()) {
        std::cerr << "Error: Your prompt for ask is empty" << std::endl;
        return "";
    }

    std::string trimmed_prompt = trim(prompt);
    if (trimmed_prompt.empty()) {
        std::cerr << "Error: Prompt containts only white spaces" << std::endl;
        return "";
    }

    std::string answer;

    while (true) {
        std::cout << prompt << std::endl;
        std::cout << "> ";

        if (!getline(std::cin, answer)) {
            std::cout << "\nInput closed\n";
            return "";
        }

        answer = trim(answer);
        if (answer.empty()) {
            std::cout << "Answer cannot be empty" << std::endl;
            continue;
        }

        return answer;
    }
}


void RoundUI::renderSlots(const std::vector<std::string>& symbols) {
    std::cout << "====================" << std::endl;
    std:: cout << "|";
    for (int i = 0; i < static_cast<int>(symbols.size()); i++) {
        std::cout << " " << symbols[i] << " " << "|";
    }
    std::cout << "====================" << std::endl;
}

void RoundUI::pause(const int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void RoundUI::clear() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void RoundUI::leaderboard(const std::string& title, const std::vector<LeaderboardEntry>& entries) {
    clear();

    print(title);
    print("===============================");
    print("RANK | NAME               | BALANCE");
    print("-------------------------------");

    int rank = 1;
    for (const auto& entry : entries) {
        printf("%-4d | %-18s | %d\n", rank, entry.name.c_str(), entry.balance);
        rank++;
        if (rank > 100) break; // Show only top 100
    }

    print("===============================");
}

void RoundUI::waitForKey(const std::string& message) {
    print(message);
    std::cin.get();
}

void RoundUI::waitForEnter(const std::string& message) {
    print(message);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string RoundUI::askInput(const std::string &prompt, const std::vector<std::string> &validInputs) {
    print(prompt);
    std::string answer;

    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, answer)) {
            std::cout << "\nInput closed\n";
            return "";
        }

        answer = trim(answer);
        if (std::find(validInputs.begin(), validInputs.end(), answer) != validInputs.end()) {
            return answer;
        } else {
            std::cout << "Invalid input. Valid options are: ";
            for (const auto& input : validInputs) {
                std::cout << input << " ";
            }
            std::cout << std::endl;
        }
    }
}

int RoundUI::askInput(const std::string &prompt, int min, int max) {
    print(prompt);
    std::string answer;

    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, answer)) {
            std::cout << "\nInput closed\n";
            return -1;
        }

        answer = trim(answer);
        try {
            int value = std::stoi(answer);
            if (value >= min && value <= max) {
                return value;
            } else {
                std::cout << "Input must be between " << min << " and " << max << std::endl;
            }
        } catch (const std::invalid_argument& e) {
            std::cout << "Invalid input. Please enter a number." << std::endl;
        } catch (const std::out_of_range& e) {
            std::cout << "Input out of range. Please enter a valid number." << std::endl;
        }
    }
}









