#include "InputController.h"

InputController::InputController(Game& game): game(game) {
}

bool InputController::isKeyDown(uint keyCode) const {
    return pressedKeys.contains(keyCode);
}

float InputController::getMouseX() const {
    return mouseX;
}

float InputController::getMouseY() const {
    return mouseY;
}

float InputController::getMouseDx() const {
    return mouseDx;
}

float InputController::getMouseDy() const {
    return mouseDy;
}

void InputController::setKeyPressed(uint keyCode) {
    pressedKeys.insert(keyCode);
}

void InputController::setKeyReleased(uint keyCode) {
    pressedKeys.erase(keyCode);
}

void InputController::setMousePos(float newX, float newY) {
    this->rawMouseX = newX;
    this->rawMouseY = newY;
}

void InputController::update() {
    mouseDx = rawMouseX - this->mouseX;
    mouseDy = rawMouseY - this->mouseY;

    this->mouseX = rawMouseX;
    this->mouseY = rawMouseY;
}
