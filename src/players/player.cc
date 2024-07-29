#include "player.h"

Player::Player(Colour c) : colour{c} {}

Colour Player::getColour() const {
    return colour;
}

Player::~Player() {}