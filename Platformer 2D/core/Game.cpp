#include "Game.h"
#include "../utils/Constants.h"
#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <chrono>
#include <algorithm>
#include <cstdio>

Game* Game::Instance = nullptr;

Game::Game() : windowWidth(Constants::WINDOW_WIDTH), windowHeight(Constants::WINDOW_HEIGHT), running(false), renderer(windowWidth, windowHeight), fps(0.0f) {
}

Game::~Game() {}

void Game::init(int argc, char** argv) {
    Instance = this;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("2D Platformer - Days 1-5");

    glutDisplayFunc(displayCallback);
    glutIdleFunc(idleCallback);
    glutKeyboardFunc(keyDownCallback);
    glutKeyboardUpFunc(keyUpCallback);
    glutReshapeFunc(reshapeCallback);

    // initialize game objects
    player.init(100.f, Constants::FLOOR_Y);
    // floor platform (height = FLOOR_Y)
    platforms.emplace_back(0.f, 0.f, (float)windowWidth, Constants::FLOOR_Y);
    // sample elevated platforms for Day 6 testing
    platforms.emplace_back(200.f, 150.f, 150.f, 20.f);
    platforms.emplace_back(420.f, 260.f, 120.f, 20.f);

    renderer.setSize(windowWidth, windowHeight);
    running = true;
}

void Game::run() {
    if (running) glutMainLoop();
}

void Game::update(float dt) {
    player.update(dt, input);

    // By default assume not grounded; will be set true if collision resolution places player on a platform
    player.onGround = false;

    // resolve collisions with platforms (AABB)
    for (auto &plat : platforms) {
        float pLeft = player.x;
        float pRight = player.x + player.w;
        float pBottom = player.y;
        float pTop = player.y + player.h;

        float sLeft = plat.x;
        float sRight = plat.x + plat.w;
        float sBottom = plat.y;
        float sTop = plat.y + plat.h;

        // test overlap
        if (pRight > sLeft && pLeft < sRight && pTop > sBottom && pBottom < sTop) {
            float overlapX = std::min(pRight, sRight) - std::max(pLeft, sLeft);
            float overlapY = std::min(pTop, sTop) - std::max(pBottom, sBottom);

            if (overlapY < overlapX) {
                // vertical resolution
                if (player.prevY >= sTop) {
                    // landed on top
                    player.y = sTop;
                    player.vy = 0.f;
                    player.onGround = true;
                } else if (player.prevY + player.h <= sBottom) {
                    // hit from below
                    player.y = sBottom - player.h;
                    player.vy = 0.f;
                } else {
                    // ambiguous: choose conservative resolution
                    if (player.vy < 0.f) {
                        player.y = sTop;
                        player.vy = 0.f;
                        player.onGround = true;
                    } else {
                        player.y = sBottom - player.h;
                        player.vy = 0.f;
                    }
                }
            } else {
                // horizontal resolution
                if (player.prevX + player.w <= sLeft) {
                    player.x = sLeft - player.w;
                } else if (player.prevX >= sRight) {
                    player.x = sRight;
                } else {
                    if (player.vx > 0.f) player.x = sLeft - player.w;
                    else player.x = sRight;
                }
                player.vx = 0.f;
            }
        }
    }

    // keep player inside window horizontally
    if (player.x < 0.f) player.x = 0.f;
    if (player.x + player.w > (float)windowWidth) player.x = (float)windowWidth - player.w;
}

void Game::render() {
    renderer.clear();
    for (const auto &p : platforms) p.render(renderer);
    player.render(renderer);
    // draw FPS
    char buf[64];
    std::snprintf(buf, sizeof(buf), "FPS: %.1f", fps);
    renderer.drawText(8.0f, (float)windowHeight - 18.0f, buf, 0.f, 0.f, 0.f);
    glutSwapBuffers();
}

void Game::onKeyDown(unsigned char key, int x, int y) {
    input.keyDown(key);
}

void Game::onKeyUp(unsigned char key, int x, int y) {
    input.keyUp(key);
}

void Game::reshape(int w, int h) {
    windowWidth = w; windowHeight = h;
    renderer.setSize(w, h);
}

static std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now();
void Game::idleCallback() {
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<float> delta = now - lastTime;
    lastTime = now;
    float dt = delta.count();
    const float maxDt = 0.05f; // clamp very large frame times
    if (dt > maxDt) dt = maxDt;
    if (Game::Instance) {
        Game::Instance->update(dt);
        if (dt > 1e-6f) Game::Instance->fps = 0.92f * Game::Instance->fps + 0.08f * (1.0f / dt);
        glutPostRedisplay();
    }
}

void Game::displayCallback() {
    if (Game::Instance) Game::Instance->render();
}

void Game::keyDownCallback(unsigned char key, int x, int y) {
    if (Game::Instance) Game::Instance->onKeyDown(key, x, y);
    if (key == 27) exit(0);
}

void Game::keyUpCallback(unsigned char key, int x, int y) {
    if (Game::Instance) Game::Instance->onKeyUp(key, x, y);
}

void Game::reshapeCallback(int w, int h) {
    if (Game::Instance) Game::Instance->reshape(w, h);
}
