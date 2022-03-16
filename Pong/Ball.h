#pragma once
#include "..\Engine\Graphics\RenderableObject.h"
#include "../Engine/Graphics/Shape.h"

struct Velocity {
    float x = 0;
    float y = 0;
};

enum class WinState {
    PLAYING,
    LEFT_WON,
    RIGHT_WON
};

class Board;

class Ball :
    public RenderableObject {    
    Velocity vel;
    float width;
    float height;
    float acceleration = 1.0F;
public:
    Ball();

    WinState checkWin();
    void tick(Board& left, Board& right, float partialTick);
    void setVelocity(float x, float y);
    Velocity getVelocity();
    void reset(bool leftWon = true);
private:
    void handleWallBounce();
    void handleBoardBounce(Board& board, bool left);
    float getDistanceSqr(float destX, float destY);
};

