#include "Input.h"
#include <cstring>

Input::Input() {
    std::memset(keys, 0, sizeof(keys));
    std::memset(pressed, 0, sizeof(pressed));
}

void Input::keyDown(unsigned char key) {
    if (!keys[key]) pressed[key] = true;
    keys[key] = true;
}

void Input::keyUp(unsigned char key) {
    keys[key] = false;
}

bool Input::isDown(unsigned char key) const {
    return keys[key];
}

bool Input::wasPressed(unsigned char key) {
    if (pressed[key]) {
        pressed[key] = false;
        return true;
    }
    return false;
}

void Input::clearPressed() {
    std::memset(pressed, 0, sizeof(pressed));
}
