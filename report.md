# PixelHop Game - Comprehensive Project Report

## Executive Summary

**PixelHop** is a 2D platformer game developed in C++ using legacy OpenGL (GLUT framework). The project demonstrates a complete game pipeline including graphics rendering, physics simulation, collision detection, audio management, and user input handling. The game features three progressive difficulty levels, Mario-inspired character design, collectible coins, and enemy encounters.

**Project Type:** 2D Platformer  
**Platform:** Cross-platform (macOS, Linux, Windows)  
**Language:** C++17  
**Graphics API:** OpenGL 2D (Legacy Immediate Mode)  
**Audio Backend:** OpenAL (cross-platform)  
**Resolution:** 800×600 pixels

---

## 1. Project Overview

### Game Objective

Players control a Mario-like character to navigate through three levels, collecting all coins while avoiding enemies. Successfully collecting all coins advances to the next level. Completing level 3 triggers a victory state with winning sound effects.

### Key Features

- **Three Progressive Levels:** Each with unique platform layouts, coin placements, and enemy configurations
- **Dynamic Graphics:** Gradient-based backgrounds, animated clouds, rotating coins
- **Character Animation:** Sprite-based character with facing direction (left/right) and mirrored rendering
- **Physics System:** Gravity-based movement with platform collision detection
- **Audio System:** Cross-platform looping background music, sound effects for coin collection, enemy hits, and level completion
- **Menu System:** Animated main menu with game instructions and pulsing UI elements
- **Enemy AI:** Patrol-based movement with boundary reversal
- **Level Progression:** Automatic level advancement on coin collection

---

## 2. Project Structure

### Directory Layout

```
PixelHop final/
├── main.cpp                 # Main game loop, rendering, game state
├── header.h                 # Common includes and platform detection
├── colors.h                 # Centralized color palette
├── color.md                 # Mario-style color reference documentation
├── shapes.h                 # OpenGL drawing primitives
├── menu.h                   # Menu UI and animations
├── music.h                  # Cross-platform audio system (OpenAL)
├── Enemy.h                  # Enemy entity, rendering, and collision
├── input/
│   └── Input.hpp           # Input state management and handling
├── physics/
│   ├── Physics.h           # Gravity and physics calculations
│   └── Collision.h         # Collision detection algorithms
├── include/                 # (Empty placeholder)
├── main                     # Compiled executable
└── [Audio Assets]
    ├── gameTrack.wav       # Background music (menu & gameplay)
    ├── coinSound.wav       # Coin collection SFX
    ├── faaah.wav           # Enemy hit SFX
    └── 7crore.wav          # Victory sound SFX
```

---

## 3. Technical Architecture

### 3.1 Graphics Pipeline

#### Technology Stack

- **Framework:** GLUT (OpenGL Utility Toolkit)
- **Rendering Mode:** Legacy OpenGL immediate mode (2D orthographic projection)
- **Coordinate System:** 2D with origin (0,0) at bottom-left corner
- **Color Model:** RGB (8-bit per channel: 0-255)

#### Rendering Stages (Painter's Algorithm)

1. **Background Layer:** Sky gradient (varying by level)
2. **Celestial Layer:** Sun or moon based on time of day
3. **Cloud Layer:** Animated cloud clusters
4. **Ground Layer:** Gradient-filled ground rectangle
5. **Platform Layer:** Brick-colored platforms with outlines
6. **Collectible Layer:** Rotating and pulsing coins
7. **Entity Layer:** Player character with facing direction
8. **Enemy Layer:** Enemy sprites with animation
9. **UI Layer:** Score, lives, level text display

#### Coordinate System

```
(0, 600) -------- (800, 600)    [Top-Left to Top-Right]
   |                 |
   |  Game World     |
   |  (2D Orthographic)
   |                 |
(0, 0) -------- (800, 0)      [Bottom-Left to Bottom-Right]
```

### 3.2 Physics System

#### Gravity Model

- **Type:** Constant acceleration downward
- **Gravity Force:** 0.5 units/frame²
- **Velocity Integration:** Explicit Euler integration
- **Terminal Velocity:** Theoretically unbounded (no air resistance)

#### Movement System

- **Horizontal Movement:** Discrete input-based (5.0 units/frame)
- **Jump Force:** 12.2 units/frame (initial velocity)
- **Grounded State:** Tracked through collision detection

### 3.3 Collision Detection

#### Types Implemented

1. **Ground Collision:** Player vs. floor boundary
2. **Platform Collision:** Player vs. solid platforms (one-way landing)
3. **Enemy Collision:** Player vs. enemy AABB (Axis-Aligned Bounding Box)
4. **Coin Collection:** Player AABB vs. coin circle (distance-based)

#### Algorithm Details

- **AABB Intersection Test:** Used for platform and enemy collisions
- **Circular Distance Test:** Used for coin proximity detection
- **One-Way Platforms:** Landing check only when falling (playerVelocityY < 0)
- **Horizontal Boundary Check:** Prevents player from leaving screen

### 3.4 Audio System (OpenAL Backend)

#### Cross-Platform Support

- **macOS:** Frameworks `-framework OpenAL`
- **Linux:** Link library `-lopenal`
- **Windows:** Link library `OpenAL32.lib`

#### Features

- **Looped Background Music:** Sync between menu and gameplay tracks
- **One-Shot Sound Effects:** Non-blocking concurrent SFX playback
- **Buffer Caching:** Loads audio files once, reuses across playback instances
- **Path Resolution:** Searches working directory and executable directory
- **Format Support:** PCM WAV files (mono/stereo, 8/16-bit)
- **Error Handling:** Format detection (rejects MP3-in-WAV), missing file warnings

#### Audio Paths

- **Menu/Gameplay Track:** `gameTrack.wav` (75% volume, looped)
- **Coin Collect SFX:** `coinSound.wav` (90% volume, one-shot)
- **Enemy Hit SFX:** `faaah.wav` (90% volume, one-shot)
- **Win SFX:** `7crore.wav` (90% volume, one-shot)

#### State Machine

```
Uninitialized → Initialize OpenAL → Ready
     ↓
   Loop:
   - Sync track (menu vs. gameplay)
   - Clean up finished SFX sources
   - Play one-shot SFX on events
     ↓
   Shutdown → Cleanup resources
```

---

## 4. Core Components

### 4.1 Main Game Loop (`main.cpp`)

#### Initialization Phase

```cpp
void init() {
  - Set initial game state (menu mode, level 1, 3 lives)
  - Load level data
  - Initialize OpenGL projection (800×600 orthographic)
  - Configure menu UI
  - Start audio system
}
```

#### Update Phase (120 FPS)

```cpp
void update(int value) {
  1. Sync audio (Music::sync)
  2. Handle menu transitions
  3. Update game state:
     - Apply gravity to player
     - Process input (left/right/jump)
     - Update platform collisions
     - Update enemies
     - Check coin collection
     - Check enemy collision with player
     - Update level progression
  4. Update animations (coin rotation, cloud movement)
  5. Schedule next frame (glutTimerFunc)
}
```

#### Display Phase

```cpp
void display() {
  1. Clear framebuffer
  2. Render background (gradient + celestial body)
  3. Render clouds
  4. Render ground
  5. Render platforms
  6. Render coins (with rotation/pulsing)
  7. Render player (with facing direction and mirror)
  8. Render enemies
  9. Render UI text (score, lives, level, win/lose)
  10. Flush and swap buffers
}
```

#### Game State Variables

```cpp
// Player
float playerX, playerY;           // Position
float playerWidth = 40, playerHeight = 60;
float playerMoveSpeed = 5.0f;
float playerVelocityY;            // Vertical velocity (gravity)
float playerFacing = 1.0f;        // 1.0 = right, -1.0 = left
bool playerGrounded;

// Game
int score = 0;
int lives = 3;
int currentLevel = 1;
int totalLevels = 3;
int winningScore;                 // = coins.size() per level
bool gameWon = false;
bool gameOver = false;
bool showMenu = true;

// Collections
vector<Platform> platforms;
vector<Coin> coins;
vector<GameEnemy> enemies;
vector<Cloud> clouds;
```

### 4.2 Rendering System (`shapes.h`)

#### Primitive Drawing Functions

**Rectangles:**

```cpp
void rectangle_with_width_height(x, y, width, height, r, g, b)
void rectangle_with_4_vertices(x1, y1, x2, y2, x3, y3, x4, y4, r, g, b)
void rectangle_outline_with_width_height(x, y, width, height, r, g, b)
```

**Squares:**

```cpp
void square_with_4_vertices(...)
void square_with_center_size(centerX, centerY, size, r, g, b)
void square_outline_with_center_size(...)
```

**Triangles:**

```cpp
void triangle_with_3_vertices(x1, y1, x2, y2, x3, y3, r, g, b)
void triangle_with_center_size(centerX, centerY, size, r, g, b)
void triangle_outline_with_3_vertices(...)
```

**Circles:**

```cpp
void circle_with_fan(centerX, centerY, radius, r, g, b)
void circle_outline_with_fan(centerX, centerY, radius, r, g, b)
```

#### Drawing Technique Notes

- **Polygon Orientation:** Counter-clockwise (CCW) for proper face culling
- **Rendering Method:** GL_POLYGON, GL_LINE_LOOP, GL_TRIANGLE_FAN
- **Color Specification:** `glColor3ub()` for 8-bit RGB values

### 4.3 Color Palette System (`colors.h`)

#### Color Organization

**Sky Colors (3 Levels):**

- **Day:** RGB(0, 155, 217) - Bright blue
- **Night:** RGB(0, 0, 0) - Black with gradient adjustments
- **Evening:** RGB(100, 50, 100) - Sunset purple tones

**Player (Mario-inspired):**

- Red Cap/Shirt: RGB(254, 0, 2)
- Blue Overalls: RGB(36, 78, 186)
- Skin: RGB(252, 212, 170)
- Brown Shoes: RGB(94, 55, 28)
- Black Outlines: RGB(18, 18, 18)
- White Details: RGB(255, 255, 255)

**Celestial Bodies:**

- **Sun:** Core (255, 218, 72), Mid (255, 195, 65), Glow (255, 160, 40)
- **Moon:** Core (235, 235, 245), Glow (180, 190, 210)
- **Sunset Sun:** Core (255, 140, 50), Mid (255, 165, 70), Glow (255, 80, 35)

**Environment:**

- Brick: RGB(185, 39, 22) - Red-brown
- Grass (Day): RGB(68, 175, 53) - Green
- Ground Gradient: Darker shades for depth

**Enemy Monster:**

- Body: RGB(92, 18, 26) - Dark red
- Eyes: RGB(255, 56, 32) - Orange-red
- Horns: RGB(255, 195, 70) - Yellow

#### Color Usage Pattern

```cpp
// Colors stored as individual RGB unsigned char variables
unsigned char skyDayR = 0, skyDayG = 155, skyDayB = 217;
unsigned char marioRedR = 254, marioRedG = 0, marioRedB = 2;

// Used in drawing
glColor3ub(marioRedR, marioRedG, marioRedB);
rectangle_with_width_height(x, y, w, h, marioRedR, marioRedG, marioRedB);
```

### 4.4 Player Character System

#### Sprite Composition

The player is drawn as a detailed Mario-like sprite using layered geometric primitives:

**Head Section (y=6-25):**

- Two brown rectangles (shoes)
- White circles with pupils (eyes)
- Black details (mustache, eyebrows)
- Yellow skin tone face

**Body Section (y=25-45):**

- Red overalls (main torso)
- Blue shirt (under overalls)
- Yellow buttons (overalls detail)
- Brown arms

**Lower Section (y=45-55):**

- Red pants with details
- Yellow shoe accents
- White eye highlight with black pupil

#### Facing Direction Implementation

```cpp
// Store facing direction
float playerFacing = 1.0f;  // 1.0 = right, -1.0 = left

// Update on input
if (Input::isLeftPressed()) playerFacing = -1.0f;
if (Input::isRightPressed()) playerFacing = 1.0f;

// Render with mirroring
if (playerFacing < 0.0f) {
  glPushMatrix();
  glTranslatef(playerWidth, 0, 0);  // Move to right edge
  glScalef(-1.0f, 1.0f, 1.0f);      // Mirror horizontally
  drawPlayerSprite();
  glPopMatrix();
} else {
  drawPlayerSprite();
}
```

#### Bounding Box vs. Visual Representation

- **Hitbox:** 40×60 pixels (rectangular for collision detection)
- **Visual:** 36 pixel width × 48 pixel height detailed sprite (centered within hitbox)

### 4.5 Menu System (`menu.h`)

#### Menu Structure

- **Title:** "PIXELHOP" (animated with pulse scale)
- **Subtitle:** "Jump, collect, and clear every level"
- **Start Prompt:** "Press Enter to Start" (pulsing animation)
- **Control Panel:** A/D to move, Space to jump
- **Objective Panel:** "Collect all coins"
- **Info:** "3 Levels to Conquer"
- **Background:** Gradient from dark blue to light blue

#### Animations

```cpp
// Pulsing effect using sine wave
float pulseScale = 1.0f + 0.14f * sin(animationAngle * PI / 180.0f);
glScalef(pulseScale, pulseScale, 1.0f);

// Update each frame
animationAngle += 2.5f;  // Rotate animation angle
```

#### Menu State Machine

```
Initial State → Menu displayed (showMenu = true)
     ↓
User presses Enter → Consume start request
     ↓
Load level 1 → showMenu = false
     ↓
Game loop runs
     ↓
User wins or loses → Display overlay on game screen
```

### 4.6 Enemy System (`Enemy.h`)

#### Enemy Attributes

```cpp
struct GameEnemy {
  float x, y;              // Position
  float width = 40, height = 40;
  float moveSpeed;         // Units per frame
  float direction;         // 1.0 = right, -1.0 = left
  float minX, maxX;        // Patrol boundaries
};
```

#### Enemy Rendering

Enemies are drawn as detailed monster sprites with:

- **Body:** Dark red rectangle (92, 18, 26)
- **Head:** Darker shadow color (45, 6, 10)
- **Eyes:** Orange-red circles (255, 56, 32) with black pupils
- **Mouth:** Small dark rectangle for smile
- **Horns:** Yellow triangles on top of head
- **Legs:** Claw-colored rectangles at base

#### AI Behavior

```cpp
// Simple patrol pattern
void update() {
  x += moveSpeed * direction;

  if (x <= minX) {
    x = minX;
    direction = 1.0f;  // Reverse to right
  } else if (x + width >= maxX) {
    x = maxX - width;
    direction = -1.0f;  // Reverse to left
  }
}

// Collision check (AABB)
bool isOverlap(playerX, playerY, playerW, playerH,
               enemyX, enemyY, enemyW, enemyH) {
  // Standard AABB intersection test
}
```

#### Level Enemy Configuration

- **Level 1:** 4 enemies with varied speeds (1.5-2.0 units/frame)
- **Level 2:** 3 enemies with varied speeds (1.6-2.2 units/frame)
- **Level 3:** 4 enemies, slower and with tighter patrol zones (2.0-2.3 units/frame)

### 4.7 Input System (`input/Input.hpp`)

#### Input State Management

```cpp
namespace Input {
  // State flags (persistent)
  static bool& leftState()      { static bool v = false; return v; }
  static bool& rightState()     { static bool v = false; return v; }
  static bool& jumpState()      { static bool v = false; return v; }
  static bool& jumpRequestedState()    { static bool v = false; return v; }
  static bool& startRequestedState()   { static bool v = false; return v; }
}
```

#### Key Mappings

| Key        | Action                      |
| ---------- | --------------------------- |
| A / a      | Move left                   |
| D / d      | Move right                  |
| Space      | Jump                        |
| Enter (13) | Start game from menu        |
| ESC (27)   | Quit (via main.cpp handler) |

#### State Management Pattern

- **Continuous State:** `leftState()`, `rightState()`, `jumpState()` persist each frame
- **One-Shot Events:** `jumpRequestedState()`, `startRequestedState()` consumed with getter

#### Input Querying Functions

```cpp
bool isLeftPressed()           // Query current state
bool isRightPressed()          // Query current state
bool isJumpPressed()           // Query current state
bool consumeJumpRequested()    // Get and clear
bool consumeStartRequested()   // Get and clear

void keyPress(key, x, y)       // GLUT callback
void keyRelease(key, x, y)     // GLUT callback
void setKeyState(key, pressed) // Internal dispatcher
```

### 4.8 Physics System (`physics/Physics.h`)

#### Gravity Application

```cpp
namespace Physics {
  void applyGravity(float& positionY, float& velocityY,
                    float gravityForce = 0.5f) {
    velocityY -= gravityForce;     // Gravity pulls down
    positionY += velocityY;         // Apply velocity
  }
}
```

#### Physics Parameters

- **Default Gravity:** 0.5 units/frame²
- **Jump Force:** 12.2 units/frame (upward initial velocity)
- **Horizontal Speed:** 5.0 units/frame
- **Terminal Velocity:** Theoretically unlimited (no air resistance implemented)

#### Numerical Integration

- **Method:** Explicit Euler integration
- **Order:** Gravity first, then velocity applied to position
- **Stability:** Works for this game scale; linear velocity integration sufficient

### 4.9 Collision Detection (`physics/Collision.h`)

#### Ground Collision

```cpp
bool groundCollision(float& playerY, float& playerVelocityY,
                     float groundTop) {
  if (playerY <= groundTop && playerVelocityY < 0.0f) {
    playerY = groundTop;
    playerVelocityY = 0.0f;
    return true;  // Landing occurred
  }
  return false;
}
```

#### Platform Collision (One-Way)

```cpp
bool platformCollision(
    float previousPlayerY,        // Y before gravity
    float playerX, float& playerY, // Updated by gravity
    float playerWidth, float& playerVelocityY,
    float platformX, float platformY,
    float platformWidth, float platformHeight) {

  // Check horizontal overlap
  bool horiz = (playerRight > platformLeft) && (playerLeft < platformRight);

  // Check vertical crossing (falling onto platform from above)
  float platformTop = platformY + platformHeight;
  bool crossed = (previousPlayerY >= platformTop) &&
                 (playerY <= platformTop);

  if (horiz && crossed && playerVelocityY <= 0.0f) {
    playerY = platformTop;
    playerVelocityY = 0.0f;
    return true;
  }
  return false;
}
```

#### Enemy Collision (AABB)

```cpp
bool isOverlap(float leftA, float bottomA, float widthA, float heightA,
               float leftB, float bottomB, float widthB, float heightB) {
  float rightA = leftA + widthA;
  float topA = bottomA + heightA;
  float rightB = leftB + widthB;
  float topB = bottomB + heightB;

  return (leftA < rightB) && (rightA > leftB) &&
         (bottomA < topB) && (topA > bottomB);
}
```

#### Coin Collection (Circular Distance)

```cpp
bool isCoinCollectedByPlayer(const Coin& coin) {
  float nearestX = max(playerX, min(coin.x, playerX + playerWidth));
  float nearestY = max(playerY, min(coin.y, playerY + playerHeight));

  float deltaX = coin.x - nearestX;
  float deltaY = coin.y - nearestY;

  return (deltaX * deltaX + deltaY * deltaY) <=
         (coin.radius * coin.radius);
}
```

### 4.10 Audio System (`music.h`)

#### OpenAL Integration Architecture

```
High-Level API (Music namespace)
├── start(path)         → Load and play looped music
├── stop()             → Shutdown and cleanup
├── sync(inMenu)       → Manage track switching
├── playCoinCollect()  → One-shot SFX
├── playEnemyHit()     → One-shot SFX
└── playWin()          → One-shot SFX (Victory)

Low-Level (OpenAL API)
├── ensureInitialized()           → Device/Context setup
├── loadWavFile()                 → Parse PCM WAV
├── loadBufferForPath()           → Buffer caching
├── playDetached()                → One-shot playback
└── cleanupFinishedSfx()          → Resource cleanup
```

#### WAV File Loading Pipeline

```cpp
bool loadWavFile(path, pcmData, format, sampleRate) {
  1. Detect MP3-in-WAV mismatch (ID3 header check)
  2. Validate RIFF header
  3. Parse fmt chunk (format, channels, bits)
  4. Parse data chunk (raw PCM bytes)
  5. Determine OpenAL format:
     - 1ch 8bit  → AL_FORMAT_MONO8
     - 1ch 16bit → AL_FORMAT_MONO16
     - 2ch 8bit  → AL_FORMAT_STEREO8
     - 2ch 16bit → AL_FORMAT_STEREO16
  6. Return format and buffer data
}
```

#### Buffer Caching Strategy

```cpp
static map<string, ALuint> bufferCache;

ALuint loadBufferForPath(string path) {
  // Check cache first
  if (cached) return cachedBuffer;

  // Load and parse WAV
  // Create OpenAL buffer
  // Cache and return

  // Benefit: Coin sound plays multiple times from same buffer
}
```

#### One-Shot SFX Management

```cpp
static vector<ALuint> activeSfxSources;

void cleanupFinishedSfx() {
  // Each frame, check SFX source states
  for each source {
    if (state == AL_STOPPED) {
      delete source;
      remove from vector;
    }
  }
}
```

#### Cross-Platform Path Resolution

```cpp
string executableDirectory() {
  #ifdef _WIN32
    Get from GetModuleFileNameA()
  #elif defined(__APPLE__)
    Get from _NSGetExecutablePath()
  #else
    Get from readlink("/proc/self/exe")
  #endif
}

string resolveTrackPath(path) {
  if (exists in working directory) return path;
  if (exists in executable directory) return exe_dir + path;
  return original path (fallback);
}
```

---

## 5. Level Design

### Level Data Structure

```cpp
struct LevelData {
  vector<Platform> platforms;
  vector<Coin> coins;
  vector<GameEnemy> levelEnemies;
};

vector<LevelData> levels = [3 levels defined];
```

### Level 1: Introduction

- **Difficulty:** Easy
- **Platforms:** 7 platforms with generous spacing
- **Coins:** 9 coins distributed evenly
- **Enemies:** 4 enemies with comfortable patrol ranges
- **Theme:** Day time with bright blue sky
- **Purpose:** Tutorial level to learn mechanics

### Level 2: Intermediate

- **Difficulty:** Medium
- **Platforms:** 8 platforms with increased complexity
- **Coins:** 10 coins with some challenging positions
- **Enemies:** 3 enemies with faster movement (2.2 units/frame max)
- **Theme:** Night time with moon and darker colors
- **Purpose:** Introduce tighter platforming and faster enemies

### Level 3: Challenge

- **Difficulty:** Hard
- **Platforms:** 9 platforms with varied heights and spacing
- **Coins:** 10 coins with strategic positioning
- **Enemies:** 4 enemies with slow but steady patrol
- **Theme:** Evening/sunset with warm color palette
- **Purpose:** Final test of player skill; completion triggers victory

#### Winning Condition

- **Per Level:** Collect all coins (score >= coins.size())
- **Automatic Advancement:** Except on Level 3 (triggers gameWon state)
- **Win Screen:** "YOU WON ALL 3 LEVELS! Great run. Final level cleared."

---

## 6. Game Mechanics

### 6.1 Scoring System

```cpp
int winningScore = coins.size();  // Per level
int score = 0;

// On coin collection
coin.collected = true;
score += 1;
Music::playCoinCollect();
updateGameStateAfterScoreChange();
```

### 6.2 Lives System

```cpp
int lives = 3;  // Starting lives

// On enemy collision
lives -= 1;
Music::playEnemyHit();

if (lives <= 0) {
  gameOver = true;
}
```

### 6.3 Level Progression

```cpp
void updateGameStateAfterScoreChange() {
  if (score >= winningScore) {
    if (currentLevel >= totalLevels) {
      gameWon = true;
      Music::playWin();  // Victory sound
    } else {
      currentLevel += 1;
      loadLevel(currentLevel);
    }
  }
}
```

### 6.4 Game States

```
MENU (showMenu=true)
  ↓ User presses Enter
GAMEPLAY Level 1 (currentLevel=1, showMenu=false)
  ↓ Collect all coins
GAMEPLAY Level 2 (currentLevel=2)
  ↓ Collect all coins
GAMEPLAY Level 3 (currentLevel=3)
  ↓ Collect all coins
VICTORY (gameWon=true)
  ↓ Display "YOU WON" message
```

### 6.5 Failure Conditions

- **Lose All Lives:** gameOver = true (frozen state, display "GAME OVER")
- **Fall Off Screen:** Player Y < 0 (treated as ground collision fails)

---

## 6.6 Game Mechanics Deep Dive: Detailed Working Mechanisms

### Per-Frame Game Loop Execution

Every frame (at 120 FPS = 8ms intervals), the game follows a precise execution order that determines the entire gameplay experience:

#### Step 1: Audio Synchronization

When `update()` begins, `Music::sync(showMenu)` is called immediately. This checks whether the player is currently on the menu or in gameplay. If the game state changed (e.g., user pressed Enter to start), the audio system switches from menu music to gameplay music. The sync function also cleans up finished one-shot SFX sources, removing sources that have finished playing to prevent memory leaks.

#### Step 2: Menu State Handling

If `showMenu = true`, the game enters menu mode:

- The `MenuUI::update()` function increments `animationAngle` by 2.5° per frame
- This angle drives the pulsing animations visible on the title and "Press Enter to Start" text
- The sine wave function creates a breathing effect: text scales between 0.86x and 1.14x normal size
- Input is checked via `Input::consumeStartRequested()` - if the player pressed Enter, this returns true (and clears the flag)
- When start is confirmed, the function calls `resetPlayer()`, `loadLevel(1)`, sets `showMenu = false`, and resets game state
- The function returns early, skipping all gameplay logic for that frame
- This means menu and gameplay never execute in the same frame

#### Step 3: Win/Loss State Check

If either `gameWon = true` or `gameOver = true`, the game freezes:

- The player can no longer move or perform actions
- The display function renders the current frame with an overlay message ("YOU WON ALL 3 LEVELS!" or "GAME OVER")
- The update function does NOT process physics, input, or collisions
- This frozen state persists until the user manually closes the game

#### Step 4: Physics Application

Gravity is applied to the player: `playerVelocityY -= 0.5f` (reduces velocity by 0.5 units, pulling downward). Then the position is updated: `playerY += playerVelocityY`. This means:

- If player is falling (velocityY = -5), they move down 5 units AND lose 0.5 velocity (accelerating)
- If player is at peak of jump (velocityY = 0), they immediately start moving down by 0.5 units
- Terminal velocity is theoretically infinite because there's no air resistance; in practice, physics becomes unrealistic at very high speeds

**Critical detail:** Before gravity is applied, `float previousPlayerY = playerY` is saved. This is essential for platform collision detection later.

#### Step 5: Input Processing

The game queries input state:

- `Input::isLeftPressed()` and `Input::isRightPressed()` are checked
- If only left is pressed: `playerX -= 5.0f` and `playerFacing = -1.0f`
- If only right is pressed: `playerX += 5.0f` and `playerFacing = 1.0f`
- If both are pressed simultaneously, neither movement occurs (movement cancels)
- The `playerFacing` variable determines how the sprite is rendered (normal or horizontally flipped)

After movement, boundary checking prevents the player from leaving the screen: if `playerX < 0`, it's set to 0. If `playerX + playerWidth > 800`, it's set to `800 - playerWidth`.

#### Step 6: Jump Request Processing

`Input::consumeJumpRequested()` is called. This returns true only once per jump press (the flag is cleared after consumption). When true AND `playerGrounded = true`:

- `playerVelocityY = 12.2f` (gives initial upward velocity)
- `playerGrounded = false` (player leaves ground immediately)

This means a jump press is buffered - if you press space while airborne, nothing happens. But the next frame you land on ground, pressing space gives no delay.

#### Step 7: Collision Detection - Ground

`Collision::groundCollision()` checks if the player reached ground level. The ground is always at Y = 80 (the top surface of the ground rectangle). If `playerY <= 80 AND playerVelocityY < 0`:

- Player position is clamped to exactly 80
- Velocity becomes 0 (stops downward motion)
- Function returns true
- `landedThisFrame = true`

#### Step 8: Collision Detection - Platforms

For each platform, `Collision::platformCollision()` is called with previous and current player Y:

- Check if player's X range overlaps platform's X range
- Check if player crossed platform top: `previousPlayerY >= platformTop AND playerY <= platformTop`
- Both conditions must be true
- If true, player Y is set to platform top, velocity becomes 0, function returns true
- This is how one-way platforms work - you can't jump through from below

After all platforms are checked, if any collision occurred, `landedThisFrame = true`.

#### Step 9: Grounded State Update

At the end of collision checking, `playerGrounded = landedThisFrame` is set. This means:

- If player landed this frame (ground or platform), next frame can jump
- If player didn't land, even if not moving, can't jump (prevents mid-air double jumps)

#### Step 10: Enemy AI Updates

For each enemy in the level:

- `enemy.x += enemy.moveSpeed * enemy.direction` (move in current direction)
- If `enemy.x <= enemy.minX` (hit left boundary):
  - Position is clamped to minX
  - `direction = 1.0f` (reverse to right)
- If `enemy.x + enemy.width >= enemy.maxX` (hit right boundary):
  - Position is clamped to `maxX - width`
  - `direction = -1.0f` (reverse to left)

Enemies simply bounce between boundaries at constant speed. They don't respond to player presence or obstacles.

#### Step 11: Enemy Collision with Player

For each enemy, `Enemy::isOverlap()` is called with player and enemy AABB (Axis-Aligned Bounding Box):

```
Player hitbox: (playerX, playerY) to (playerX + 40, playerY + 60)
Enemy hitbox: (enemy.x, enemy.y) to (enemy.x + 40, enemy.y + 40)
```

If rectangles overlap:

- `Music::playEnemyHit()` is called (one-shot SFX)
- `lives -= 1`
- If `lives <= 0`, `gameOver = true` (game ends)
- Otherwise, `resetCurrentLevel()` is called (resets player position and reload level without changing level number)
- Break statement exits loop (only one hit per frame)

#### Step 12: Coin Collection

For each coin in the level:

- Skip if already collected
- Call `isCoinCollectedByPlayer()` which uses circle-to-AABB distance:
  - Find nearest point on player rectangle to coin center
  - Calculate distance from that point to coin center
  - If distance ≤ coin.radius (10 units), coin collected
- When collected:
  - `coin.collected = true` (visual effect: coin disappears)
  - `Music::playCoinCollect()` plays SFX
  - `score += 1`
- After all coins checked, call `updateGameStateAfterScoreChange()`

#### Step 13: Level Progression

`updateGameStateAfterScoreChange()` logic:

- Check if `score >= winningScore` (winningScore = number of coins in level)
- If true, check if `currentLevel >= totalLevels` (totalLevels = 3)
  - If yes: `gameWon = true` AND `Music::playWin()` (victory SFX)
  - If no: `currentLevel += 1` and `loadLevel(currentLevel)` (load next level, reset coin/enemy positions, reset player, reset score to 0)

#### Step 14: Animation Updates

- `coinRotationAngle += 3.0f` per frame (makes coins spin)
- When angle reaches 360, it resets to 0 (prevent overflow)
- For each cloud: `cloud.x += cloud.speed`
- When cloud exits right edge (`cloud.x > 800 + 50`), it wraps to left (`cloud.x = -50`)

#### Step 15: Frame Scheduling

Finally, `glutTimerFunc(8, update, 0)` schedules the next update after 8ms (120 FPS).

### How Levels Work

Each level has three components: platforms, coins, and enemies. When a level loads via `loadLevel(int levelNumber)`:

1. Vectors are cleared and refilled with that level's data from the `levels` array
2. Player is reset to start position (120, 100) with zero velocity
3. First enemy's position is synced to `Enemy::x` and `Enemy::y` global variables
4. Score is reset to 0
5. `winningScore` is set to `coins.size()` (number of coins in this level)

### How Lives and Death Work

When an enemy hits the player:

- If this is NOT the last life (lives > 1):
  - Level resets via `resetCurrentLevel()` which calls `loadLevel(currentLevel)`
  - This respawns all coins (uncollected), resets all enemies to start positions, respawns player
  - Score remains 0 (level resets, but overall progress to next level resets)
  - Player can continue from this level
- If this IS the last life (lives == 1):
  - After `lives -= 1`, lives becomes 0
  - `gameOver = true` set immediately
  - Game display freezes with "GAME OVER" message
  - Game becomes unresponsive except for ESC to quit

### How Rendering Works

The display function renders in strict order (Painter's Algorithm):

1. **Clear:** Entire framebuffer is black
2. **Background Gradient:** A quad fills the screen from bottom (light color) to top (dark color)
   - Level 1: Light blue to darker blue
   - Level 2: Very dark (night) to slightly lighter dark
   - Level 3: Purple to orange (sunset)
3. **Celestial Body:** Depending on level:
   - Level 1: Large sun (3 concentric circles with colors) at 20% width, 78% height
   - Level 2: Moon with crater details at 18% width, 80% height
   - Level 3: Sunset sun with warm colors at 50% width, 16% height
4. **Clouds:** 4 clouds drawn as 3-puff clusters
   - Each puff is a circle, offset and scaled slightly differently
   - Creates a cumulus cloud appearance
5. **Ground:** Gradient rectangle from Y=0 to Y=80
   - Top edge: Light grass color
   - Bottom edge: Darker soil color
6. **Platforms:** Each platform rendered as a red-brown rectangle with black outline
7. **Coins:** For each non-collected coin:
   - Push matrix
   - Translate to coin position
   - Rotate by current animation angle
   - Scale by pulse animation (0.8x to 1.2x)
   - Draw filled gold circle with dark stripe
   - Pop matrix
8. **Player:**
   - Push matrix
   - Translate to player position
   - If facing left: translate to right edge, scale X by -1 (mirror)
   - Draw all sprite components (60+ individual rectangles and circles)
   - If jump is held: Draw yellow outline above player (visual feedback)
   - Pop matrix
9. **Enemies:** For each enemy:
   - Sync global Enemy namespace variables with current enemy data
   - Call `Enemy::enemyDraw()` which renders all body parts
10. **UI Text:**
    - Top-left: "Score: {score}" in white
    - Below: "Lives: {lives}" in white
    - Below: "Level: {currentLevel}/3" in white
11. **Win/Loss Overlay:**
    - If gameWon: Yellow text saying "YOU WON ALL 3 LEVELS!" and "Great run. Final level cleared."
    - If gameOver: Red text saying "GAME OVER" and "You lost all your lives."

### How Audio Works During Gameplay

Audio state is managed via `Music::sync(showMenu)` called every frame:

1. **Initial Call:** `ensureInitialized()` sets up OpenAL device and context on first call (thread-safe one-time setup)

2. **Track Selection:**
   - If `inMenu = true`, desired track is `menuTrackPath` (gameTrack.wav)
   - If `inMenu = false`, desired track is `gameplayTrackPath` (same file)
   - In this implementation, both use the same file, so switching doesn't actually change the audio
   - In a more complete game, these could be different tracks

3. **Track Switching Logic:**
   - If desired track differs from currently playing track:
     - Load buffer via `loadBufferForPath()` (searches cache first, then loads from disk)
     - Create new source
     - Bind buffer to source
     - Set loop flag to AL_TRUE (music repeats)
     - Set volume to 0.75f
     - Start playback
   - If same track is already playing, do nothing
   - If same track but playback stopped, resume playback

4. **SFX Cleanup:**
   - `cleanupFinishedSfx()` iterates through all active SFX sources
   - Queries each source's state
   - If state == AL_STOPPED, source is deleted and removed from vector
   - This prevents memory leaks from accumulating finished sounds

5. **One-Shot SFX Playback:**
   - When `Music::playCoinCollect()` is called:
     - `playDetached(coinCollectPath)` is invoked
     - Loads coinSound.wav buffer (or retrieves from cache)
     - Creates new independent source
     - Sets volume to 0.90f (higher than music)
     - Starts playback
     - Adds to `activeSfxSources` vector
     - This source will play once and stop; next frame it will be cleaned up
   - Multiple SFX can play simultaneously since each has its own source

### Critical Timing and Frame Precision

The 8ms per-frame timing is critical:

- **Physics Stability:** Gravity is applied per-frame. At 120 FPS with 0.5 units/frame² gravity:
  - Frame 1: v = 0, then v -= 0.5 → v = -0.5, y += -0.5 → y = -0.5
  - Frame 2: v = -0.5, then v -= 0.5 → v = -1.0, y += -1.0 → y = -1.5
  - Total fall after 2 frames: 1.5 units
  - This progression creates smooth looking gravity

- **Collision Order:** Order matters because:
  - If collisions were checked before gravity, player would be stuck mid-air
  - If enemy collision happened before coin collection, coin sound wouldn't play if player dies
  - Current order ensures smooth gameplay

- **Input Responsiveness:** Jump requires both:
  - Space key pressed this frame
  - Player grounded from previous frame's collision check
  - This creates a 1-frame buffer that makes jumping feel responsive

### Level Difficulty Progression

**Level 1 → Level 2 → Level 3** increases difficulty via:

- **Platform Spacing:** Level 1 has forgiving gaps; Level 3 has tight platforming
- **Coin Positions:** Level 1 coins are safe; Level 3 coins are on dangerous platforms
- **Enemy Speeds:** Level 1 enemies move slowly (1.5-2.0); Level 3 enemies move at 2.0-2.3 units/frame
- **Enemy Patrol Zones:** Level 1 has wide zones; Level 3 zones are compact, creating dangerous traffic
- **Number of Coins:** Same count (9-10) but distribution changes
- **Visual Distraction:** Darker colors and sunset theme make Level 3 harder to see platforms

---

## 7. File-by-File Detailed Breakdown

### 7.1 main.cpp

**Lines:** ~1500  
**Responsibilities:**

- Game loop initialization and execution
- Global state management (player, level, game status)
- Input handling callbacks
- Rendering all game elements
- Update physics and collisions
- Audio synchronization
- Level loading and progression

**Key Functions:**

- `void init()` - Initialize OpenGL and game state
- `void update(int)` - Update game 120 times/sec
- `void display()` - Render current frame
- `void handleKeyPress()`, `handleKeyRelease()` - Input callbacks
- `void drawPlayerSprite()` - Render character
- `void drawCloud()`, `drawMoon()`, `drawSun()` - Environment rendering
- `void loadLevel(int)` - Load level data by number
- `void resetPlayer()`, `resetCurrentLevel()` - Reset functions
- `void updateGameStateAfterScoreChange()` - Progression logic

### 7.2 header.h

**Lines:** ~50  
**Responsibilities:**

- Suppress deprecation warnings (`GL_SILENCE_DEPRECATION`)
- Include standard library headers
- Platform-specific OpenGL includes (macOS vs Linux/Windows)
- Define PI constant (3.1416)

**Includes:**

- Standard: iostream, vector, string, algorithm, cmath, etc.
- Graphics: OpenGL/gl.h, GLUT/glut.h (platform-specific)

### 7.3 colors.h

**Lines:** ~150  
**Responsibilities:**

- Define all RGB color constants used throughout project
- Organize colors by semantic meaning (sky, player, enemy, etc.)

**Color Categories:**

- Sky colors (day, night, evening variants)
- Grass colors with gradients
- Player sprite colors (Mario palette)
- Enemy monster colors
- UI colors (brick, coin, etc.)
- Celestial body colors (sun, moon)

### 7.4 shapes.h

**Lines:** ~300  
**Responsibilities:**

- Implement primitive drawing functions
- Wrap raw OpenGL calls in high-level interfaces

**Primitives Provided:**

- Rectangles (filled and outline, 2 variants each)
- Squares (filled and outline)
- Triangles (filled and outline)
- Circles (filled and outline)

**Design Notes:**

- All functions use `glColor3ub()` for 8-bit RGB
- All shapes drawn counter-clockwise (CCW)
- Coordinates use game world space (0,0 = bottom-left)

### 7.5 menu.h

**Lines:** ~180  
**Responsibilities:**

- Define menu UI structure
- Implement menu animations
- Provide drawing routines for menu screen

**Components:**

- Title and subtitle text
- Animated pulsing "Press Enter to Start" prompt
- Control instructions panel
- Objective panel
- Decorative coin elements
- Background gradient

### 7.6 music.h

**Lines:** ~550  
**Responsibilities:**

- Provide cross-platform audio backend using OpenAL
- Manage music and SFX playback
- Handle file I/O for WAV audio
- Implement path resolution for portable file loading

**Major Subsystems:**

- **OpenAL Context Management:** Device, context, source creation
- **WAV File Parser:** RIFF header parsing, PCM data extraction
- **Buffer Caching:** Map-based caching for repeated playback
- **Cross-Platform Path Resolution:** Search executbale and working directories
- **SFX Source Pool:** Manage multiple concurrent one-shot sounds

**Public API:**

- `Music::start(path)` - Play looped music track
- `Music::stop()` - Stop all audio and cleanup
- `Music::sync(bool inMenu)` - Switch between menu/gameplay tracks
- `Music::playCoinCollect()` - Play coin SFX
- `Music::playEnemyHit()` - Play enemy hit SFX
- `Music::playWin()` - Play victory SFX

### 7.7 Enemy.h

**Lines:** ~200  
**Responsibilities:**

- Define enemy entity and behavior
- Implement enemy rendering
- Provide collision detection with player
- Manage enemy movement and AI

**Enemy Attributes:**

- Position (x, y)
- Dimensions (width = 40, height = 40)
- Movement speed and direction
- Patrol boundaries (minX, maxX)

**Functions:**

- `isOverlap()` - AABB collision detection
- `hitsPlayer()` - Specific player collision check
- `update()` - Update position with patrol logic
- `enemyDraw()` - Render detailed enemy sprite

### 7.8 input/Input.hpp

**Lines:** ~220  
**Responsibilities:**

- Manage keyboard input state
- Provide query functions for game logic
- Handle one-shot events (jump, start)

**State Tracking:**

- Left/right movement flags (continuous)
- Jump flags (continuous + one-shot)
- Start request flag (one-shot, consumed)

**API Functions:**

- `setKeyState(key, pressed)` - Internal dispatcher
- `isLeftPressed()`, `isRightPressed()`, `isJumpPressed()` - Query
- `consumeJumpRequested()`, `consumeStartRequested()` - Consume one-shot
- `keyPress()`, `keyRelease()` - GLUT callbacks

### 7.9 physics/Physics.h

**Lines:** ~35  
**Responsibilities:**

- Implement gravity application
- Provide physics calculations

**Functions:**

- `applyGravity(posY, velY, gravityForce=0.5)` - Apply downward acceleration

### 7.10 physics/Collision.h

**Lines:** ~120  
**Responsibilities:**

- Implement collision detection algorithms
- Provide collision response logic

**Functions:**

- `groundCollision()` - Detect landing on ground
- `platformCollision()` - Detect landing on platform (one-way)
- `isOverlap()` - AABB intersection test (in Enemy.h, re-exported)

### 7.11 color.md

**Lines:** ~60  
**Responsibilities:**

- Document Mario-style color palette
- Provide reference table with hex and RGB values
- Explain color usage for game elements

**Content:**

- Mario character colors (hat, overalls, skin)
- Environment colors (sky, grass, brick)
- Enemy colors (Goomba, Koopa, etc.)
- Comparison with NES/SMB1 authentic palette

---

## 8. Build and Compilation

### 8.1 Build Command

**macOS:**

```bash
clang++ -o main main.cpp -framework OpenGL -framework GLUT -framework OpenAL
```

**Linux:**

```bash
g++ -o main main.cpp -lGL -lglut -lopenal
```

**Windows (MSVC):**

```bash
cl /EHsc main.cpp /link opengl32.lib glut32.lib openal32.lib
```

### 8.2 Compilation Flags

- `-o main` - Output executable name
- `-framework OpenGL`, `-lGL` - OpenGL library
- `-framework GLUT`, `-lglut` - GLUT framework
- `-framework OpenAL`, `-lopenal` - OpenAL audio
- `-Wall -O2` - Recommended: warnings and optimization

### 8.3 Compiler Support

- **Minimum C++ Version:** C++11 (uses `static` in namespace for state)
- **Tested Compilers:** clang++ (macOS), g++ (Linux)
- **Deprecated Warnings:** Suppressed via pragma in header.h and music.h

### 8.4 Header Dependencies

```
main.cpp
├── header.h (GL includes, std libs)
├── shapes.h (drawing primitives)
├── colors.h (RGB color constants)
├── menu.h (menu UI)
│   ├── header.h
│   ├── colors.h
│   ├── shapes.h
│   └── drawCenteredText() [forward declared, defined in main.cpp]
├── music.h (audio system)
│   ├── header.h
│   └── [OpenAL headers]
├── Enemy.h (enemy entity)
│   ├── header.h
│   ├── shapes.h
│   └── colors.h
├── input/Input.hpp (input handling)
│   └── header.h
├── physics/Physics.h (gravity)
│   └── header.h
└── physics/Collision.h (collision detection)
```

---

## 9. Asset Management

### 9.1 Audio Assets

All audio files should be PCM WAV format (not MP3-in-WAV):

| File          | Purpose                    | Format          | Volume | Loop |
| ------------- | -------------------------- | --------------- | ------ | ---- |
| gameTrack.wav | Menu & gameplay background | PCM WAV 44.1kHz | 75%    | Yes  |
| coinSound.wav | Coin collection SFX        | PCM WAV 44.1kHz | 90%    | No   |
| faaah.wav     | Enemy hit SFX              | PCM WAV 44.1kHz | 90%    | No   |
| 7crore.wav    | Victory sound              | PCM WAV 44.1kHz | 90%    | No   |

### 9.2 Audio Format Conversion

If source files are MP3 or other formats, convert to PCM WAV:

```bash
ffmpeg -i gameTrack.mp3 -acodec pcm_s16le -ar 44100 gameTrack.wav
ffmpeg -i coinSound.mp3 -acodec pcm_s16le -ar 44100 coinSound.wav
ffmpeg -i faaah.mp3 -acodec pcm_s16le -ar 44100 faaah.wav
ffmpeg -i win_sound.mp3 -acodec pcm_s16le -ar 44100 7crore.wav
```

### 9.3 Audio File Path Resolution

Files can be placed in:

1. **Working directory:** Where executable runs from
2. **Executable directory:** Where the `main` binary is located

Audio system attempts both before warning "Audio file not found".

---

## 10. Implementation Techniques and Design Patterns

### 10.1 Singleton Pattern (Static State)

Used throughout for global state management:

```cpp
namespace Input {
  static bool& leftState() {
    static bool value = false;
    return value;
  }
}
```

**Benefits:** Clean API, thread-safe initialization, module-like namespace organization

### 10.2 Namespace Organization

```cpp
namespace Music { ... }
namespace Physics { ... }
namespace Collision { ... }
namespace Input { ... }
namespace Enemy { ... }
namespace MenuUI { ... }
```

**Benefits:** Avoid global namespace pollution, logical grouping, easy to find related code

### 10.3 Painter's Algorithm

Rendering in strict back-to-front order:

1. Background
2. Clouds
3. Platforms
4. Coins
5. Player
6. Enemies
7. UI
   **Benefits:** Correct depth without Z-buffer in 2D orthographic projection

### 10.4 State Machines

**Menu/Gameplay State:**

```
showMenu = true  →  (Enter pressed)  →  showMenu = false
```

**Game Win/Lose:**

```
(normal gameplay)  →  gameWon/gameOver = true  →  (frozen, display overlay)
```

### 10.5 Buffer Caching

Audio files loaded once, reused for multiple plays:

```cpp
map<string, ALuint> bufferCache;
```

**Benefits:** Performance (avoid reload), memory efficient for repeated SFX

### 10.6 One-Shot Event Consumption

Events queried once and consumed (cleared):

```cpp
bool consumeJumpRequested() {
  bool requested = jumpRequestedState();
  jumpRequestedState() = false;  // Clear for next frame
  return requested;
}
```

**Benefits:** Prevents repeated event handling, frame-based input consistency

### 10.7 Cross-Platform Path Resolution

Executable directory detection using platform-specific APIs:

- **macOS:** `_NSGetExecutablePath()`
- **Linux:** `readlink("/proc/self/exe")`
- **Windows:** `GetModuleFileNameA()`

**Benefits:** Portable audio loading, works from any working directory

### 10.8 Error Recovery

Graceful degradation for missing audio:

```cpp
if (!loadWavFile(path, ...)) {
  warnMissingOnce(path);  // Warn once per file
  return 0;               // Silently fail, game continues
}
```

**Benefits:** Game playable without audio, clear diagnostics

---

## 11. Performance Characteristics

### 11.1 Update Frequency

- **Target:** 120 FPS (8ms per frame)
- **Mechanism:** `glutTimerFunc(8, update, 0)`
- **Actual:** Limited by system performance and rendering speed

### 11.2 Rendering Complexity

- **Static Geometry:** Platforms (up to 9 per level)
- **Dynamic Objects:** Player (1), enemies (3-4), coins (9-10), clouds (4)
- **Total Draw Calls:** ~50-100 per frame (dependent on particle/detail level)

### 11.3 Memory Usage

- **Level Data:** < 1 MB (vectors of platforms, coins, enemies)
- **Audio Buffers:** Varies by WAV file size (typically 1-10 MB per track)
- **OpenGL Buffers:** Immediate mode (no VBOs), minimal GPU memory

### 11.4 CPU Utilization

- **Physics/Collision:** O(n) for n enemies/platforms per frame
- **Rendering:** O(n) for n drawable objects
- **Audio:** Background processing in OpenAL library

---

## 12. Known Limitations and Future Improvements

### 12.1 Current Limitations

1. **Legacy OpenGL:** Uses deprecated immediate mode (works but outdated)
2. **Fixed Resolution:** 800×600 hardcoded (not scalable)
3. **No Particle Effects:** Coins rotate/pulse but no trails or explosions
4. **Limited AI:** Enemies only patrol horizontally
5. **No Save System:** Game state not persistent between sessions
6. **One Control Scheme:** Only keyboard, no gamepad support
7. **Audio Limitations:** PCM WAV only (no MP3, OGG, FLAC)
8. **No Localization:** All text in English only

### 12.2 Future Enhancement Opportunities

1. **Modern Graphics:** Port to OpenGL 3.3+/4.5+ with VAO/VBO
2. **Scalable UI:** Resolution-independent rendering
3. **Advanced Enemies:** Jumping enemies, pattern-based AI, boss fights
4. **Particle System:** Dust clouds, coin sparkles, explosions
5. **Level Editor:** Create/edit levels visually
6. **Save/Load:** Persistent high scores and level progress
7. **Controller Support:** Xbox/PlayStation controller support
8. **Audio Formats:** Support OGG Vorbis, FLAC, or use external library
9. **Soundtrack Variety:** Different music per level
10. **Visual Polish:** Parallax scrolling, post-processing effects
11. **Platform Hazards:** Spikes, moving platforms, conveyor belts
12. **Power-ups:** Shield, speed boost, double jump abilities

---

## 13. Troubleshooting Guide

### 13.1 Compilation Issues

**Error: "fatal error: GL/gl.h: No such file or directory"**

- **Linux:** Install GLUT dev packages: `sudo apt install freeglut3-dev`
- **macOS:** Should be included with Xcode command line tools

**Error: "Undefined reference to `alGenBuffers`"**

- **macOS:** Add `-framework OpenAL` to compile command
- **Linux:** Add `-lopenal` to compile command; install: `sudo apt install libopenal-dev`

### 13.2 Runtime Issues

**No Audio Playing:**

1. Check audio files exist in working directory or executable directory
2. Ensure files are PCM WAV (not MP3-in-WAV): `file *.wav`
3. Check console output for "Audio file not found" messages
4. Verify OpenAL system: `pacmd list | grep -i audio` (Linux) or System Preferences (macOS)

**Enemies Not Appearing:**

1. Check screen boundaries (they spawn at specific coordinates)
2. Verify collision detection: Add debug print statements in `update()`
3. Confirm level data loaded: Check `platforms.size()`, `enemies.size()`

**Player Falls Through Platforms:**

1. Check previousPlayerY calculation (must happen before gravity)
2. Verify platform collision order (checked after ground)
3. Check playerVelocityY sign (must be < 0 for landing)

**Menu Not Showing:**

1. Check `showMenu = true` in `init()`
2. Verify MenuUI::reset() called before display
3. Confirm `glMatrixMode(GL_MODELVIEW)` set after projection

### 13.3 Optimization Tips

**If frame rate drops:**

1. Reduce cloud count or complexity
2. Simplify player sprite (fewer primitives)
3. Profile with frame timing: `cout << "FPS: " << 1000.0/deltaTime << endl;`

**Memory issues:**

1. Limit SFX source pool size (currently unbounded)
2. Implement LOD (level of detail) for distant objects
3. Release unused level data between level transitions

---

## 14. Code Quality and Best Practices

### 14.1 Coding Conventions

- **Naming:** Camel case for variables (`playerX`), PascalCase for types (`LevelData`)
- **Namespaces:** Logical grouping by system (Physics, Collision, Input)
- **Comments:** Separation headers for logical sections, TODO markers for incomplete features
- **Formatting:** 4-space indentation, K&R brace style

### 14.2 Design Principles Applied

- **Separation of Concerns:** Physics separate from rendering, audio separate from game logic
- **Single Responsibility:** Each namespace handles one system
- **DRY (Don't Repeat Yourself):** Reusable drawing primitives (shapes.h), centralized colors (colors.h)
- **Fail Gracefully:** Audio system continues if files missing, game continues if audio unavailable

### 14.3 Type Safety

- **Unsigned char:** For color values (0-255 range explicit)
- **Float:** For positions and physics (precision for velocities)
- **Vector:** For dynamic collections (platforms, coins, enemies)
- **Bool:** For state flags (explicit intent)

### 14.4 const Correctness

```cpp
const Cloud& cloud : clouds         // Const reference in read-only loops
const string resolvedPath = ...     // Resolved path doesn't change
static const string menuTrackPath   // Compile-time constant
```

---

## 15. Conclusion

PixelHop demonstrates a complete 2D game pipeline from scratch using fundamental computer graphics and game development concepts. The project successfully integrates:

- **Graphics:** OpenGL immediate mode with painter's algorithm
- **Physics:** Gravity simulation and collision detection
- **Audio:** Cross-platform OpenAL backend with file I/O
- **Input:** Keyboard state management with one-shot events
- **Architecture:** Namespace-based modular design
- **Game Design:** Progressive difficulty, clear objectives, polished presentation

The codebase serves as an excellent reference for learning game development fundamentals and can be extended with modern graphics APIs, advanced AI, and additional features. Its modular architecture makes it suitable for educational purposes and as a foundation for larger projects.

---

## Appendix A: Quick Reference

### Compilation

```bash
# macOS
clang++ -o main main.cpp -framework OpenGL -framework GLUT -framework OpenAL

# Linux
g++ -o main main.cpp -lGL -lglut -lopenal

# Run
./main
```

### Key Controls

| Key   | Action     |
| ----- | ---------- |
| A     | Move left  |
| D     | Move right |
| Space | Jump       |
| Enter | Start game |
| ESC   | Quit       |

### Audio Files Location

```
.
├── gameTrack.wav       (Menu & gameplay music)
├── coinSound.wav       (Coin collection)
├── faaah.wav           (Enemy hit)
└── 7crore.wav          (Victory)
```

### Color Palette Quick Lookup

- Sky: RGB(0, 155, 217)
- Grass: RGB(68, 175, 53)
- Mario Red: RGB(254, 0, 2)
- Brick: RGB(185, 39, 22)
- Coin: RGB(248, 205, 48)

---

**Document Generated:** 2026  
**Project Status:** Complete (Playable with 3 levels)  
**Last Update:** Addition of win SFX when level 3 cleared
