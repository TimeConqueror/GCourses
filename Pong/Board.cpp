#include "Board.h"
#include "../Engine/Graphics/ConstantBufferTypes.h"

const float Board::ratioX = 30.0F * 2 /*ratio from -1 to 1 means 2 */ / 800;
const float Board::ratioY = 150.0F * 2 /*ratio from -1 to 1 means 2 */ / 600;

float Board::getWidth() const {
	return width;
}

float Board::getHeight() const {
	return height;
}
