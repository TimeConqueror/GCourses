#pragma once
#include "..\Engine\Game.h"
#include "Board.h"
#include "Ball.h"

class Pong :
    public Game {
private:
    Board leftBoard;
    Board rightBoard;
    Ball ball;

    float leftScore = 0;
    float rightScore = 0;
    bool paused = false;
public:
    Pong(uint screenWidth, uint screenHeight): leftBoard(true), rightBoard(false), Game(L"Pong", screenWidth, screenHeight){}
protected:
    virtual void init() override;
    virtual void tick() override;
private:
    void handleWinState();
    void handleInput();
};

