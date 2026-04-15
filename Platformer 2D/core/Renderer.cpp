#include "Renderer.h"

Renderer::Renderer(int width, int height) : width(width), height(height) {}

void Renderer::setSize(int w, int h) {
    width = w;
    height = h;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Renderer::clear() {
    glClearColor(0.45f, 0.7f, 0.95f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::drawRect(float x, float y, float w, float h, float r, float g, float b) const {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
}

void Renderer::drawText(float x, float y, const char* text, float r, float g, float b) const {
    glColor3f(r, g, b);
    glRasterPos2f(x, y);
    const unsigned char* c = (const unsigned char*)text;
    while (*c) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
        ++c;
    }
}
