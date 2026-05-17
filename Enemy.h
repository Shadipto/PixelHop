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
    // Enemy Draw 
    // --------------------------------
    inline void enemyDraw()
    {
        float bw = width;
        float bh = height;
        float cx = x + bw * 0.5f;




        // ---------------------------------
        // Body (main rectangle)
        // ---------------------------------
        float bodyTop = y + bh * 0.75f;
        rectangle_with_4_vertices(
            x, y,
            x + bw, y,
            x + bw, bodyTop,
            x, bodyTop,
            enemyMonsterBodyR, enemyMonsterBodyG, enemyMonsterBodyB
        );
        // ---------------------------------
        // Body (main rectangle)
        // ---------------------------------






        // --------------------------------
        // Shadow
        // --------------------------------
        float headY = bodyTop;
        float headHeight = bh * 0.28f;
        rectangle_with_4_vertices(
            x + bw * 0.08f, headY,
            x + bw - bw * 0.08f, headY,
            x + bw - bw * 0.08f, headY + headHeight,
            x + bw * 0.08f, headY + headHeight,
            enemyMonsterShadowR, enemyMonsterShadowG, enemyMonsterShadowB
        );
        // --------------------------------
        // Shadow
        // --------------------------------



        // shadow circles 
        circle_with_fan(x + bw * 0.18f, headY + headHeight, bw * 0.12f, enemyMonsterShadowR, enemyMonsterShadowG, enemyMonsterShadowB);
        circle_with_fan(x + bw * 0.82f, headY + headHeight, bw * 0.12f, enemyMonsterShadowR, enemyMonsterShadowG, enemyMonsterShadowB);
        // shadow circles





        // --------------------------------
        // Eye, Pupil, Mouth, Horns
        // --------------------------------
        
        // Eye + pupil
        float eyeY = headY + headHeight * 0.6f;
        float eyeOffsetX = bw * 0.18f;
        float eyeR = bw * 0.08f;



        // Eyes 
        circle_with_fan(cx - eyeOffsetX, eyeY, eyeR, enemyMonsterEyeR, enemyMonsterEyeG, enemyMonsterEyeB);
        circle_with_fan(cx + eyeOffsetX, eyeY, eyeR, enemyMonsterEyeR, enemyMonsterEyeG, enemyMonsterEyeB);
        // Eyes



        // Pupils
        circle_with_fan(cx - eyeOffsetX, eyeY, eyeR * 0.45f, enemyMonsterPupilR, enemyMonsterPupilG, enemyMonsterPupilB);
        circle_with_fan(cx + eyeOffsetX, eyeY, eyeR * 0.45f, enemyMonsterPupilR, enemyMonsterPupilG, enemyMonsterPupilB);
        // Pupils




        // Mouth 
        float mouthW = bw * 0.28f;
        float mouthH = bh * 0.06f;
        float mouthX1 = cx - mouthW * 0.5f;
        float mouthY1 = headY + headHeight * 0.15f;




        // Mouth
        rectangle_with_4_vertices(mouthX1, mouthY1, mouthX1 + mouthW, mouthY1, mouthX1 + mouthW, mouthY1 + mouthH, mouthX1, mouthY1 + mouthH, enemyMonsterMouthR, enemyMonsterMouthG, enemyMonsterMouthB);
        // Mouth




        // Horns - small triangles
        float hornY = headY + headHeight + (bw * 0.03f);




        // Horns
        triangle_with_3_vertices(x + bw * 0.15f, headY + headHeight, x + bw * 0.08f, hornY, x + bw * 0.22f, hornY, enemyMonsterHornR, enemyMonsterHornG, enemyMonsterHornB);
        triangle_with_3_vertices(x + bw * 0.85f, headY + headHeight, x + bw * 0.78f, hornY, x + bw * 0.92f, hornY, enemyMonsterHornR, enemyMonsterHornG, enemyMonsterHornB);
        // Horns





        // Legs
        float legW = bw * 0.22f;
        float legH = bh * 0.18f;




        // Legs
        rectangle_with_4_vertices(x + bw * 0.14f, y - 0.0f, x + bw * 0.14f + legW, y - 0.0f, x + bw * 0.14f + legW, y + legH, x + bw * 0.14f, y + legH, enemyMonsterClawR, enemyMonsterClawG, enemyMonsterClawB);
        rectangle_with_4_vertices(x + bw * 0.64f, y - 0.0f, x + bw * 0.64f + legW, y - 0.0f, x + bw * 0.64f + legW, y + legH, x + bw * 0.64f, y + legH, enemyMonsterClawR, enemyMonsterClawG, enemyMonsterClawB);
        // Legs


    }
    // --------------------------------
    // Enemy Draw 
    // --------------------------------





}
// =============================
// Enemy Namespace
// =============================