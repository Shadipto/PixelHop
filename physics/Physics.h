#pragma once

namespace Physics {

inline void applyGravity(float& positionY, float& velocityY, float gravityForce)
{
    velocityY -= gravityForce;
    positionY += velocityY;
}

} // namespace Physics
