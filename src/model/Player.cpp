/**
 * Player.cpp
 */

#include "Player.hpp"

const double Player::turnStep_ = 0.3;
const double Player::moveStep_ = 6;
const double Player::viewAngleHalfWidth_ = M_PI / 4;

void Player::turnLeft() {
	viewAngleMiddle_ -= turnStep_;
	if (viewAngleMiddle_ <= 0) {
		viewAngleMiddle_ = M_PI * 2;
	}
}

void Player::turnRight() {
	viewAngleMiddle_ += turnStep_;
	if (viewAngleMiddle_ >= M_PI * 2) {
		viewAngleMiddle_ = 0;
	}
}

void Player::doStep(const Maze &maze, double x, double y) {
	if (!maze.isCollided(DoublePoint(x, y))) {
		position_.setX(x);
		position_.setY(y);
	}	
}

void Player::stepForward(const Maze &maze) {
	const double x = position_.getX() + cos(viewAngleMiddle_) * moveStep_;
	const double y = position_.getY() + sin(viewAngleMiddle_) * moveStep_;
	doStep(maze, x, y);
}

void Player::stepBackward(const Maze &maze) {
	const double x = position_.getX() - cos(viewAngleMiddle_) * moveStep_;
	const double y = position_.getY() - sin(viewAngleMiddle_) * moveStep_;
	doStep(maze, x, y);
}
