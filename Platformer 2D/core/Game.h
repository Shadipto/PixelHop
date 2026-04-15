#ifndef GAME_H
#define GAME_H

#include "../entities/Player.h"
#include "../entities/Platform.h"
#include "../core/Renderer.h"
#include "../input/Input.h"
#include <vector>

class Game {
public:
    Game();
    ~Game();
    void init(int argc, char** argv);
    void run();
    void update(float dt);
    void render();
    void onKeyDown(unsigned char key, int x, int y);
    void onKeyUp(unsigned char key, int x, int y);
    void reshape(int w, int h);

    static Game* Instance;

private:
    int windowWidth, windowHeight;
    bool running;
    Player player;
    std::vector<Platform> platforms;
    Renderer renderer;
    Input input;
    float fps;

    static void displayCallback();
    static void idleCallback();
    static void keyDownCallback(unsigned char key, int x, int y);
    static void keyUpCallback(unsigned char key, int x, int y);
    static void reshapeCallback(int w, int h);
};

#endif // GAME_H
