#pragma once

#include "../header.h"


// =============================
// Input Namespace
// =============================
namespace Input 
{




    // --------------------------------
    // Left State
    // --------------------------------
    inline bool& leftState()
    {
        static bool value = false;
        return value;
    }
    // --------------------------------
    // Left State
    // --------------------------------






    // --------------------------------
    // Right State
    // --------------------------------
    inline bool& rightState()
    {
        static bool value = false;
        return value;
    }
    // --------------------------------
    // Right State
    // --------------------------------








    // --------------------------------
    // Jump State
    // --------------------------------
    inline bool& jumpState()
    {
        static bool value = false;
        return value;
    }
    // --------------------------------
    // Jump State
    // --------------------------------






    // --------------------------------
    // Jump Request State
    // --------------------------------
    inline bool& jumpRequestedState() 
    {
        static bool value = false;
        return value;
    }
    // --------------------------------
    // Jump Request State
    // --------------------------------





    // -------------------------------
    // Terminal print
    // -------------------------------
    inline void printState()
    {
        std::cout << "Input state | A: " << leftState() << " D: " << rightState() << " Space: " << jumpState() << std::endl;
    }
    // -------------------------------
    // Terminal print
    // -------------------------------













    // =============================
    // Input switch case
    // =============================
    inline void setKeyState(unsigned char key, bool isPressed) // Not a good naming 'isPressed'
    {
        switch (key) {
            case 'a':
            case 'A':
                leftState() = isPressed;
                break;
            case 'd':
            case 'D':
                rightState() = isPressed;
                break;
            case ' ':
                jumpState() = isPressed;
                if (isPressed) 
                {
                    jumpRequestedState() = true;
                }
                break;
            default:
                return;
        }

        printState();
        glutPostRedisplay();
    }
    // =============================
    // Input switch case
    // =============================









    // --------------------------------
    // Key Pressed
    // --------------------------------
    inline void keyPress(unsigned char key, int x, int y)
    {
        setKeyState(key, true);
    }
    // --------------------------------
    // Key Pressed
    // --------------------------------






    // --------------------------------
    // Key Released
    // --------------------------------
    inline void keyRelease(unsigned char key, int x, int y)
    {
        setKeyState(key, false);
    }
    // --------------------------------
    // Key Released
    // --------------------------------









    // --------------------------------
    // Is Left Pressed
    // --------------------------------
    inline bool isLeftPressed()
    {
        return leftState();
    }
    // --------------------------------
    // Is Left Pressed
    // --------------------------------





    // --------------------------------
    // Is Right Pressed
    // --------------------------------
    inline bool isRightPressed()
    {
        return rightState();
    }
    // --------------------------------
    // Is Right Pressed
    // --------------------------------







    // --------------------------------
    // Is Jump Pressed
    // --------------------------------
    inline bool isJumpPressed()
    {
        return jumpState();
    }
    // --------------------------------
    // Is Jump Pressed
    // --------------------------------









    // --------------------------------
    // Consume Jump Request
    // --------------------------------
    inline bool consumeJumpRequested()
    {
        bool requested = jumpRequestedState();
        jumpRequestedState() = false;
        return requested;
    }
    // --------------------------------
    // Consume Jump Request
    // --------------------------------





}
// =============================
// Input Namespace
// =============================
