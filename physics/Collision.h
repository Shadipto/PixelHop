#pragma once


// =============================
// Collision Namespace
// =============================
namespace Collision 
{






    // --------------------------------
    // Ground Collision/Landing
    // --------------------------------
    inline bool groundCollision(float& playerY, float& playerVelocityY, float groundTop)
    {
        // Check if player is falling and has reached or passed the ground level
        if (playerY <= groundTop && playerVelocityY < 0.0f) 
        {
            playerY = groundTop;
            playerVelocityY = 0.0f;
            return true;
        }

        return false;
    }
    // --------------------------------
    // Ground Collision/Landing
    // --------------------------------




    




    // --------------------------------
    // Platform Collision/Landing
    // --------------------------------
    inline bool platformCollision(
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
            // Only check for falling onto platform [jumping up through it is allowed]
            if (playerVelocityY >= 0.0f) 
            {
                return false;
            }

            float playerLeft = playerX;
            float playerRight = playerX + playerWidth;
            float platformLeft = platformX;
            float platformRight = platformX + platformWidth;



            // Check for horizontal overlap and if player is crossing the platform top from above
            bool hasHorizontalOverlap = (playerRight > platformLeft) && (playerLeft < platformRight);


            // platform top
            float platformTop = platformY + platformHeight;


            // Check if player is crossing the platform top from above (i.e., falling onto the platform)
            bool crossedPlatformTop = (previousPlayerY >= platformTop) && (playerY <= platformTop);



            // If both conditions are true, we have a landing on the platform
            if (hasHorizontalOverlap && crossedPlatformTop) 
            {
                playerY = platformTop;
                playerVelocityY = 0.0f;
                return true;
            }

            return false;
    }
    // --------------------------------
    // Platform Collision/Landing
    // --------------------------------







}
// =============================
// Collision Namespace
// =============================
