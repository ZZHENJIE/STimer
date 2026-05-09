#pragma once

#include <SDL3/SDL_events.h>
#include "core/widget.h"
#include <string>
#include <functional>

class Button : public Widget {
private:
    std::string label;
    std::function<void()> onClick;
public:
    Button(std::string label);
    void setOnClick(std::function<void()> callback);
    void update(SDL_Event& event) override;
    void render(SDL_Renderer* renderer) override;
};
