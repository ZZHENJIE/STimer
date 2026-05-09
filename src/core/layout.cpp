#include "core/layout.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_rect.h"
#include "core/widget.h"

Layout::Layout():padding(10), margin(10){

}

SDL_FRect Layout::Content() const{
    SDL_FRect content = {
        this->x + this->padding,
        this->y + this->padding,
        this->width - 2 * this->padding,
        this->height - 2 * this->padding
    };
    return content;
}

float Layout::Padding() const{
    return this->padding;
}

float Layout::Margin() const{
    return this->margin;
}

void Layout::setMargin(float margin){
    this->margin = margin;
}

void Layout::setPadding(float padding){
    this->padding = padding;
}

void Layout::resize(int width, int height){
    this->setSize(width, height);
    this->calculate();
    for (auto& widget : widgets) {
        auto* layout = dynamic_cast<Layout*>(widget.get());
        if (layout) {
            layout->calculate();
        }
    }
}

void Layout::update(SDL_Event& event) {
    if(this->visible) {
        const SDL_FPoint mouse_pos = { event.button.x, event.button.y };
        for (auto &widget : widgets){
            const SDL_FRect widget_rect = widget->getRect();
            if(SDL_PointInRectFloat(&mouse_pos, &widget_rect)){
                widget->update(event);
            }
        }
    }
}

void Layout::render(SDL_Renderer* renderer){
    if(this->visible) {
        for (auto &widget : widgets){
            widget->render(renderer);
        }
        SDL_FRect rect = this->getRect();
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderRect(renderer, &rect);
    }
}
