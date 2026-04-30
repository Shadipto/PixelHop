#pragma once

#include "../header.h"



// =============================
// Physics Namespace
// =============================
namespace Physics 
{




    // --------------------------------
    // Apply Gravity
    // --------------------------------
    inline void applyGravity(float& positionY, float& velocityY, float gravityForce = 0.5f)
    {
        velocityY -= gravityForce;
        positionY += velocityY;
    }
    // --------------------------------
    // Apply Gravity
    // --------------------------------






}
// =============================
// Physics Namespace
// =============================
