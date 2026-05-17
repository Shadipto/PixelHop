#pragma once

#include "header.h"
#include "colors.h"
#include "shapes.h"

void drawCenteredText(float centerX, float y, const string& text, void* font);

namespace MenuUI
{
    static float animationAngle = 0.0f;





    // --------------------------------
    // Menu drawing utilities
    // --------------------------------
    inline void drawRect(float x1, float y1, float x2, float y2, unsigned char r, unsigned char g, unsigned char b)
    {
        rectangle_with_width_height(x1, y2, x2 - x1, y2 - y1, r, g, b);
    }

    inline void drawFrame(float x1, float y1, float x2, float y2, unsigned char r, unsigned char g, unsigned char b)
    {
        rectangle_outline_with_width_height(x1, y2, x2 - x1, y2 - y1, r, g, b);
    }

    inline void drawCoin(float cx, float cy, float radius, float pulseScale)
    {
        glPushMatrix();
        glTranslatef(cx, cy, 0.0f);
        glScalef(pulseScale, pulseScale, 1.0f);
        circle_with_fan(0.0f, 0.0f, radius, 255, 215, 0);
        glColor3ub(200, 150, 0);
        glLineWidth(4.0f);
        glBegin(GL_LINES);
            glVertex2f(-radius, 0.0f);
            glVertex2f(radius, 0.0f);
        glEnd();
        glLineWidth(1.0f);
        glPopMatrix();
    }
    // --------------------------------
    // Menu drawing utilities
    // --------------------------------








    // --------------------------------
    // Menu main functions
    // --------------------------------
    inline void reset()
    {
        animationAngle = 0.0f;
    }

    inline void update()
    {
        animationAngle += 2.5f;
        if (animationAngle >= 360.0f)
        {
            animationAngle -= 360.0f;
        }
    }
    // --------------------------------
    // Menu main functions
    // --------------------------------






    inline void draw(float windowWidth, float windowHeight)
    {
        float pulseScale = 1.0f + 0.14f * sin(animationAngle * PI / 180.0f);
        float smallPulse = 1.0f + 0.08f * sin((animationAngle + 90.0f) * PI / 180.0f);
        float promptPulse = 1.0f + 0.05f * sin((animationAngle * 1.8f) * PI / 180.0f);

        float cardX1 = 70.0f;
        float cardY1 = 60.0f;
        float cardX2 = windowWidth - 70.0f;
        float cardY2 = windowHeight - 60.0f;
        float centerX = windowWidth * 0.5f;
        float leftPanelCenterX = cardX1 + 147.5f;
        float rightPanelCenterX = cardX2 - 147.5f;

        
        glBegin(GL_QUADS);
            glColor3ub(menuBottomR, menuBottomG, menuBottomB);
            glVertex2f(0.0f, windowHeight);
            glVertex2f(windowWidth, windowHeight);

            glColor3ub(menuTopR, menuTopG, menuTopB);
            glVertex2f(windowWidth, 0.0f);
            glVertex2f(0.0f, 0.0f);
        glEnd();

        rectangle_with_width_height(cardX1, cardY2, cardX2 - cardX1, cardY2 - cardY1, 10, 30, 55);
        rectangle_outline_with_width_height(cardX1, cardY2, cardX2 - cardX1, cardY2 - cardY1, 255, 220, 120);

        rectangle_with_width_height(centerX - 78.0f, cardY2 - 34.0f, 156.0f, 28.0f, 255, 220, 120);
        rectangle_outline_with_width_height(centerX - 78.0f, cardY2 - 34.0f, 156.0f, 28.0f, 20, 45, 70);
        glColor3ub(255, 255, 255);
        drawCenteredText(centerX, cardY2 - 54.0f, "MENU", GLUT_BITMAP_HELVETICA_18);

        rectangle_with_width_height(centerX - 170.0f, 456.0f, 340.0f, 58.0f, 18, 45, 78);
        rectangle_outline_with_width_height(centerX - 170.0f, 456.0f, 340.0f, 58.0f, 255, 215, 0);
        glPushMatrix();
        glTranslatef(centerX, 428.0f, 0.0f);
        glScalef(pulseScale, pulseScale, 1.0f);
        glColor3ub(20, 20, 20);
        drawCenteredText(0.0f, -4.0f, "PIXELHOP", GLUT_BITMAP_TIMES_ROMAN_24);
        glColor3ub(255, 255, 255);
        drawCenteredText(0.0f, -6.0f, "PIXELHOP", GLUT_BITMAP_TIMES_ROMAN_24);
        glPopMatrix();

        glColor3ub(255, 235, 150);
        drawCenteredText(centerX, 354.0f, "Jump, collect, and clear every level", GLUT_BITMAP_HELVETICA_18);

        glPushMatrix();
        glTranslatef(centerX, 307.0f, 0.0f);
        glScalef(promptPulse, promptPulse, 1.0f);

        glColor3ub(255, 190, 40);
        rectangle_with_width_height(-168.0f, 30.0f, 336.0f, 60.0f, 120, 65, 18);
        rectangle_outline_with_width_height(-168.0f, 30.0f, 336.0f, 60.0f, 255, 235, 120);

        glColor3ub(255, 215, 0);
        rectangle_with_width_height(-155.0f, 24.0f, 310.0f, 48.0f, 80, 45, 20);
        rectangle_outline_with_width_height(-155.0f, 24.0f, 310.0f, 48.0f, 255, 215, 0);

        glColor3ub(255, 245, 180);
        drawCenteredText(0.0f, -2.0f, "Press Enter to Start", GLUT_BITMAP_HELVETICA_18);

        glColor3ub(255, 220, 120);
        glLineWidth(2.0f);
        glBegin(GL_LINES);
            glVertex2f(104.0f, -1.0f);
            glVertex2f(126.0f, -1.0f);
        glEnd();
        glLineWidth(1.0f);

        glColor3ub(255, 215, 0);
        triangle_with_3_vertices(126.0f, 0.0f, 118.0f, 6.0f, 118.0f, -6.0f, 255, 215, 0);

        glColor3ub(255, 255, 255);
        glPopMatrix();

        rectangle_with_width_height(cardX1 + 40.0f, 262.0f, 215.0f, 52.0f, 20, 45, 70);
        rectangle_outline_with_width_height(cardX1 + 40.0f, 262.0f, 215.0f, 52.0f, 90, 210, 255);
        glColor3ub(255, 255, 255);
        drawCenteredText(leftPanelCenterX, 244.0f, "Controls", GLUT_BITMAP_HELVETICA_18);
        glColor3ub(220, 235, 255);
        drawCenteredText(leftPanelCenterX, 224.0f, "A / D move   Space jump", GLUT_BITMAP_HELVETICA_18);

        rectangle_with_width_height(cardX2 - 255.0f, 262.0f, 215.0f, 52.0f, 35, 20, 60);
        rectangle_outline_with_width_height(cardX2 - 255.0f, 262.0f, 215.0f, 52.0f, 255, 160, 90);
        glColor3ub(255, 255, 255);
        drawCenteredText(rightPanelCenterX, 244.0f, "Objective", GLUT_BITMAP_HELVETICA_18);
        glColor3ub(255, 230, 200);
        drawCenteredText(rightPanelCenterX, 224.0f, "Collect all coins", GLUT_BITMAP_HELVETICA_18);

        glColor3ub(255, 255, 255);
        drawCenteredText(centerX, 166.0f, "3 Levels to Conquer", GLUT_BITMAP_HELVETICA_18);

        drawCoin(cardX1 + 74.0f, 158.0f, 16.0f, smallPulse);
        drawCoin(cardX2 - 74.0f, 158.0f, 16.0f, smallPulse);

        glColor3ub(255, 220, 120);
        drawCenteredText(centerX, 118.0f, "Clear the challenge. Unlock the next stage.", GLUT_BITMAP_HELVETICA_18);
    }
}
