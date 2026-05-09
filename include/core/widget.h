#pragma once

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_render.h"

class Widget{
public:
    Widget();
    void setVisible(bool visible);
    bool Visible() const;
    void setPosition(float x, float y);
    void setSize(float width, float height);
    SDL_FRect getRect();
protected:
    float x, y, width, height;
    bool visible;
public:
    virtual ~Widget() = default;
    virtual void update(SDL_Event& event) = 0;
    virtual void render(SDL_Renderer* renderer) = 0;
};
