#pragma once

namespace Collision {

inline bool resolveGroundCollision(float& playerY, float& playerVelocityY, float groundTop)
{
    if (playerY <= groundTop && playerVelocityY < 0.0f) {
        playerY = groundTop;
        playerVelocityY = 0.0f;
        return true;
    }

    return false;
}

inline bool resolvePlatformCollision(
    float previousPlayerY,
    float playerX,
    float& playerY, // reference as Y is always updated by gravity before collision checks
    float playerWidth,
    float& playerVelocityY, // reference as velocity is updated when landing on platform
    float platformX,
    float platformY,
    float platformWidth,
    float platformHeight
) {
    if (playerVelocityY >= 0.0f) {
        return false;
    }

    float playerLeft = playerX;
    float playerRight = playerX + playerWidth;
    float platformLeft = platformX;
    float platformRight = platformX + platformWidth;
    // Check for horizontal overlap and if player is crossing the platform top from above
    bool hasHorizontalOverlap = (playerRight > platformLeft) && (playerLeft < platformRight);

    float platformTop = platformY + platformHeight;
    // Check if player is crossing the platform top from above (i.e., falling onto the platform)
    bool crossedPlatformTop = (previousPlayerY >= platformTop) && (playerY <= platformTop);

    if (hasHorizontalOverlap && crossedPlatformTop) {
        playerY = platformTop;
        playerVelocityY = 0.0f;
        return true;
    }

    return false;
}

} // namespace Collision
