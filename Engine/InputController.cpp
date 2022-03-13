#include "InputController.h"

InputController::InputController(Game& game): game(game) {
}

bool InputController::isKeyDown(uint keyCode) {
    return pressedKeys.contains(keyCode);
}

void InputController::setKeyPressed(uint keyCode) {
    pressedKeys.insert(keyCode);
}

void InputController::setKeyReleased(uint keyCode) {
    pressedKeys.erase(keyCode);
}
