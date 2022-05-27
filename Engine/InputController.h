#pragma once
#include "Utils.h"
#include <unordered_set>

class Game;

class InputController {
	friend class Window;

private:
	Game& game;
	std::unordered_set<uint> pressedKeys;

	float rawMouseX = 0;
	float rawMouseY = 0;

	float mouseX = 0;
	float mouseY = 0;

	float mouseDx = 0;
	float mouseDy = 0;
public:
	InputController(Game& game);
	bool isKeyDown(uint keyCode) const;

	float getMouseX() const;
	float getMouseY() const;

	float getMouseDx() const;
	float getMouseDy() const;
	void update();
private:
	void setKeyReleased(uint keyCode);
	void setKeyPressed(uint keyCode);
	void setMousePos(float newX, float newY);
};