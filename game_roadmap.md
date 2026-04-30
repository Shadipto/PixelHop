# PixelHop Game Roadmap

This file tracks the next requirements for the game. It starts as a planning list and can be updated as we decide details.

## Current Base

- [x] Player movement
- [x] Gravity and jumping
- [x] Platforms and collision
- [x] One enemy
- [x] Basic score and win/lose state

## 1. Improve Player Feel

### Final Decisions

- Movement should feel smooth and responsive, not slippery.
- Jumping should be consistent and easy to control.
- Landing should snap cleanly onto platforms and the ground.
- Add coyote time so the player can still jump briefly after walking off an edge.
- Add jump buffering so a jump input just before landing still triggers.
- Keep the core jump simple for now: no dash, no double jump, and no wall jump in this version.

### Implementation Targets

- [ ] Make movement smoother
- [ ] Make jumping feel better
- [ ] Add better landing behavior
- [ ] Add jump grace time (coyote time)
- [ ] Add jump buffering
- [ ] Keep extra movement skills out of this version

## 2. Better Enemy Behavior

### Final Decisions

- Enemies should patrol normally by default.
- Enemies should chase the player when close.
- Enemies should hurt the player on touch.
- Enemies should stay within level boundaries.
- Keep to one enemy type for now.

### Implementation Targets

- [ ] Add smarter enemy movement
- [ ] Add patrol behavior
- [ ] Add chase behavior when the player is close
- [ ] Add touch damage or player reset on collision
- [ ] Keep enemies inside level boundaries
- [ ] Avoid adding multiple enemy types for now

## 3. Collectibles and Scoring

- [ ] Add collectibles such as coins or stars
- [ ] Decide what each collectible is worth
- [ ] Make score based on gameplay events, not just standing on ground
- [ ] Add bonus score for reaching harder areas
- [ ] Add a clear scoring UI

## 4. Real Level System

- [ ] Create a proper level structure
- [ ] Decide how many levels the game should have
- [ ] Add start and finish points
- [ ] Add checkpoints if needed
- [ ] Add level progression after completion
- [ ] Add restart and retry logic
- [ ] Decide on hazards like spikes, gaps, or moving platforms

## 5. UI, Sound, and Polish

- [ ] Add a main menu
- [ ] Add pause and resume
- [ ] Add game over and victory screens
- [ ] Add HUD for score, lives, and level
- [ ] Add sound effects
- [ ] Add background music
- [ ] Improve background visuals
- [ ] Improve colors and readability

## 6. Sprites and Animation

- [ ] Replace shapes with sprites
- [ ] Add player walk animation
- [ ] Add player jump animation
- [ ] Add enemy sprites
- [ ] Add platform or environment textures
- [ ] Add animation for collectibles
- [ ] Tune sprite scaling and rendering

## Open Questions

- Should the game stay simple and clean, or become more like a full Mario-style platformer?
- Should the player have health/lives, or should one hit always restart the level?
- Should collectibles be required to finish a level or only optional?
- Should the game have multiple short levels or one larger level with checkpoints?
- Should we keep the current shape-based style until gameplay is finalized?

## Next Update Format

When we decide something, I can update this file with:

- a checked box for completed items
- short notes for decisions
- new requirements added later
