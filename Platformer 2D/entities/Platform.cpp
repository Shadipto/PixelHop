#include "Platform.h"
#include "../core/Renderer.h"

Platform::Platform(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}

void Platform::render(Renderer& renderer) const {
    renderer.drawRect(x, y, w, h, 0.35f, 0.2f, 0.05f);
}
