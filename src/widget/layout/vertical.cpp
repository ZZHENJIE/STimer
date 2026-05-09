#include "widget/layout/vertical.h"
#include "SDL3/SDL_rect.h"

void VerticalLayout::calculate() {
    SDL_FRect content = this->Content();
    int count = 0;
    float margin_height = this->Margin() * (this->widgets.size() - 1);
    float average_height = (content.h - margin_height) / this->widgets.size();
    for(auto &widget : this->widgets) {
        float average_count_height = count * average_height;
        float margin_count_height = count * this->Margin();
        widget->setPosition(content.x, content.y + average_count_height + margin_count_height);
        widget->setSize(content.w, average_height);
        count++;
    }
}
