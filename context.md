# PixelHop Session Context

## Project

- 2D platformer game built with C++ and GLUT.
- Current working file: `context.md`.
- Goal: keep the project manageable and finishable as a polished prototype, not a full Mario clone.

## What is already done in code

- GLUT window and main game loop work.
- Player movement, gravity, jumping, ground collision, and platform collision are implemented.
- Input handling for A, D, and Space works.
- Enemy logic exists and was split into `Enemy.h`.
- Basic score, lives, win, and lose logic exist.
- The project currently builds and runs successfully.

## Important code notes

- Enemy behavior currently: patrol, chase when close, hurt on touch, stay within boundaries.
- The score system was adjusted so it does not instantly win from standing on the ground.
- The current implementation is still shape-based, not sprite-based.

## Decisions already made

### Collectibles and scoring

- Coins are the only collectible.
- Each coin = +1 point.
- Finishing a level gives bonus points.
- Defeating an enemy gives bonus points.
- No special items.
- No hidden area rewards.

### Level system

- Add a `currentLevel` state in `main.cpp`.
- Create 3 separate handcrafted level layouts using the same Platform, Coin, and enemy setup style already in the file.
- Add a reset function that reloads player position, enemy position, coin states, score rules, and level-specific objects.
- Detect level completion when all coins are collected or a finish target is reached.
- Advance to the next level, and on the last level show a win screen or final completion state.
- Add a restart path for death so the current level can be replayed cleanly.
- Keep the implementation inside `main.cpp` for now.

### Enemy behavior

- Patrol normally by default.
- Chase the player when close.
- Hurt the player on touch.
- Stay within level boundaries.

### UI and polish

- Main menu.
- Pause and resume.
- HUD for score, lives, and level.
- Win/lose messages.
- Clean background and readable colors.

### Player feel

- Make movement smoother.
- Make jumping feel better.
- Add better landing behavior.
- Add coyote time.
- Add jump buffering.
- No dash, no double jump, and no wall jump for this version.

## Current priority order

1. Add coins and meaningful scoring.
2. Build the 3-level system.
3. Improve enemy behavior.
4. Add UI and polish.
5. Keep sprites and animation for later, only after gameplay is solid.

## Markdown status

- `platformer.md` is the main roadmap document now.
- `context.md` is the session handoff note for current state and next steps.

## Things to remember in future chats

- Do not restart the whole discussion about scope from scratch.
- Use this context to continue from the agreed game design.
- Keep the project realistic and finishable.
- Preserve the Mario-style color palette preference from `color.md` / `colors.h`.
