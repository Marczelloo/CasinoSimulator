cmake_minimum_required(VERSION 4.0)
project(Kasyno)

set(CMAKE_CXX_STANDARD 20)

add_executable(Kasyno main.cpp
        Player.cpp
        Player.h
        Game.cpp
        Game.h
        RoundUI.cpp
        RoundUI.h
        Casino.cpp
        Casino.h
        Rng.cpp
        Rng.h
        TextRes.h
        Enums.h
        FileHandler.cpp
        FileHandler.h
        TestPlayground.cpp)

add_executable(TestPlayground TestPlayground.cpp
        Player.cpp
        Player.h
        Game.cpp
        Game.h
        RoundUI.cpp
        RoundUI.h
        Casino.cpp
        Casino.h
        Rng.cpp
        Rng.h
        TextRes.h
        Enums.h
        FileHandler.cpp
        FileHandler.h)
