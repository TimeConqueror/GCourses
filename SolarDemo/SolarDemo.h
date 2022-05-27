#pragma once
#include "..\Engine\Game.h"
#include "PlaneComponent.h"
#include "Graphics/Camera.h"
#include "Graphics/CameraHandler.h"

class SolarDemo :
    public Game {
private:
public:
    SolarDemo(uint screenWidth, uint screenHeight);
protected:
    void init() override;
    void tick() override;
private:
    void handleWinState();
    void handleInput();
};

