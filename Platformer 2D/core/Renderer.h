#ifndef RENDERER_H
#define RENDERER_H

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

class Renderer {
public:
    Renderer(int width = 800, int height = 600);
    void setSize(int w, int h);
    void clear();
    void drawRect(float x, float y, float w, float h, float r, float g, float b) const;
    void drawText(float x, float y, const char* text, float r = 0.f, float g = 0.f, float b = 0.f) const;
private:
    int width, height;
};

#endif // RENDERER_H
