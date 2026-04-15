#include "core/Game.h"

int main(int argc, char** argv) {
    Game game;
    game.init(argc, argv);
    game.run();
    return 0;
}
