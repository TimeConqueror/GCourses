#pragma once
#include "..\Engine\Game.h"
#include "PlaneComponent.h"
#include "Planet.h"
#include "Graphics/Camera.h"
#include "Graphics/CameraHandler.h"

class ITickable;

class SolarDemo :
    public Game {
private:
    std::vector<ITickable*> entities;

public:
    SolarDemo(uint screenWidth, uint screenHeight);
protected:
    void init() override;
    void addPlanet(Planet* planet);
    void tick() override;
private:
    void handleWinState();
    void handleInput();
};

