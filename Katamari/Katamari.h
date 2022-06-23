#pragma once
#include "Actor.h"
#include "Game.h"
#include "PlaneComponent.h"
#include "Planet.h"
#include "Graphics/Camera.h"
#include "Graphics/CameraHandler.h"

class ITickable;

class Katamari :
    public Game {
public:
    std::vector<Actor*> entities;
    Katamari(uint screenWidth, uint screenHeight);
protected:
    void init() override;
    void addActor(Actor* actor, float x, float z, float scale);
    void tick() override;
private:
    void handleInput();
};

