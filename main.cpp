#include "header.h"
#include "shapes.h"
#include "colors.h"
#include "menu.h"
#include "input/Input.hpp"
#include "physics/Physics.h"
#include "physics/Collision.h"
#include "Enemy.h"
#include "music.h"



// ---------------------------------------
// Window size
// ---------------------------------------
int windowWidth = 800;
int windowHeight = 600;
// ---------------------------------------
// Window size
// ---------------------------------------





// ---------------------------------------
// Player attributes
// ---------------------------------------
float playerX = 120.0f; 
float playerY = 100.0f;
float playerWidth = 40.0f;
float playerHeight = 60.0f;
float playerMoveSpeed = 5.0f;
float playerFacing = 1.0f;
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
int winningScore = 9;
bool gameWon = false;
bool gameOver = false;
int currentLevel = 1;
int totalLevels = 3;
bool showMenu = true;
// ---------------------------------------
// Score and game rules
// ---------------------------------------





// ---------------------------------------
// Animation states
// ---------------------------------------
float coinRotationAngle = 0.0f;  // Rotation angle (degree)
// ---------------------------------------
// Animation states
// ---------------------------------------



// groundTop collision calculation
float groundTop = groundY + groundHeight;





// ---------------------------------------
// Player rendering
// ---------------------------------------
inline void drawPlayerSprite()
{
    rectangle_with_width_height(4.0f, 8.0f, 12.0f, 8.0f, marioBrownR, marioBrownG, marioBrownB);
    rectangle_outline_with_width_height(4.0f, 8.0f, 12.0f, 8.0f, marioBlackR, marioBlackG, marioBlackB);

    rectangle_with_width_height(22.0f, 8.0f, 14.0f, 9.0f, marioBrownR, marioBrownG, marioBrownB);
    rectangle_outline_with_width_height(22.0f, 8.0f, 14.0f, 9.0f, marioBlackR, marioBlackG, marioBlackB);

    rectangle_with_width_height(10.0f, 18.0f, 8.0f, 16.0f, marioBlueR, marioBlueG, marioBlueB);
    rectangle_outline_with_width_height(10.0f, 18.0f, 8.0f, 16.0f, marioBlackR, marioBlackG, marioBlackB);

    rectangle_with_width_height(20.0f, 18.0f, 10.0f, 18.0f, marioBlueR, marioBlueG, marioBlueB);
    rectangle_outline_with_width_height(20.0f, 18.0f, 10.0f, 18.0f, marioBlackR, marioBlackG, marioBlackB);

    rectangle_with_width_height(8.0f, 30.0f, 24.0f, 14.0f, marioRedR, marioRedG, marioRedB);
    rectangle_outline_with_width_height(8.0f, 30.0f, 24.0f, 14.0f, marioBlackR, marioBlackG, marioBlackB);

    rectangle_with_width_height(13.0f, 35.0f, 13.0f, 13.0f, marioBlueR, marioBlueG, marioBlueB);
    rectangle_outline_with_width_height(13.0f, 35.0f, 13.0f, 13.0f, marioBlackR, marioBlackG, marioBlackB);

    circle_with_fan(16.0f, 40.0f, 1.8f, marioYellowR, marioYellowG, marioYellowB);
    circle_outline_with_fan(16.0f, 40.0f, 1.8f, marioBlackR, marioBlackG, marioBlackB);
    circle_with_fan(24.5f, 40.0f, 1.8f, marioYellowR, marioYellowG, marioYellowB);
    circle_outline_with_fan(24.5f, 40.0f, 1.8f, marioBlackR, marioBlackG, marioBlackB);

    rectangle_with_width_height(5.5f, 27.0f, 5.0f, 11.0f, marioSkinR, marioSkinG, marioSkinB);
    rectangle_outline_with_width_height(5.5f, 27.0f, 5.0f, 11.0f, marioBlackR, marioBlackG, marioBlackB);

    circle_with_fan(4.8f, 23.5f, 3.0f, marioWhiteR, marioWhiteG, marioWhiteB);
    circle_outline_with_fan(4.8f, 23.5f, 3.0f, marioBlackR, marioBlackG, marioBlackB);

    rectangle_with_width_height(30.0f, 28.0f, 5.0f, 10.0f, marioSkinR, marioSkinG, marioSkinB);
    rectangle_outline_with_width_height(30.0f, 28.0f, 5.0f, 10.0f, marioBlackR, marioBlackG, marioBlackB);

    circle_with_fan(34.0f, 24.5f, 3.1f, marioWhiteR, marioWhiteG, marioWhiteB);
    circle_outline_with_fan(34.0f, 24.5f, 3.1f, marioBlackR, marioBlackG, marioBlackB);

    rectangle_with_width_height(10.0f, 42.0f, 4.0f, 4.0f, marioSkinR, marioSkinG, marioSkinB);
    rectangle_with_width_height(11.0f, 46.0f, 19.0f, 9.0f, marioRedR, marioRedG, marioRedB);
    rectangle_outline_with_width_height(11.0f, 46.0f, 19.0f, 9.0f, marioBlackR, marioBlackG, marioBlackB);
    rectangle_with_width_height(9.0f, 44.0f, 22.0f, 4.0f, marioRedR, marioRedG, marioRedB);
    rectangle_outline_with_width_height(9.0f, 44.0f, 22.0f, 4.0f, marioBlackR, marioBlackG, marioBlackB);

    circle_with_fan(14.0f, 47.0f, 1.7f, marioYellowR, marioYellowG, marioYellowB);
    circle_outline_with_fan(14.0f, 47.0f, 1.7f, marioBlackR, marioBlackG, marioBlackB);
    circle_with_fan(27.0f, 47.0f, 1.7f, marioYellowR, marioYellowG, marioYellowB);
    circle_outline_with_fan(27.0f, 47.0f, 1.7f, marioBlackR, marioBlackG, marioBlackB);

    rectangle_with_width_height(20.0f, 41.0f, 2.5f, 3.0f, marioBlackR, marioBlackG, marioBlackB);
    circle_with_fan(31.0f, 39.0f, 2.3f, marioSkinR, marioSkinG, marioSkinB);
    circle_outline_with_fan(31.0f, 39.0f, 2.3f, marioBlackR, marioBlackG, marioBlackB);

    rectangle_with_width_height(20.5f, 37.5f, 8.0f, 2.6f, marioBlackR, marioBlackG, marioBlackB);
    rectangle_with_width_height(21.0f, 35.0f, 6.8f, 2.2f, marioBlackR, marioBlackG, marioBlackB);

    circle_with_fan(24.5f, 42.5f, 1.8f, marioWhiteR, marioWhiteG, marioWhiteB);
    circle_outline_with_fan(24.5f, 42.5f, 1.8f, marioBlackR, marioBlackG, marioBlackB);
    circle_with_fan(25.1f, 42.2f, 0.8f, marioBlackR, marioBlackG, marioBlackB);

    rectangle_with_width_height(23.0f, 19.0f, 2.5f, 14.0f, marioBrownR, marioBrownG, marioBrownB);
    rectangle_outline_with_width_height(23.0f, 19.0f, 2.5f, 14.0f, marioBlackR, marioBlackG, marioBlackB);
    rectangle_with_width_height(13.0f, 19.0f, 3.0f, 13.0f, marioBrownR, marioBrownG, marioBrownB);
    rectangle_outline_with_width_height(13.0f, 19.0f, 3.0f, 13.0f, marioBlackR, marioBlackG, marioBlackB);

    rectangle_with_width_height(10.0f, 6.0f, 13.0f, 4.0f, marioBrownR, marioBrownG, marioBrownB);
    rectangle_outline_with_width_height(10.0f, 6.0f, 13.0f, 4.0f, marioBlackR, marioBlackG, marioBlackB);
    rectangle_with_width_height(23.0f, 6.0f, 13.0f, 5.0f, marioBrownR, marioBrownG, marioBrownB);
    rectangle_outline_with_width_height(23.0f, 6.0f, 13.0f, 5.0f, marioBlackR, marioBlackG, marioBlackB);
}
// ---------------------------------------
// Player rendering
// ---------------------------------------

inline void handleKeyPress(unsigned char key, int x, int y)
{
    if (key == 27)
    {
        Music::stop();
        exit(0);
    }

    Input::keyPress(key, x, y);
}

inline void handleKeyRelease(unsigned char key, int x, int y)
{
    Input::keyRelease(key, x, y);
}






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
    {200.0f, 180.0f, 150.0f, 20.0f},     // Platform 1
    {450.0f, 240.0f, 140.0f, 20.0f},     // Platform 2
    {150.0f, 200.0f, 100.0f, 20.0f},     // Platform 3
    {550.0f, 280.0f, 160.0f, 20.0f},     // Platform 4
    {350.0f, 320.0f, 120.0f, 20.0f},     // Platform 5
    {650.0f, 380.0f, 100.0f, 20.0f}      // Platform 6
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
    {220.0f, 220.0f, 10.0f, false},      
    {470.0f, 280.0f, 10.0f, false},      
    {170.0f, 240.0f, 10.0f, false},    

    {570.0f, 320.0f, 10.0f, false},      
    {370.0f, 360.0f, 10.0f, false},      
    
    {750.0f, 140.0f, 10.0f, false},      
    {100.0f, 130.0f, 10.0f, false},      
    {670.0f, 420.0f, 10.0f, false},      
    {400.0f, 150.0f, 10.0f, false}       
};
// -------------------------
// Coin structure
// -------------------------




// -------------------------
// Enemy structure
// -------------------------
struct GameEnemy
{
    float x;
    float y;
    float width;
    float height;
    float moveSpeed;
    float direction;        // 1.0 ==> right, -1.0 ==> left
    float minX;             // boundary (left)
    float maxX;             // boundary (right)
};



vector<GameEnemy> enemies = 
{
    {200.0f, 220.0f, 40.0f, 40.0f, 2.0f, 1.0f, 180.0f, 350.0f},
    
    {550.0f, 320.0f, 40.0f, 40.0f, 2.0f, -1.0f, 500.0f, 710.0f},
    
    {600.0f, 120.0f, 40.0f, 40.0f, 1.5f, 1.0f, 550.0f, 750.0f}
};
// -------------------------
// Enemy structure
// -------------------------







// -------------------------
// Cloud
// -------------------------
struct Cloud
{
    float x;
    float y;
    float radius;
    float speed;    // movement speed 
};

struct CloudPair
{
    float x1, y1, r1;
    float x2, y2, r2;
    float x3, y3, r3;
};

inline void drawCloud(float x, float y, float radius, unsigned char r, unsigned char g, unsigned char b)
{
    circle_with_fan(x - radius * 0.95f, y - radius * 0.05f, radius * 0.75f, r, g, b);
    circle_with_fan(x, y + radius * 0.18f, radius, r, g, b);
    circle_with_fan(x + radius * 1.0f, y - radius * 0.02f, radius * 0.82f, r, g, b);
    circle_with_fan(x + radius * 0.18f, y + radius * 0.42f, radius * 0.62f, r, g, b);
}

inline void drawMoon(float x, float y, float radius,
                              unsigned char coreR, unsigned char coreG, unsigned char coreB,
                              unsigned char glowR, unsigned char glowG, unsigned char glowB,
                              bool isMoon = false)
{
    circle_with_fan(x, y, radius * 1.35f, glowR, glowG, glowB);
    circle_with_fan(x, y, radius, coreR, coreG, coreB);

    if (isMoon)
    {
        circle_with_fan(x - radius * 0.28f, y + radius * 0.18f, radius * 0.68f, glowR, glowG, glowB);
        circle_with_fan(x + radius * 0.22f, y + radius * 0.05f, radius * 0.12f, glowR, glowG, glowB);
        circle_with_fan(x - radius * 0.02f, y - radius * 0.24f, radius * 0.10f, glowR, glowG, glowB);
    }
}

inline void drawSun(float x, float y, float radius,
                            unsigned char outerR, unsigned char outerG, unsigned char outerB,
                            unsigned char midR, unsigned char midG, unsigned char midB,
                            unsigned char innerR, unsigned char innerG, unsigned char innerB)
{
    circle_with_fan(x, y, radius * 1.40f, outerR, outerG, outerB);
    circle_with_fan(x, y, radius * 1.00f, midR, midG, midB);
    circle_with_fan(x, y, radius * 0.70f, innerR, innerG, innerB);
}


vector<Cloud> clouds =
{
    // Left
    {100.0f, windowHeight - 80.0f, 26.0f, 0.22f},
    {240.0f, windowHeight - 70.0f, 30.0f, 0.35f},
    {390.0f, windowHeight - 85.0f, 24.0f, 0.28f},
    {580.0f, windowHeight - 75.0f, 28.0f, 0.18f},

};



// -------------------------
// Level data structure
// -------------------------
struct LevelData
{
    vector<Platform> platforms;
    vector<Coin> coins;
    vector<GameEnemy> levelEnemies;
};


vector<LevelData> levels =
{
    // ===========================
    // LEVEL 1 - Dipto
    // ===========================
    {
        // Platforms 
        {
            {100.0f, 150.0f, 140.0f, 20.0f},     // Start

            {300.0f, 220.0f, 120.0f, 20.0f},

            {500.0f, 160.0f, 140.0f, 20.0f},     

            {250.0f, 300.0f, 110.0f, 20.0f},   

            {480.0f, 360.0f, 130.0f, 20.0f},     

            {700.0f, 240.0f, 140.0f, 20.0f},     

            {600.0f, 440.0f, 120.0f, 20.0f}      
        },

        // Coins 
        {
            {130.0f, 200.0f, 10.0f, false},
            {330.0f, 260.0f, 10.0f, false},

            {530.0f, 200.0f, 10.0f, false},

            {270.0f, 340.0f, 10.0f, false},
            {510.0f, 400.0f, 10.0f, false},

            {730.0f, 280.0f, 10.0f, false},

            {630.0f, 480.0f, 10.0f, false},

            {400.0f, 130.0f, 10.0f, false},

            {650.0f, 170.0f, 10.0f, false}
        },

        // Enemies 
        {
            {120.0f, 170.0f, 40.0f, 40.0f, 1.5f, 1.0f, 100.0f, 240.0f},

            {500.0f, 180.0f, 40.0f, 40.0f, 2.0f, -1.0f, 480.0f, 640.0f},

            {260.0f, 320.0f, 40.0f, 40.0f, 1.8f, 1.0f, 250.0f, 360.0f},

            {650.0f, 130.0f, 40.0f, 40.0f, 1.5f, 1.0f, 600.0f, 800.0f}
        }
    },
    // ===========================
    // LEVEL 2 - Shamin
    // ===========================
    {
        {
            {80.0f, 140.0f, 140.0f, 20.0f},    
            {260.0f, 200.0f, 120.0f, 20.0f},   
            {420.0f, 160.0f, 100.0f, 20.0f},   
            {620.0f, 160.0f, 120.0f, 20.0f},   
            {520.0f, 260.0f, 90.0f, 20.0f},    
            {440.0f, 340.0f, 80.0f, 20.0f},    
            {360.0f, 420.0f, 80.0f, 20.0f},    
            {680.0f, 460.0f, 120.0f, 20.0f}    
        },

        // Coins
        {
            {110.0f, 180.0f, 10.0f, false},
            {290.0f, 240.0f, 10.0f, false},
            {450.0f, 200.0f, 10.0f, false},

            {640.0f, 200.0f, 10.0f, false},
            {540.0f, 300.0f, 10.0f, false},

            {380.0f, 460.0f, 10.0f, false},
            {520.0f, 200.0f, 10.0f, false},

            {360.0f, 460.0f, 10.0f, false},

            {700.0f, 500.0f, 10.0f, false},
            {200.0f, 260.0f, 10.0f, false}
        },

        // Enemies
        {
            {260.0f, 240.0f, 36.0f, 36.0f, 1.6f, 1.0f, 240.0f, 350.0f},
            {620.0f, 200.0f, 36.0f, 36.0f, 1.8f, -1.0f, 600.0f, 740.0f},
            {460.0f, 120.0f, 36.0f, 36.0f, 2.2f, 1.0f, 420.0f, 760.0f}
        }
    },
    // ===========================
    // LEVEL 3 - Moderately Hard (Balanced)
    // ===========================
    {
        // Platforms (9 total): wider, more forgiving, challenging but fair
        {
            {100.0f, 150.0f, 140.0f, 20.0f},    // Start platform
            {280.0f, 210.0f, 110.0f, 20.0f},    // Platform #1 (wider for easier landing)
            {420.0f, 170.0f, 120.0f, 20.0f},    // Platform #2 (medium gap)
            {580.0f, 240.0f, 100.0f, 20.0f},    // Platform #3 (still challenging)
            {350.0f, 300.0f, 120.0f, 20.0f},    // Vertical climb starts (wider)
            {500.0f, 360.0f, 110.0f, 20.0f},    // Platform #4 (mid-climb, wider)
            {650.0f, 320.0f, 110.0f, 20.0f},    // Recovery platform (wider)
            {450.0f, 420.0f, 120.0f, 20.0f},    // Gauntlet section (wider)
            {680.0f, 460.0f, 130.0f, 20.0f}     // Final platform (goal, wider)
        },

        // Coins (10 total): more safe coins, fewer risky ones
        {
            {130.0f, 190.0f, 10.0f, false},     // Safe coin 1 (start area)
            {310.0f, 250.0f, 10.0f, false},     // Safe coin 2 (platform #1)
            {450.0f, 210.0f, 10.0f, false},     // Medium challenge
            {610.0f, 280.0f, 10.0f, false},     // Challenge coin
            {380.0f, 340.0f, 10.0f, false},     // Safe coin 3 (climb area)
            {530.0f, 400.0f, 10.0f, false},     // Safe coin 4 (mid-climb)
            {480.0f, 460.0f, 10.0f, false},     // Gauntlet coin (safe)
            {710.0f, 500.0f, 10.0f, false},     // Final platform coin
            {650.0f, 280.0f, 10.0f, false},     // Recovery platform coin
            {560.0f, 180.0f, 10.0f, false}      // Extra safe coin (gap area)
        },

        // Enemies (4 total): slower, tighter patrol zones
        {
            {280.0f, 230.0f, 40.0f, 40.0f, 2.0f, 1.0f, 260.0f, 380.0f},     // Slower, shorter patrol
            {520.0f, 280.0f, 40.0f, 40.0f, 2.2f, -1.0f, 460.0f, 600.0f},    // Mid-level patrol (slower)
            {380.0f, 340.0f, 40.0f, 40.0f, 2.0f, 1.0f, 360.0f, 480.0f},     // Climb section (slower, tighter)
            {650.0f, 200.0f, 40.0f, 40.0f, 2.3f, -1.0f, 600.0f, 720.0f}     // Reduced top speed
        }
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
    enemies = levels[levelIndex].levelEnemies;

    resetPlayer();

    // if no enemy, default position and direction for enemy
    if (!enemies.empty())
    {
        Enemy::x = enemies[0].x;
        Enemy::y = enemies[0].y;
        Enemy::direction = enemies[0].direction;
    }

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

void drawCenteredText(float centerX, float y, const string& text, void* font = GLUT_BITMAP_HELVETICA_18)
{
    float textWidth = static_cast<float>(glutBitmapLength(font, reinterpret_cast<const unsigned char*>(text.c_str())));
    drawText(centerX - textWidth * 0.5f, y, text, font);
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
            Music::playWin();
        }
        else
        {
            currentLevel += 1;
            loadLevel(currentLevel);
        }
    }
}









// --------------------------------
// Check if coin collected
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
// Check if coin collected
// --------------------------------












// ================================
// Update Function 
// ================================
void update(int value)
{
    Music::sync(showMenu);


    // ----------------------------
    // text pop-up
    // ----------------------------
    if (showMenu)
    {
        MenuUI::update(); // Update menu animation

        if (Input::consumeStartRequested())
        {
            showMenu = false;
            resetPlayer();
            loadLevel(1);
            currentLevel = 1;
            lives = 3;
            gameWon = false;
            gameOver = false;
        }

        glutPostRedisplay();
        glutTimerFunc(8, update, 0);
        return;
    }
    // ------------------------------
    // text pop-up
    // ------------------------------





    // ------------------------------
    // Frezze game if won or over
    // ------------------------------
    if (gameWon || gameOver)
    {
        glutPostRedisplay();          
        glutTimerFunc(8, update, 0);  // 120 FPS
        return;
    }
    // ------------------------------
    // Frezze game if won or over
    // ------------------------------




    // Save player Y before gravity for platform collision detection
    float previousPlayerY = playerY;




    // ------------------------------
    // Update coin rotation
    // ------------------------------
    coinRotationAngle += 3.0f;  // 3 degree per frame
    if (coinRotationAngle >= 360.0f)
    {
        coinRotationAngle -= 360.0f;  // Reset to prevent overflow
    }
    // ------------------------------
    // Update coin rotation
    // ------------------------------




    // ------------------------------
    // Update cloud 
    // ------------------------------
    for (Cloud& cloud : clouds)
    {
        cloud.x += cloud.speed;  // Move cloud right direction
        
        if (cloud.x > windowWidth + 50.0f)
        {
            cloud.x = -50.0f;
        }
    }
    // ------------------------------
    // Update cloud 
    // ------------------------------





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
        playerFacing = -1.0f;
    } 
    else if (Input::isRightPressed() && !Input::isLeftPressed()) 
    {
        playerX += playerMoveSpeed; // Move right
        playerFacing = 1.0f;
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
    // Update all enemies
    // ---------------------------------
    for (GameEnemy& enemy : enemies)
    {
        // Move enemy
        enemy.x += enemy.moveSpeed * enemy.direction;
        
        // Check patrol boundaries and reverse direction
        if (enemy.x <= enemy.minX || enemy.x >= enemy.maxX)
        {
            enemy.direction *= -1.0f;
        }
    }
    // ---------------------------------
    // Update all enemies
    // ---------------------------------

    





    // --------------------------------
    // Check if any enemy hits player
    // --------------------------------
    for (const GameEnemy& enemy : enemies)
    {
        if (Enemy::isOverlap(playerX, playerY, playerWidth, playerHeight, 
                            enemy.x, enemy.y, enemy.width, enemy.height))
        {
            Music::playEnemyHit();
            lives -= 1;

            if (lives <= 0)
            {
                gameOver = true;
            }
            else
            {
                resetCurrentLevel();
            }
            break;  // Only lose one life per frame
        }
    }
    // --------------------------------
    // Check if any enemy hits player
    // --------------------------------
    

    

    

    // --------------------------------
    // coin collection 
    // --------------------------------
    for (Coin& coin : coins)
    {
        if (!coin.collected && isCoinCollectedByPlayer(coin))
        {
            coin.collected = true;
            Music::playCoinCollect();
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





    if (showMenu)
    {
        MenuUI::draw((float)windowWidth, (float)windowHeight);

        glFlush();
        glutSwapBuffers();
        return;
    }






    // ---------------------------------
    // Background: sky gradient + clouds
    // Painter's algorithm
    // ---------------------------------
    glBegin(GL_QUADS);
        
        if(currentLevel == 1)
        {
            glColor3ub(skyDaytopR, skyDaytopG, skyDaytopB);
            glVertex2f(0.0f, (float)windowHeight);
            glVertex2f((float)windowWidth, (float)windowHeight);

            glColor3ub(skyDaybottomR, skyDaybottomG, skyDaybottomB);
            glVertex2f((float)windowWidth, 0.0f);
            glVertex2f(0.0f, 0.0f);
        }
        if(currentLevel == 2)
        {
            glColor3ub(skyNighttopR, skyNighttopG, skyNighttopB);
            glVertex2f(0.0f, (float)windowHeight);
            glVertex2f((float)windowWidth, (float)windowHeight);

            glColor3ub(skyNightbottomR, skyNightbottomG, skyNightbottomB);
            glVertex2f((float)windowWidth, 0.0f);
            glVertex2f(0.0f, 0.0f);
        }
        if(currentLevel == 3)
        {
            glColor3ub(skyEveningtopR, skyEveningtopG, skyEveningtopB);
            glVertex2f(0.0f, (float)windowHeight);
            glVertex2f((float)windowWidth, (float)windowHeight);

            glColor3ub(skyEveningbottomR, skyEveningbottomG, skyEveningbottomB);
            glVertex2f((float)windowWidth, 0.0f);
            glVertex2f(0.0f, 0.0f);
        }
    glEnd();




    
    // Celestial body layer for painter's algorithm
    if (currentLevel == 1)
    {
        drawSun(windowWidth * 0.20f, windowHeight * 0.78f, 62.0f, sunGlowR, sunGlowG, sunGlowB, sunMidR, sunMidG, sunMidB, sunCoreR, sunCoreG, sunCoreB);
    }
    if (currentLevel == 2)
    {
        drawMoon(windowWidth * 0.18f, windowHeight * 0.80f, 54.0f, moonCoreR, moonCoreG, moonCoreB, moonGlowR, moonGlowG, moonGlowB, true);
    }
    if (currentLevel == 3)
    {
        drawSun(windowWidth * 0.50f, windowHeight * 0.16f, 72.0f, sunsetGlowR, sunsetGlowG, sunsetGlowB, sunsetMidR, sunsetMidG, sunsetMidB, sunsetCoreR, sunsetCoreG, sunsetCoreB);
    }





    for (const Cloud& cloud : clouds)
    {
        if (currentLevel == 1)
        {
            drawCloud(cloud.x, cloud.y, cloud.radius, 255, 255, 255); // White clouds
        }
        if (currentLevel == 2)  
        {
            drawCloud(cloud.x, cloud.y, cloud.radius, 200, 200, 200); // Gray clouds for night
        }
        if (currentLevel == 3)  
        {
            drawCloud(cloud.x, cloud.y, cloud.radius, 255, 255, 255); // White clouds
        }
    }
    // -----------------------------------
    // Background: sky gradient + clouds
    // Painter's algorithm
    // -----------------------------------







    // ------------------------------
    // Ground rectangle with gradient
    // ------------------------------
    glBegin(GL_QUADS);

    if(currentLevel == 1)
    {
        // Top edge - grass green
        glColor3ub(daygrasstopR, daygrasstopG, daygrasstopB);
        glVertex2f(groundX, groundY + groundHeight);
        glVertex2f(groundX + groundWidth, groundY + groundHeight);
        
        // Bottom edge - darker soil
        glColor3ub(daygrassbottomR, daygrassbottomG, daygrassbottomB);
        glVertex2f(groundX + groundWidth, groundY);
        glVertex2f(groundX, groundY);
    }
    if(currentLevel == 2)
    {
        // Top edge - grass green
        glColor3ub(nightGrasstopR, nightGrasstopG, nightGrasstopB);
        glVertex2f(groundX, groundY + groundHeight);
        glVertex2f(groundX + groundWidth, groundY + groundHeight);
        
        // Bottom edge - darker soil
        glColor3ub(nightGrassbottomR, nightGrassbottomG, nightGrassbottomB);
        glVertex2f(groundX + groundWidth, groundY);
        glVertex2f(groundX, groundY);
    }
    if(currentLevel == 3)
    {
        // Top edge - grass green
        glColor3ub(eveningGrasstopR, eveningGrasstopG, eveningGrasstopB);
        glVertex2f(groundX, groundY + groundHeight);
        glVertex2f(groundX + groundWidth, groundY + groundHeight);
        
        // Bottom edge - darker soil
        glColor3ub(eveningGrassbottomR, eveningGrassbottomG, eveningGrassbottomB);
        glVertex2f(groundX + groundWidth, groundY);
        glVertex2f(groundX, groundY);
    }
    
    
    glEnd();
    // ------------------------------
    // Ground rectangle with gradient
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
    // Coins (with rotation)
    // -----------------------------------------
    for (const Coin& coin : coins)
    {
        if (!coin.collected)
        {
            //------------------------------
            //------------------------------
            // Matrix push
            //------------------------------
            //------------------------------
            glPushMatrix();

            glTranslatef(coin.x, coin.y, 0.0f);        // Move to coin position
            glRotatef(coinRotationAngle, 0.0f, 0.0f, 1.0f);  // Rotate around Z-axis
            
            // Pulsing [glScalef] 
            float pulseScale = 1.0f + 0.2f * sin(coinRotationAngle * 3.14159f / 180.0f);
            glScalef(pulseScale, pulseScale, 1.0f);
            
            circle_with_fan(0.0f, 0.0f, coin.radius, 255, 215, 0);  // Draw at origin
            
            // Strip
            glColor3ub(200, 150, 0);  
            glLineWidth(7.0f);        // Strip Thickness
            glBegin(GL_LINES);
            glVertex2f(-coin.radius, 0.0f);      // Left side
            glVertex2f(coin.radius, 0.0f);       // Right side
            glEnd();
            glLineWidth(1.0f);        // Reset line width
            
            glPopMatrix();
            //------------------------------
            //------------------------------
            // Matrix pop
            //------------------------------
            //------------------------------
        }
    }
    // -----------------------------------------
    // Coins (with rotation)
    // -----------------------------------------










    //------------------------------
    //------------------------------
    // Matrix push
    //------------------------------
    //------------------------------
    glPushMatrix();
    




    glTranslatef(playerX, playerY, 0.0f); // Move the player to its current position
    // ------------------------------
    // Player character
    // ------------------------------
    if (playerFacing < 0.0f)
    {
        glPushMatrix();
        glTranslatef(playerWidth, 0.0f, 0.0f);
        glScalef(-1.0f, 1.0f, 1.0f);
        drawPlayerSprite();

        if(Input::isJumpPressed())
        {
            rectangle_outline_with_width_height(
                playerWidth / 4.0f, playerHeight + 10.0f,
                playerWidth / 2.0f, 10.0f,
                255, 255, 0
            );
        }
        glPopMatrix();
    }
    else
    {
        drawPlayerSprite();

        if(Input::isJumpPressed())
        {
            rectangle_outline_with_width_height(
                playerWidth / 4.0f, playerHeight + 10.0f,
                playerWidth / 2.0f, 10.0f,
                255, 255, 0
            );
        }
    }
    // ------------------------------
    // Player character
    // ------------------------------


    glPopMatrix();
    //------------------------------
    //------------------------------
    // Matrix pop
    //------------------------------
    //------------------------------









    // ------------------------------
    // Draw all enemies
    // ------------------------------
    for (const GameEnemy& enemy : enemies)
    {
        Enemy::x = enemy.x;
        Enemy::y = enemy.y;
        Enemy::width = enemy.width;
        Enemy::height = enemy.height;
        Enemy::enemyDraw();
    }
    // ------------------------------
    // Draw all enemies
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
    glutSwapBuffers();
}
// ================================
// Display Function 
// ================================



















// ================================
// Initialization
// ================================
void init() 
{
    showMenu = true;
    currentLevel = 1;
    lives = 3;
    gameWon = false;
    gameOver = false;
    MenuUI::reset();
    loadLevel(currentLevel);
    Music::sync(showMenu);

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

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(windowWidth, windowHeight);

    glutInitWindowPosition(100, 100);

    glutCreateWindow("GLUT Window");

    init();
    atexit(Music::stop);

    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeyPress);
    glutKeyboardUpFunc(handleKeyRelease);
    glutTimerFunc(8, update, 0); // 120 FPS

    glutMainLoop();

    return 0;
}
// ================================
// Main Function
// ================================