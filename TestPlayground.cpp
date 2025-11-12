#include "Casino.h"
#include "FileHandler.h"
#include "Player.h"
#include "RoundUI.h"
#include "Rng.h"
#include <iostream>
#include <cassert>

void testPlayer() {
    std::cout << "\n=== Testing Player ===" << std::endl;

    Player player("TestPlayer", 1000);
    std::cout << "✓ Created player: " << player.getName() << std::endl;
    std::cout << "✓ Initial balance: " << player.getBalance() << std::endl;

    player.updateBalance(-100);
    std::cout << "✓ After bet 100: " << player.getBalance() << std::endl;
    assert(player.getBalance() == 900);

    player.updateBalance(500);
    std::cout << "✓ After win 500: " << player.getBalance() << std::endl;
    assert(player.getBalance() == 1400);

    player.updateBalance(-2000);
    std::cout << "✓ After losing more than balance: " << player.getBalance() << std::endl;
}

void testFileHandler() {
    std::cout << "\n=== Testing FileHandler ===" << std::endl;

    std::vector<LeaderboardEntry> testEntries = {
        {"Alice", 2500},
        {"Bob", 1800},
        {"Charlie", 1200}
    };

    bool saved = FileHandler::saveLeaderboard(testEntries, "test_leaderboard.txt");
    std::cout << "✓ Saved leaderboard: " << (saved ? "Success" : "Failed") << std::endl;

    auto loaded = FileHandler::loadLeaderboard("test_leaderboard.txt");
    std::cout << "✓ Loaded " << loaded.size() << " entries" << std::endl;

    for (const auto& entry : loaded) {
        std::cout << "  - " << entry.name << ": " << entry.balance << std::endl;
    }

    LeaderboardEntry newEntry{"Dave", 3000};
    bool added = FileHandler::addEntry(newEntry, "test_leaderboard.txt");
    std::cout << "✓ Added new entry: " << (added ? "Success" : "Failed") << std::endl;

    auto updatedEntries = FileHandler::loadLeaderboard("test_leaderboard.txt");
    std::cout << "✓ Total entries after adding: " << updatedEntries.size() << std::endl;
}

void testRng() {
    std::cout << "\n=== Testing RNG ===" << std::endl;

    Rng rng;

    std::cout << "✓ 10 random numbers (1-100):" << std::endl;
    for (int i = 0; i < 10; i++) {
        int num = rng.randInt(1, 100);
        std::cout << "  " << num << std::endl;
        assert(num >= 1 && num <= 100);
    }

    std::cout << "✓ 5 random booleans:" << std::endl;
    for (int i = 0; i < 5; i++) {
        bool result = rng.randBool(0.5);
        std::cout << "  " << (result ? "true" : "false") << std::endl;
    }
}

void testRoundUI() {
    std::cout << "\n=== Testing RoundUI ===" << std::endl;

    RoundUI ui;

    ui.print("✓ Testing print function");

    std::vector<LeaderboardEntry> testEntries = {
        {"Player1", 5000},
        {"Player2", 3000},
        {"Player3", 1500}
    };

    ui.leaderboard("TEST LEADERBOARD", testEntries);
    std::cout << "✓ Leaderboard displayed" << std::endl;
}

void testCasino() {
    std::cout << "\n=== Testing Casino ===" << std::endl;

    Casino casino;
    std::cout << "✓ Casino instance created" << std::endl;

    casino.checkLeaderboard();
    std::cout << "✓ Leaderboard check completed" << std::endl;
}

int main() {
    std::cout << "╔════════════════════════════════╗" << std::endl;
    std::cout << "║    TEST PLAYGROUND - START     ║" << std::endl;
    std::cout << "╚════════════════════════════════╝" << std::endl;

    try {
        testPlayer();
        testRng();
        testFileHandler();
        testRoundUI();
        testCasino();

    } catch (const std::exception& e) {
        std::cerr << "\n✗ Error occurred: " << e.what() << std::endl;
        return 1;
    }

    // Opcjonalne czyszczenie plików testowych
    std::remove("test_leaderboard.txt");

    std::cout << "\n╔════════════════════════════════╗" << std::endl;
    std::cout << "║   ALL TESTS COMPLETED! ✓       ║" << std::endl;
    std::cout << "╚════════════════════════════════╝" << std::endl;

    return 0;
}

