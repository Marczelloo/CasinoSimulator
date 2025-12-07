//
// Created by moskw on 12.11.2025.
//

#ifndef KASYNO_ROULETTEGAME_H
#define KASYNO_ROULETTEGAME_H
#include "Game.h"
#include "RouletteTypes.h"

enum class RouletteBetType {
    BET_RED = 0,
    BET_BLACK,
    BET_GREEN,
    BET_NUMBER,
    BET_ODD,
    BET_EVEN,
    BET_LOW,
    BET_HIGH,
};

class RouletteGame: public Game {
private:
    int askForBet(int maxBalance) override;
    int renderInterface(const Player& player) override;
    int calculateScore(int selectedTile,int bet);
    void displayPayouts() const override;
    void animateSpin(const Player& player, int resultIndex);

    int lastScore;
    RouletteBetType betType;
    int betNumber;
    std::string errorMessage;

    std::vector<RouletteTile> initWheel();
    RouletteTileType getColorForNumber(int number) const;
    int spinWheel();

    std::vector<RouletteTile> wheel;
    std::vector<RouletteTile> prevTiles;
    int spunTile;


public:
    RouletteGame(Rng &rng);
    ~RouletteGame();
    GameState playRound(Player& player) override;
};


#endif //KASYNO_ROULETTEGAME_H