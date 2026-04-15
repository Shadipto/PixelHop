#ifndef PLATFORM_H
#define PLATFORM_H

class Renderer;

class Platform {
public:
    Platform(float x, float y, float w, float h);
    void render(class Renderer& renderer) const;
    float x, y, w, h;
};

#endif // PLATFORM_H
