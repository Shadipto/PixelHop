#pragma once
#include "header.h"

// Attention!!!!!!!!
// All color parameters are unsigned char (0-255) for r, g, b
// All 2D orthographic coordinates are in the form of (x, y) where (0, 0) is the bottom-left corner of the window and (windowWidth, windowHeight) is the top-right corner of the window.
// All shapes are drawn in a counter-clockwise order for proper face culling if enabled in the future.
// All shapes are filled by default. For outlines, use the corresponding outline functions.




// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------





//-------------------------------
// Rectangle using GL_POLYGON and 4 vertices using color3ub
//-------------------------------
void rectangle_with_4_vertices(float x1, float y1, float x2, float y2,
               float x3, float y3, float x4, float y4, unsigned char r, unsigned char g, unsigned char b) {
    glBegin(GL_POLYGON);
        glColor3ub(r, g, b);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
        glVertex2f(x4, y4);
    glEnd();
}

// -------------------------------
// Rectangle using width-height using GL_POLYGON and color3ub
// -------------------------------
void rectangle_with_width_height(float x, float y, float width, float height, unsigned char r, unsigned char g, unsigned char b) {
    glBegin(GL_POLYGON);
        glColor3ub(r, g, b);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y - height);
        glVertex2f(x, y - height);
    glEnd();
}

// -----------------------------------------------
// Rectangle Outline using width-height using GL_LINE_LOOP and color3ub
// -----------------------------------------------
void rectangle_outline_with_width_height(float x, float y, float width, float height, unsigned char r, unsigned char g, unsigned char b) {
    glBegin(GL_LINE_LOOP);
        glColor3ub(r, g, b);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y - height);
        glVertex2f(x, y - height);
    glEnd();
}





// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------







// ------------------------------------------------
// Square using GL_POLYGON and 4 vertices
// ------------------------------------------------
void square_with_4_vertices(float x1, float y1, float x2, float y2,
            float x3, float y3, float x4, float y4, unsigned char r, unsigned char g, unsigned char b) {
    glBegin(GL_POLYGON);
        glColor3ub(r, g, b);    
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3); 
        glVertex2f(x4, y4);
    glEnd();
}

// ------------------------------------------------
// Square using center and size using GL_POLYGON
// ------------------------------------------------
void square_with_center_size(float centerX, float centerY, float size, unsigned char r, unsigned char g, unsigned char b) {
    float half = size / 2.0;
    glBegin(GL_POLYGON);
        glColor3ub(r, g, b);
        glVertex2f(centerX - half, centerY + half);
        glVertex2f(centerX + half, centerY + half);
        glVertex2f(centerX + half, centerY - half);
        glVertex2f(centerX - half, centerY - half);
    glEnd();
}

// ------------------------------------------------
// Square Outline using center and size using GL_LINE_LOOP
// ------------------------------------------------
void square_outline_with_center_size(float centerX, float centerY, float size, unsigned char r, unsigned char g, unsigned char b) {
    float half = size / 2.0;
    glBegin(GL_LINE_LOOP);
        glColor3ub(r, g, b);
        glVertex2f(centerX - half, centerY + half);
        glVertex2f(centerX + half, centerY + half);
        glVertex2f(centerX + half, centerY - half); 
        glVertex2f(centerX - half, centerY - half);
    glEnd();
}







// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------







// ------------------------------------------------
// Triangle using GL_POLYGON and 3 vertices
// ------------------------------------------------
void triangle_with_3_vertices(float x1, float y1, float x2, float y2,
                               float x3, float y3, unsigned char r, unsigned char g, unsigned char b) {
    glBegin(GL_POLYGON);
        glColor3ub(r, g, b);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
    glEnd();
}


// ------------------------------------------------
// Triangle using center and size using GL_POLYGON
// ------------------------------------------------
void triangle_with_center_size(float centerX, float centerY, float size, unsigned char r, unsigned char g, unsigned char b) {
    float h = size * sqrt(3) / 2.0;
    glBegin(GL_POLYGON);
        glColor3ub(r, g, b);
        glVertex2f(centerX, centerY + h * 2.0 / 3.0);
        glVertex2f(centerX - size / 2, centerY - h / 3.0);
        glVertex2f(centerX + size / 2, centerY - h / 3.0);
    glEnd();
}

// ------------------------------------------------
// Triangle Outline using GL_LINE_LOOP and 3 vertices
// ------------------------------------------------
void triangle_outline_with_3_vertices(float x1, float y1, float x2, float y2,
                                      float x3, float y3, unsigned char r, unsigned char g, unsigned char b) {
    glBegin(GL_LINE_LOOP);
        glColor3ub(r, g, b);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
    glEnd();
}   

// ------------------------------------------------
// Triangle Outline using center and size using GL_LINE_LOOP
// ------------------------------------------------
void triangle_outline_with_center_size(float centerX, float centerY, float size, unsigned char r, unsigned char g, unsigned char b) {
    float h = size * sqrt(3) / 2.0;
    glBegin(GL_LINE_LOOP);
        glColor3ub(r, g, b);
        glVertex2f(centerX, centerY + h * 2.0 / 3.0);
        glVertex2f(centerX - size / 2, centerY - h / 3.0);
        glVertex2f(centerX + size / 2, centerY - h / 3.0);
    glEnd();
}





// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------






// ------------------------------------------------
// Circle using Fan and color3ub
// ------------------------------------------------
void circle_with_fan(float centerX, float centerY, float radius, unsigned char r, unsigned char g, unsigned char b) {
    glBegin(GL_TRIANGLE_FAN);
        glColor3ub(r, g, b);
        glVertex2f(centerX, centerY);
        for (int i = 0; i <= 100; i++) {
            float angle = 2.0 * PI * i / 100;
            glVertex2f(centerX + radius * cos(angle),
                       centerY + radius * sin(angle));
        }
    glEnd();
}


// Circle Outline using GL_LINE_LOOP and color3ub
void circle_outline_with_fan(float centerX, float centerY, float radius, unsigned char r, unsigned char g, unsigned char b) {
    glBegin(GL_LINE_LOOP);
        glColor3ub(r, g, b);
        for (int i = 0; i <= 100; i++) {
            float angle = 2.0 * PI * i / 100;
            glVertex2f(centerX + radius * cos(angle),
                       centerY + radius * sin(angle));
        }
    glEnd();
}

// ------------------------------------------------
// Partial Circle (arc) using GL_LINE_STRIP and color3ub
// ------------------------------------------------
void circle_arc_with_fan(float centerX, float centerY, float radius, float startAngle, float endAngle, unsigned char r, unsigned char g, unsigned char b) {
    glBegin(GL_LINE_STRIP);
        glColor3ub(r, g, b);
        for (int i = 0; i <= 100; i++) {
            float angle = (startAngle + (endAngle - startAngle) * i / 100) * PI / 180.0;
            glVertex2f(centerX + radius * cos(angle),
                       centerY + radius * sin(angle));
        }   
    glEnd();
}




// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------



// ------------------------------------------------
// Polygon with n sides using center and radius using GL_POLYGON and color3ub
// ------------------------------------------------
void polygon_with_n_sides(float centerX, float centerY, float radius, int sides, unsigned char r, unsigned char g, unsigned char b) {
    glBegin(GL_POLYGON);
        glColor3ub(r, g, b);
        for (int i = 0; i < sides; i++) {
            float angle = 2.0 * PI * i / sides;
            glVertex2f(centerX + radius * cos(angle),
                       centerY + radius * sin(angle));
        }
    glEnd();
}

// ------------------------------------------------
// Polygon outline with n sides using center and radius and n sides using GL_LINE_LOOP and color3ub
// ------------------------------------------------
void polygon_outline_with_n_sides(float centerX, float centerY, float radius, int sides, unsigned char r, unsigned char g, unsigned char b) {
    glBegin(GL_LINE_LOOP);
        glColor3ub(r, g, b);
        for (int i = 0; i < sides; i++) {
            float angle = 2.0 * PI * i / sides;
            glVertex2f(centerX + radius * cos(angle),
                       centerY + radius * sin(angle));
        }
    glEnd();
}


