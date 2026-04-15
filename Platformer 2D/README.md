# 2D Platformer (GLUT + C++)

This workspace contains a minimal 2D platformer prototype implementing Days 1–5 from the plan: window + renderer, basic shapes, input, horizontal movement and gravity.

Build (macOS / Linux):

```bash
make
./platformer
```

Controls:

- `A` / `D` : move left / right
- `Space` : jump (basic)
- `Esc` : quit

Files of interest:

- [main.cpp](main.cpp)
- [core/Game.h](core/Game.h)
- [entities/Player.cpp](entities/Player.cpp)
