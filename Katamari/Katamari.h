#pragma once
#include "Game.h"
#include "PlaneComponent.h"
#include "Planet.h"
#include "Graphics/Camera.h"
#include "Graphics/CameraHandler.h"

class ITickable;

class Katamari :
    public Game {
private:
    std::vector<ITickable*> entities;

public:
    Katamari(uint screenWidth, uint screenHeight);
protected:
    void init() override;
    void addPlanet(Planet* planet);
    void tick() override;
private:
    void handleWinState();
    void handleInput();
};

