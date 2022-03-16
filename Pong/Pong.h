#pragma once
#include "..\Engine\Game.h"
#include "Board.h"

class Pong :
    public Game {
private:
    Board leftBoard;
    Board rightBoard;
public:
    Pong(uint screenWidth, uint screenHeight): leftBoard(true), rightBoard(false), Game(L"Pong", screenWidth, screenHeight){}
protected:
    virtual void init() override;
    virtual void tick() override;
};

