#include "header.h"
#include "shapes.h"
#include "colors.h"
#include "input/Input.hpp"
#include "physics/Physics.h"
#include "physics/Collision.h"

// Window size
int windowWidth = 800;
int windowHeight = 600;

// Player attributes
float playerX = 120.0f; 
float playerY = 100.0f;
float playerWidth = 40.0f;
float playerHeight = 60.0f;
float playerMoveSpeed = 5.0f;

// Ground attributes
float groundX = 0.0f;
float groundY = 0.0f;
float groundWidth = 800.0f;
float groundHeight = 80.0f;

// Gravity and jumping
float playerVelocityY = 0.0f;
float gravityForce = 0.5f;
float jumpForce = 12.2f;
bool playerGrounded = false;


// Day 6 variable for ground level
float groundTop = groundY + groundHeight;

struct Platform {
    float x;
    float y;
    float width;
    float height;
};

vector<Platform> platforms = {
    {190.0f, 180.0f, 160.0f, 20.0f},
    {430.0f, 270.0f, 160.0f, 20.0f},
    {620.0f, 360.0f, 130.0f, 20.0f}
};

void update(int value)
{
    // Store previous Y position for platform collision detection
    float previousPlayerY = playerY;
    bool landedThisFrame = false;

    // Handle jump input
    if (Input::consumeJumpRequested() && playerGrounded)
    {
        playerVelocityY = jumpForce;
        playerGrounded = false;
    }

    // Handle player movement based on input state
    if (Input::isLeftPressed() && !Input::isRightPressed()) 
    {
        playerX -= playerMoveSpeed;
    } 
    else if (Input::isRightPressed() && !Input::isLeftPressed()) 
    {
        playerX += playerMoveSpeed;
    }

    // Keep player inside the window
    if (playerX < 0.0f) 
    {
        playerX = 0.0f;
    }
    if (playerX + playerWidth > windowWidth) 
    {
        playerX = windowWidth - playerWidth;
    }

    // Physics 
    Physics::applyGravity(playerY, playerVelocityY, gravityForce);

    // Collision with ground
    landedThisFrame = Collision::resolveGroundCollision(playerY, playerVelocityY, groundTop) || landedThisFrame;

    // Collision with platforms
    for (const Platform& platform : platforms)
    {
        landedThisFrame = Collision::resolvePlatformCollision(
            previousPlayerY,
            playerX,
            playerY,
            playerWidth,
            playerVelocityY,
            platform.x,
            platform.y,
            platform.width,
            platform.height
        ) || landedThisFrame;
    }

    playerGrounded = landedThisFrame;

    glutPostRedisplay();
    // 8 ms timer for smooth updates [120 FPS]
    glutTimerFunc(8, update, 0);
}

// ================================
// Display Function 
// ================================
void display() 
{
    glClear(GL_COLOR_BUFFER_BIT);

    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Ground rectangle
    rectangle_with_4_vertices(
        groundX, groundY,
        groundX + groundWidth, groundY,
        groundX + groundWidth, groundY + groundHeight,
        groundX, groundY + groundHeight,
        grassR, grassG, grassB
    );

    // Platforms rectangles foreach loop
    for (const Platform& platform : platforms)
    {
        rectangle_with_4_vertices(
            platform.x,
            platform.y,
            platform.x + platform.width,
            platform.y,
            platform.x + platform.width,
            platform.y + platform.height,
            platform.x,
            platform.y + platform.height,
            brickR, brickG, brickB
        );
    }

    // Player rectangle rendering
    glPushMatrix();
    glTranslatef(playerX, playerY, 0.0f);

    rectangle_with_4_vertices(
        0.0f, 0.0f,
        playerWidth, 0.0f,
        playerWidth, playerHeight,
        0.0f, playerHeight,
        marioRedR, marioRedG, marioRedB
    );

    if(Input::isJumpPressed())
    {
        // jump indicator yellow box
        rectangle_outline_with_width_height(
            playerWidth / 4.0f, playerHeight + 10.0f,
            playerWidth / 2.0f, 10.0f,
            255, 255, 0 // Yellow color
        );
    }

    glPopMatrix();

    glFlush();
}



// ================================
// Initialization
// ================================
void init() {
    glClearColor(
        skyDayR / 255.0f,
        skyDayG / 255.0f,
        skyDayB / 255.0f,
        1.0f
    );

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // 2D coordinate system
    gluOrtho2D(0, windowWidth, 0, windowHeight);
}



// ================================
// Main Function
// ================================
int main(int argc, char** argv) 
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(windowWidth, windowHeight);

    glutInitWindowPosition(100, 100);

    glutCreateWindow("GLUT Window");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(Input::keyPress);
    glutKeyboardUpFunc(Input::keyRelease);
    // 8 ms timer for smooth updates [120 FPS]
    glutTimerFunc(8, update, 0);

    glutMainLoop();

    return 0;
}