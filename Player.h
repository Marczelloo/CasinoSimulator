//
// Created by moskw on 08.10.2025.
//

#ifndef KASYNO_PLAYER_H
#define KASYNO_PLAYER_H
#include <string>


class Player {
    std::string name;
    int balance;
    int winnings;
    int currentBet;
public:
    Player();
    Player(const std::string& name,const int& balance);

    std::string getName() const;
    int getBalance() const;
    int getWinnings() const;
    int getCurrentBet() const;

    void setName(const std::string& newName);
    void setBalance(const int& newBalance);
    void setWinnings(const int& newWinnings);
    void setCurrentBet(const int& newBet);

    void updateBalance(const int& amount);
};


#endif //KASYNO_PLAYER_H