#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace Constants {
    constexpr int WINDOW_WIDTH = 800;
    constexpr int WINDOW_HEIGHT = 600;
    // pixels / second^2 (downwards)
    constexpr float GRAVITY = -1500.0f;
    constexpr float MOVE_SPEED = 300.0f; // px/s
    constexpr float JUMP_VELOCITY = 600.0f; // px/s
    constexpr float FLOOR_Y = 50.0f; // y coordinate of the floor
}

#endif // CONSTANTS_H
