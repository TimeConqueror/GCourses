#pragma once
#include "Utils.h"
#include <unordered_set>

class Game;

class InputController {
private: 
	Game& game;
	std::unordered_set<uint> pressedKeys;
public:
	InputController(Game& game);
	bool isKeyDown(uint keyCode);
	void setKeyPressed(uint keyCode);
	void setKeyReleased(uint keyCode);
};