#pragma once

#include "../header.h"

namespace Input {

inline bool& leftPressedState()
{
    static bool value = false;
    return value;
}

inline bool& rightPressedState()
{
    static bool value = false;
    return value;
}

inline bool& jumpPressedState()
{
    static bool value = false;
    return value;
}

inline bool& jumpRequestedState()
{
    static bool value = false;
    return value;
}

inline void printState()
{
    std::cout << "Input state | A: " << leftPressedState()
              << " D: " << rightPressedState()
              << " Space: " << jumpPressedState() << std::endl;
}

inline void setKeyState(unsigned char key, bool isPressed)
{
    switch (key) {
        case 'a':
        case 'A':
            leftPressedState() = isPressed;
            break;
        case 'd':
        case 'D':
            rightPressedState() = isPressed;
            break;
        case ' ':
            jumpPressedState() = isPressed;
            if (isPressed) {
                jumpRequestedState() = true;
            }
            break;
        default:
            return;
    }

    printState();
    glutPostRedisplay();
}

inline void keyPress(unsigned char key, int x, int y)
{
    setKeyState(key, true);
}

inline void keyRelease(unsigned char key, int x, int y)
{
    setKeyState(key, false);
}

inline bool isLeftPressed()
{
    return leftPressedState();
}

inline bool isRightPressed()
{
    return rightPressedState();
}

inline bool isJumpPressed()
{
    return jumpPressedState();
}

inline bool consumeJumpRequested()
{
    bool requested = jumpRequestedState();
    jumpRequestedState() = false;
    return requested;
}

} // namespace Input
