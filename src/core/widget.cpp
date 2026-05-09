#include "core/widget.h"
#include <SDL3/SDL_rect.h>

Widget::Widget() : x(0), y(0), width(0), height(0), visible(true) {

}

void Widget::setVisible(bool visible) { this->visible = visible; }

bool Widget::Visible() const { return visible; }

void Widget::setPosition(float x, float y) { this->x = x; this->y = y; }

void Widget::setSize(float width, float height) { this->width = width; this->height = height; }

SDL_FRect Widget::getRect() {
    return {x, y, width, height};
}
