#include "header.h"
#include "shapes.h"
#include "colors.h"
#include "input/Input.hpp"
#include "physics/Physics.h"
#include "physics/Collision.h"
#include "Enemy.h"

// Window size
int windowWidth = 800;
int windowHeight = 600;





// ---------------------------------------
// Player attributes
// ---------------------------------------
float playerX = 120.0f; 
float playerY = 100.0f;
float playerWidth = 40.0f;
float playerHeight = 60.0f;
float playerMoveSpeed = 5.0f;
// ---------------------------------------
// Player attributes
// ---------------------------------------






// ---------------------------------------
// Ground attributes
// ---------------------------------------
float groundX = 0.0f;
float groundY = 0.0f;
float groundWidth = 800.0f;
float groundHeight = 80.0f;
// ---------------------------------------
// Ground attributes
// ---------------------------------------







// ---------------------------------------
// Gravity and jumping
// ---------------------------------------
float playerVelocityY = 0.0f; // Initial vertical velocity
//float gravityForce = 0.5f;
float jumpForce = 12.2f; 
bool playerGrounded = false;
// ---------------------------------------
// Gravity and jumping
// ---------------------------------------







// ---------------------------------------
// Score and game rules
// ---------------------------------------
int score = 0;
int lives = 3;
int winningScore = 6;
bool gameWon = false;
bool gameOver = false;
int currentLevel = 1;
int totalLevels = 3;
// ---------------------------------------
// Score and game rules
// ---------------------------------------





// groundTop collision calculation
float groundTop = groundY + groundHeight;






// -------------------------
// Platform structure
// -------------------------
struct Platform 
{
    float x;
    float y;
    float width;
    float height;
};



vector<Platform> platforms = 
{
    {190.0f, 180.0f, 160.0f, 20.0f},
    {430.0f, 270.0f, 160.0f, 20.0f},
    {620.0f, 360.0f, 130.0f, 20.0f}
};
// -------------------------
// Platform structure
// -------------------------







// -------------------------
// Coin structure
// -------------------------
struct Coin 
{
    float x;
    float y;
    float radius;
    bool collected;
};




vector<Coin> coins = 
{
    {120.0f, 120.0f, 10.0f, false},
    {230.0f, 230.0f, 10.0f, false},
    {330.0f, 230.0f, 10.0f, false},
    {490.0f, 320.0f, 10.0f, false},
    {700.0f, 410.0f, 10.0f, false},
    {760.0f, 120.0f, 10.0f, false}
};
// -------------------------
// Coin structure
// -------------------------




// -------------------------
// Level data structure
// -------------------------
struct LevelData
{
    vector<Platform> platforms;
    vector<Coin> coins;
    float enemyX;
    float enemyY;
    float enemyDirection;
};



vector<LevelData> levels =
{
    {
        {
            {190.0f, 180.0f, 160.0f, 20.0f},
            {430.0f, 270.0f, 160.0f, 20.0f},
            {620.0f, 360.0f, 130.0f, 20.0f}
        },
        {
            {120.0f, 120.0f, 10.0f, false},
            {230.0f, 230.0f, 10.0f, false},
            {330.0f, 230.0f, 10.0f, false},
            {490.0f, 320.0f, 10.0f, false},
            {700.0f, 410.0f, 10.0f, false},
            {760.0f, 120.0f, 10.0f, false}
        },
        520.0f,
        100.0f,
        1.0f
    },
    {
        {
            {190.0f, 180.0f, 160.0f, 20.0f},
            {430.0f, 270.0f, 160.0f, 20.0f},
            {620.0f, 360.0f, 130.0f, 20.0f}
        },
        {
            {120.0f, 120.0f, 10.0f, false},
            {230.0f, 230.0f, 10.0f, false},
            {330.0f, 230.0f, 10.0f, false},
            {490.0f, 320.0f, 10.0f, false},
            {700.0f, 410.0f, 10.0f, false},
            {760.0f, 120.0f, 10.0f, false}
        },
        520.0f,
        100.0f,
        1.0f
    },
    {
        {
            {190.0f, 180.0f, 160.0f, 20.0f},
            {430.0f, 270.0f, 160.0f, 20.0f},
            {620.0f, 360.0f, 130.0f, 20.0f}
        },
        {
            {120.0f, 120.0f, 10.0f, false},
            {230.0f, 230.0f, 10.0f, false},
            {330.0f, 230.0f, 10.0f, false},
            {490.0f, 320.0f, 10.0f, false},
            {700.0f, 410.0f, 10.0f, false},
            {760.0f, 120.0f, 10.0f, false}
        },
        520.0f,
        100.0f,
        1.0f
    }
};
// -------------------------
// Level data structure
// -------------------------










// ----------------------------
// Back to initial position
// ----------------------------
void resetPlayer()
{
    playerX = 120.0f;
    playerY = 100.0f;
    playerVelocityY = 0.0f;
    playerGrounded = false;
}
// ----------------------------
// Back to initial position
// ----------------------------






// ----------------------------
// Load level by number
// ----------------------------
void loadLevel(int levelNumber)
{
    int levelIndex = levelNumber - 1;

    if (levelIndex < 0 || levelIndex >= static_cast<int>(levels.size()))
    {
        return;
    }

    platforms = levels[levelIndex].platforms;
    coins = levels[levelIndex].coins;

    resetPlayer();

    Enemy::x = levels[levelIndex].enemyX;
    Enemy::y = levels[levelIndex].enemyY;
    Enemy::direction = levels[levelIndex].enemyDirection;

    score = 0;
    winningScore = static_cast<int>(coins.size());
}
// ----------------------------
// Load level by number
// ----------------------------






// ----------------------------
// Restart current level
// ----------------------------
void resetCurrentLevel()
{
    loadLevel(currentLevel);
}
// ----------------------------
// Restart current level
// ----------------------------











// ----------------------------
// Text pop-up
// ----------------------------
void drawText(float x, float y, const string& text, void* font = GLUT_BITMAP_HELVETICA_18)
{
    glRasterPos2f(x, y); // Set the position for the text
    for (char character : text)
    {
        glutBitmapCharacter(font, character);
    }
}
// ----------------------------
// Text pop-up
// ----------------------------










void updateGameStateAfterScoreChange()
{
    if (score >= winningScore)
    {
        if (currentLevel >= totalLevels)
        {
            gameWon = true;
        }
        else
        {
            currentLevel += 1;
            loadLevel(currentLevel);
        }
    }
}








// --------------------------------
// Check if player collects coins
// --------------------------------
bool isCoinCollectedByPlayer(const Coin& coin)
{
    float nearestX = max(playerX, min(coin.x, playerX + playerWidth));
    float nearestY = max(playerY, min(coin.y, playerY + playerHeight));

    float deltaX = coin.x - nearestX;
    float deltaY = coin.y - nearestY;

    return (deltaX * deltaX + deltaY * deltaY) <= (coin.radius * coin.radius);
}
// --------------------------------
// Check if player collects coins
// --------------------------------












// ================================
// Update Function 
// ================================
void update(int value)
{





    // ------------------------------
    // Frezze game if won or over
    // ------------------------------
    if (gameWon || gameOver)
    {
        glutPostRedisplay();          // Ensure the final state is rendered
        glutTimerFunc(8, update, 0);  // 120 FPS
        return;
    }
    // ------------------------------
    // Frezze game if won or over
    // ------------------------------




    // Save player Y before gravity for platform collision detection
    float previousPlayerY = playerY;




    // ------------------------------
    // Apply gravity to player
    // ------------------------------
    Physics::applyGravity(playerY, playerVelocityY);
    // ------------------------------
    // Apply gravity to player
    // ------------------------------







    // ------------------------------
    // Right and Left movement
    // ------------------------------
    if (Input::isLeftPressed() && !Input::isRightPressed()) 
    {
        playerX -= playerMoveSpeed; // Move left
    } 
    else if (Input::isRightPressed() && !Input::isLeftPressed()) 
    {
        playerX += playerMoveSpeed; // Move right
    }
    // ------------------------------
    // Right and Left movement
    // ------------------------------









    // ------------------------------
    // Jumping
    // ------------------------------
    if (Input::consumeJumpRequested() && playerGrounded)
    {
        playerVelocityY = jumpForce;
        playerGrounded = false;
    }
    // ------------------------------
    // Jumping
    // ------------------------------







    

    // ------------------------------------------
    // Ground collision/landing
    // ------------------------------------------
    bool landedThisFrame = false; 


    if (Collision::groundCollision(playerY, playerVelocityY, groundTop)) 
    {
        landedThisFrame = true;
    }
    // ------------------------------------------
    // Ground collision/landing
    // ------------------------------------------








    // -------------------------------------------
    // Platform collision/landing
    // -------------------------------------------
    for (const Platform& platform : platforms)
    {
        bool landedOnPlatform = Collision::platformCollision(
            previousPlayerY,
            playerX,
            playerY,
            playerWidth,
            playerVelocityY,
            platform.x,
            platform.y,
            platform.width,
            platform.height
        );

        if (landedOnPlatform)
        {
            landedThisFrame = true;
        }
    }
    // -------------------------------------------
    // Platform collision/landing
    // -------------------------------------------




    // Update grounded state after checking all collisions
    playerGrounded = landedThisFrame;





    // -----------------------------------
    // Keep player within window bounds
    // -----------------------------------
    if (playerX < 0.0f) 
    {
        playerX = 0.0f;
    }
    if (playerX + playerWidth > windowWidth) 
    {
        playerX = windowWidth - playerWidth;
    }
    // -----------------------------------
    // Keep player within window bounds
    // -----------------------------------





    
    
    // ---------------------------------
    // Update enemy position
    // ---------------------------------
    Enemy::update(windowWidth, groundX);
    // ---------------------------------
    // Update enemy position
    // ---------------------------------

    





    // --------------------------------
    // Check if enemy hits player
    // --------------------------------
    if (Enemy::hitsPlayer(playerX, playerY, playerWidth, playerHeight))
    {
        lives -= 1;

        if (lives <= 0)
        {
            gameOver = true;
        }
        else
        {
            resetCurrentLevel();
        }
    }
    // --------------------------------
    // Check if enemy hits player
    // --------------------------------
    

    

    

    // --------------------------------
    // coin collection 
    // --------------------------------
    for (Coin& coin : coins)
    {
        if (!coin.collected && isCoinCollectedByPlayer(coin))
        {
            coin.collected = true;
            score += 1;
        }
    }

    updateGameStateAfterScoreChange();
    // --------------------------------
    // coin collection
    // --------------------------------

    

    

    glutPostRedisplay();
    glutTimerFunc(8, update, 0); // 120 FPS
}
// ================================
// Update Function 
// ================================























// ================================
// Display Function 
// ================================
void display() 
{
    glClear(GL_COLOR_BUFFER_BIT);





    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();






    // ------------------------------
    // Ground rectangle
    // ------------------------------
    rectangle_with_4_vertices(
        groundX, groundY,
        groundX + groundWidth, groundY,
        groundX + groundWidth, groundY + groundHeight,
        groundX, groundY + groundHeight,
        grassR, grassG, grassB // Green color
    );
    // ------------------------------
    // Ground rectangle
    // ------------------------------









    // ----------------------------------------
    // Platforms rectangles foreach loop
    // ----------------------------------------
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
            
            brickR, brickG, brickB // Red color
        );
    }
    // ----------------------------------------
    // Platforms rectangles foreach loop
    // ----------------------------------------











    // -----------------------------------------
    // Coins
    // -----------------------------------------
    for (const Coin& coin : coins)
    {
        // if not collected, render the circle
        if (!coin.collected)
        {
            circle_with_fan(coin.x, coin.y, coin.radius, 255, 215, 0);
        }
    }
    // -----------------------------------------
    // Coins
    // -----------------------------------------










    //------------------------------
    //------------------------------
    // Matrix push
    //------------------------------
    //------------------------------
    glPushMatrix();
    




    glTranslatef(playerX, playerY, 0.0f); // Move the player to its current position
    // ------------------------------
    // Player rectangle
    // ------------------------------
    rectangle_with_4_vertices(
        0.0f, 0.0f,
        playerWidth, 0.0f,
        playerWidth, playerHeight,
        0.0f, playerHeight,
        marioRedR, marioRedG, marioRedB
    );
    // ------------------------------
    // Player rectangle
    // ------------------------------








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
    //------------------------------
    //------------------------------
    // Matrix pop
    //------------------------------
    //------------------------------









    // ------------------------------
    // Enemy rectangle 
    // ------------------------------
    Enemy::enemyDraw();
    // ------------------------------
    // Enemy rectangle
    // ------------------------------








    // ------------------------------
    // Score and lives text
    // ------------------------------
    glColor3ub(255, 255, 255);
    drawText(10.0f, windowHeight - 24.0f, "Score: " + to_string(score));
    drawText(10.0f, windowHeight - 46.0f, "Lives: " + to_string(lives));
    drawText(10.0f, windowHeight - 68.0f, "Level: " + to_string(currentLevel) + "/" + to_string(totalLevels));
    // ------------------------------
    // Score and lives text
    // ------------------------------






    // ------------------------------
    // Win/Lose text
    // ------------------------------
    if (gameWon)
    {
        glColor3ub(255, 255, 0);
        drawText(250.0f, 330.0f, "YOU WON ALL 3 LEVELS!");
        drawText(230.0f, 300.0f, "Great run. Final level cleared.");
    }
    else if (gameOver)
    {
        glColor3ub(255, 80, 80);
        drawText(290.0f, 330.0f, "GAME OVER");
        drawText(235.0f, 300.0f, "You lost all your lives.");
    }
    // ------------------------------
    // Win/Lose text
    // ------------------------------











    glFlush();
}
// ================================
// Display Function 
// ================================



















// ================================
// Initialization
// ================================
void init() 
{
    currentLevel = 1;
    lives = 3;
    gameWon = false;
    gameOver = false;
    loadLevel(currentLevel);

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
// Initialization
// ================================























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
    glutTimerFunc(8, update, 0); // 120 FPS

    glutMainLoop();

    return 0;
}
// ================================
// Main Function
// ================================