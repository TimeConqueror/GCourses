#pragma once
#include <Game.h>

class SolarDemo :
    public Game {
private:

public:
    SolarDemo(uint screenWidth, uint screenHeight): Game(L"Solar Demo", screenWidth, screenHeight){}
protected:
    void init() override;
    void tick() override;
private:
    void handleWinState();
    void handleInput();
};

