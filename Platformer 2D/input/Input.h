#ifndef INPUT_H
#define INPUT_H

class Input {
public:
    Input();
    void keyDown(unsigned char key);
    void keyUp(unsigned char key);
    bool isDown(unsigned char key) const;
    bool wasPressed(unsigned char key);
    void clearPressed();
private:
    bool keys[256];
    bool pressed[256];
};

#endif // INPUT_H
