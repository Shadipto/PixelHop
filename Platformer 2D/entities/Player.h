#ifndef PLAYER_H
#define PLAYER_H

#include "../core/Renderer.h"
#include "../input/Input.h"

class Player {
public:
    Player();
    void init(float startX, float startY);
    void update(float dt, Input& input);
    void render(Renderer& renderer) const;

    float x, y, w, h;
    float vx, vy;
    bool onGround;
    float prevX, prevY;
};

#endif // PLAYER_H
