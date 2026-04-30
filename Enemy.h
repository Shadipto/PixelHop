#pragma once

#include "header.h"
#include "shapes.h"
#include "colors.h"

// =============================
// Enemy Namespace
// =============================
namespace Enemy 
{



    // Enemy attributes
    static float x = 520.0f;      
    static float y = 100.0f;      
    static float width = 40.0f;   
    static float height = 40.0f;  
    static float moveSpeed = 2.0f; 
    static float direction = 1.0f; // movement direction [1 ==> right, -1 ==> left]





    // -----------------------------------
    // overlap checking
    // -----------------------------------
    inline bool isOverlap(
        float leftA, float bottomA, float widthA, float heightA,
        float leftB, float bottomB, float widthB, float heightB
    )
    {
        float rightA = leftA + widthA;
        float topA = bottomA + heightA;
        float rightB = leftB + widthB;
        float topB = bottomB + heightB;

        if ((leftA < rightB) && (rightA > leftB) && (bottomA < topB) && (topA > bottomB)) 
        {
            return true; // Overlap exists
        }
        
        return false; // No overlap
    }
    // -----------------------------------
    // overlap checking 
    // -----------------------------------







    // --------------------------------
    // Check if enemy hits player
    // --------------------------------
    inline bool hitsPlayer(
        float playerX, float playerY, 
        float playerWidth, float playerHeight
    )
    {
        if (isOverlap(playerX, playerY, playerWidth, playerHeight, x, y, width, height))
        {
            return true; // Enemy hits player
        }
        return false; // Enemy does not hit player
    }
    // --------------------------------
    // Check if enemy hits player
    // --------------------------------










    // --------------------------------
    // Enemy Update Movement
    // --------------------------------
    inline void update(float windowWidth, float groundX)
    {
        x += moveSpeed * direction; // Move enemy in current direction

        if (x <= groundX)
        {
            x = groundX;
            direction = 1.0f; // right direction
        }
        else if (x + width >= windowWidth)
        {
            x = windowWidth - width;
            direction = -1.0f; // left direction
        }
    }
    // --------------------------------
    // Enemy Update Movement
    // --------------------------------
















    // --------------------------------
    // Enemy Draw [rectangle]
    // --------------------------------
    inline void enemyDraw()
    {
        rectangle_with_4_vertices(
            x, y,
            x + width, y,
            x + width, y + height,
            x, y + height,
            brickR, brickG, brickB
        );
    }
    // --------------------------------
    // Enemy Draw [rectangle]
    // --------------------------------





}
// =============================
// Enemy Namespace
// =============================