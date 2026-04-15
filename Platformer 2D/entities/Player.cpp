#include "Player.h"
#include "../utils/Constants.h"

Player::Player() {
    x = 100.f; y = 200.f;
    w = 32.f; h = 48.f;
    vx = vy = 0.f;
    onGround = false;
}

void Player::init(float startX, float startY) {
    x = startX; y = startY;
}

void Player::update(float dt, Input& input) {
    // store previous position for collision resolution
    prevX = x;
    prevY = y;

    // horizontal movement
    vx = 0.f;
    if (input.isDown('a') || input.isDown('A')) vx = -Constants::MOVE_SPEED;
    if (input.isDown('d') || input.isDown('D')) vx = Constants::MOVE_SPEED;

    // jump (edge-triggered: consume single key press)
    if (input.wasPressed(' ') && onGround) {
        vy = Constants::JUMP_VELOCITY;
        onGround = false;
    }

    // apply gravity
    vy += Constants::GRAVITY * dt;

    // integrate
    x += vx * dt;
    y += vy * dt;
}

void Player::render(Renderer& renderer) const {
    renderer.drawRect(x, y, w, h, 0.9f, 0.1f, 0.2f);
}
