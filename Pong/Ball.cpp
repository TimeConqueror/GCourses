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
	if (getX() > 1) {
		return WinState::LEFT_WON;
	} else if (getX() + width < -1) {
		return WinState::RIGHT_WON;
	}
	return WinState::PLAYING;
}

void Ball::tick(Board& left, Board& right, float partialTick) {
	handleWallBounce();
	handleBoardBounce(left, true);
	handleBoardBounce(right, false);

	setX(getX() + vel.x);
	setY(getY() + vel.y);
}

void Ball::handleWallBounce() {
	if (getY() + height >= 1 || getY() <= -1) {
		vel.y = -vel.y;
	}
}

void Ball::handleBoardBounce(Board& board, bool left) {
	float x = getX();
	float y = getY();

	//when it's too late
	if (left) {
		if (x < board.getX())  return;
	} else if (x > board.getX() + board.getWidth()) {
		return;
	}

	float fault = 0.004F;

	if ((left ? board.getX() + board.getWidth() >= x + fault : board.getX() <= x + width - fault)
		&& !(y + height <board.getY() || y > board.getY() + board.getHeight())) {

		vel.x = abs(vel.x * 1.04);
		if (!left) {
			vel.x = -vel.x;
		}

		Vertex2f v;
		if (left) {
			v = Vertex2f{board.getX() + board.getWidth(), board.getY() + board.getHeight() / 2};
		} else {
			v = Vertex2f{board.getX(), board.getY() + board.getHeight() / 2};
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
	float dx = getX() - destX;
	float dy = getY() - destY;
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
	setX(-width / 2);
	setY(-height / 2);

	setVelocity(0.035, 0);

	if (!leftWon) vel.x = -vel.x;
}
