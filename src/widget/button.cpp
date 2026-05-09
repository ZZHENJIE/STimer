#include "widget/button.h"

Button::Button(std::string label): label(label) {}

void Button::setOnClick(std::function<void()> callback) {
    onClick = callback;
}

void Button::update(SDL_Event& event){
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        if (onClick) {
            onClick();
        }
    }
}

void Button::render(SDL_Renderer* renderer) {
    SDL_FRect rect = getRect();
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderRect(renderer, &rect);
    SDL_RenderDebugText(renderer, rect.x + 15, rect.y + 15, this->label.c_str());
}
