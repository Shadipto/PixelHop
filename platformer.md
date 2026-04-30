# 🎮 2D Platformer Game (GLUT + C++)

## 📌 Project Overview

This project is a **2D platformer game inspired by Mario-style gameplay**, built using **C++ and GLUT (OpenGL Utility Toolkit)**.

The goal is to implement a complete playable game with:

- Player movement with physics (gravity + jumping)
- Collision detection with platforms
- Enemy movement system
- Score and game rules
- Optional sprite-based graphics upgrade

## 🎯 Current Priority

The next main focus is to make the game feel more complete and less basic by adding:

- Real collectibles and meaningful scoring
- A proper level system instead of one simple scene
- Better enemy behavior beyond left-right movement
- Stronger UI and polish, including menus, pause, HUD, and clear messages

These are the highest-priority features before any visual sprite upgrade.

The project focuses on core computer graphics concepts:

- Real-time rendering
- Game loop design
- Physics simulation
- Modular system thinking

---

# 🧠 Core Game Architecture Concept

The game follows a simple real-time loop:

Each frame:

1. Input is read (keyboard)
2. Game updates player/enemies
3. Physics is applied (gravity, velocity)
4. Collision is resolved
5. Everything is rendered

---

# 🚀 PHASE 1 — CORE GAME (Day 1–10)

## 🎯 Goal:

Build a fully playable 2D platformer using simple shapes.

---

## 🧩 Day 1 — Project Setup

- Setup GLUT window
- Create game loop structure
- Initialize basic rendering

✔ Output: Window opens successfully

---

## 🖼️ Day 2 — Basic Rendering

- Draw player (rectangle)
- Draw ground/platform (rectangle)

✔ Output: Objects visible on screen

---

## 🎮 Day 3 — Input System

- Implement keyboard input (A, D, Space)
- Store key states

✔ Output: Input detection works

---

## 🏃 Day 4 — Player Movement

- Move player left and right
- Add movement speed

✔ Output: Player moves smoothly

---

## 🌍 Day 5 — Gravity System

- Apply gravity force
- Add vertical velocity

✔ Output: Player falls naturally

---

## 🧱 Day 6 — Ground Collision

- Implement collision detection
- Stop player from falling through ground

✔ Output: Player stands correctly

---

## 🪜 Day 7 — Platform System

- Add multiple platforms
- Platform collision handling

✔ Output: Player can jump between platforms

---

## 🧠 Day 8 — Jump System Refinement

- Add jump force
- Prevent double jumping
- Improve landing behavior

✔ Output: Smooth jumping mechanics

---

## 👾 Day 9 — Enemy System

- Add simple enemy movement
- Basic player-enemy collision

✔ Output: Enemy exists in game

---

## 🪙 Day 10 — Score + Game Rules

- Add scoring system
- Add win/lose condition

✔ Output: Fully playable game

---

# 🎨 PHASE 2 — GAME EXPANSION + POLISH (NEXT PRIORITY)

## 🎯 Goal:

Make the game deeper, clearer, and more complete before moving to sprites.

---

## 🪙 Day 11 — Collectibles + Scoring

- Add coins as the main collectible
- Make each coin worth +1 point
- Add bonus points for finishing a level
- Add bonus points for defeating an enemy
- Keep the scoring simple and easy to understand

✔ Output: Score feels meaningful

---

## 🧭 Day 12 — Level System

- Create 3 small handcrafted levels
- Use one finish goal per level
- Use coin-based scoring inside the levels
- Add one restart system for failed runs
- Add a simple transition to the next level after completion

✔ Output: More than one simple scene

---

## 👾 Day 13 — Enemy Behavior Upgrade

- Patrol normally by default
- Chase the player when close
- Hurt the player on touch
- Stay within level boundaries

✔ Output: Enemies feel more like part of the game

---

## 🎨 Day 14 — UI and Polish

- Add a main menu
- Add pause and resume
- Add HUD for score, lives, and level
- Add win/lose messages
- Improve background visuals and readable colors

✔ Output: Game is easier to understand and play

---

# 🖼️ PHASE 3 — OPTIONAL GRAPHICS UPGRADE (LATER)

## 🎯 Goal:

Replace shapes with sprite-based graphics after gameplay is solid.

---

## 🧰 Day 13 — Texture System Setup

- Load images using OpenGL texture system
- Initialize image rendering support

✔ Output: Images can be loaded

---

## 👤 Day 14 — Player Sprite

- Replace rectangle with image
- Fix scaling issues

✔ Output: Player sprite visible

---

## 🧱 Day 15 — Environment Sprites

- Replace platforms with textures
- Add background image

✔ Output: Visual upgrade applied

---

## 🎞️ Day 16 — Animation System

- Implement frame-based animation
- Add walking cycle

✔ Output: Animated player movement

---

## 👾 Day 17 — Enemy Sprites

- Add enemy textures
- Optional animation support

✔ Output: Animated enemy

---

## 🎮 Day 18 — Final Polish

- Fix rendering issues
- Smooth animations
- Final visual tuning

✔ Output: Mario-style prototype feel

---

# ⚠️ IMPORTANT DEVELOPMENT RULES

- Always complete gameplay before graphics
- Keep physics, rendering, and input separate
- Test every feature before moving to the next
- Avoid adding sprites before core mechanics are stable

---

# 🎯 FINAL OUTCOME

By the end of this project, you will have:

✔ Fully working 2D platformer  
✔ Clean C++ modular game structure  
✔ Physics-based movement system  
✔ Collision detection system  
✔ Score and enemy mechanics  
✔ Optional sprite-based visual upgrade

---

# 🧠 SUMMARY

This project replicates the structure of classic platformers like Mario using:

- Game loop architecture
- Physics simulation (gravity + jump)
- Collision detection system
- Modular system design
- OpenGL rendering using GLUT

# 🧱 Project File Architecture (GLUT 2D Platformer)

## 📁 Full Structure

PlatformerGame/
│
├── main.cpp
│
├── core/
│ ├── Game.h
│ ├── Game.cpp
│ ├── Renderer.h
│ ├── Renderer.cpp
│
├── entities/
│ ├── Player.h
│ ├── Player.cpp
│ ├── Platform.h
│ ├── Platform.cpp
│ ├── Enemy.h
│ ├── Enemy.cpp
│
├── physics/
│ ├── Physics.h
│ ├── Physics.cpp
│ ├── Collision.h
│ ├── Collision.cpp
│
├── input/
│ ├── Input.h
│ ├── Input.cpp
│
├── utils/
│ ├── Constants.h
│
├── assets/ (optional for Phase 3)
│ ├── images/
│ ├── sounds/
│ ├── levels/
│
└── README.md
