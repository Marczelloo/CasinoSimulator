cmake_minimum_required(VERSION 4.0)
project(Kasyno)

set(CMAKE_CXX_STANDARD 20)

# Główna aplikacja (BEZ TestPlayground.cpp)
add_executable(Kasyno
        main.cpp
        Player.cpp
        RoundUI.cpp
        Casino.cpp
        Rng.cpp
        FileHandler.cpp
        Games/SlotsGame.cpp
        Games/SlotsGame.h
        Games/RouletteGame.cpp
        Games/RouletteGame.h
        Games/BlackjackGame.cpp
        Games/BlackjackGame.h
)

# Testy (BEZ main.cpp)
add_executable(KasynoTests
        TestPlayground.cpp
        Player.cpp
        RoundUI.cpp
        Casino.cpp
        Rng.cpp
        FileHandler.cpp
)