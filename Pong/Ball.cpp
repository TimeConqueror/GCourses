#include "Ball.h"
#include "Board.h"
#include "../Engine/Rand.h"
#include "../Engine/Vertex2f.h"
#define _USE_MATH_DEFINES
#include <MathHelper.h>

Ball::Ball(): RenderableObject(Shape::quad(Board::ratioX, Board::ratioX * 800.0F / 600)), width(Board::ratioX), height(Board::ratioX * 800.0F / 600) {
	reset();
};

WinState Ball::checkWin() {
	if (getPos().y > 1) {
		return WinState::LEFT_WON;
	} else if (getPos().x + width < -1) {
		return WinState::RIGHT_WON;
	}
	return WinState::PLAYING;
}

void Ball::tick(Board& left, Board& right, float partialTick) {
	handleWallBounce();
	handleBoardBounce(left, true);
	handleBoardBounce(right, false);

	setPos(getPos().x + vel.x, getPos().y + vel.y, 1.0F);
}

void Ball::handleWallBounce() {
	if (getPos().y + height >= 1 || getPos().y <= -1) {
		vel.y = -vel.y;
	}
}

void Ball::handleBoardBounce(Board& board, bool left) {
	float x = getPos().x;
	float y = getPos().y;

	//when it's too late
	if (left) {
		if (x < board.getPos().x)  return;
	} else if (x > board.getPos().x + board.getWidth()) {
		return;
	}

	float fault = 0.004F;

	if ((left ? board.getPos().x + board.getWidth() >= x + fault : board.getPos().x <= x + width - fault)
		&& !(y + height <board.getPos().y || y > board.getPos().y + board.getHeight())) {

		vel.x = abs(vel.x * 1.04);
		if (!left) {
			vel.x = -vel.x;
		}

		Vertex2f v;
		if (left) {
			v = Vertex2f{board.getPos().x + board.getWidth(), board.getPos().y + board.getHeight() / 2};
		} else {
			v = Vertex2f{board.getPos().x, board.getPos().y + board.getHeight() / 2};
		}

		float mult = 20;
		float factor = getDistanceSqr(v.x, v.y) * mult;
		vel.y = 0.2f * factor * 0.035;

		if (getDistanceSqr(v.x, v.y + board.getHeight() / 2) * mult > factor) {
			vel.y = -vel.y;
		}
	}
}

float Ball::getDistanceSqr(float destX, float destY) {
	float dx = getPos().x - destX;
	float dy = getPos().y - destY;
	return dx * dx + dy * dy;
}

void Ball::setVelocity(float x, float y) {
	vel.x = x;
	vel.y = y;
}

Velocity Ball::getVelocity() {
	return vel;
}

void Ball::reset(bool leftWon) {
	setPos(-width / 2, -height / 2, 1.0F);

	setVelocity(0.035, 0);

	if (!leftWon) vel.x = -vel.x;
}
