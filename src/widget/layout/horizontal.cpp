#include "widget/layout/horizontal.h"
#include "SDL3/SDL_rect.h"

void HorizontalLayout::calculate() {
    SDL_FRect content = this->Content();
    int count = 0;
    float margin_width = this->Margin() * (this->widgets.size() - 1);
    float average_width = (content.w - margin_width) / this->widgets.size();
    for(auto &widget : this->widgets) {
        float average_count_width = count * average_width;
        float margin_count_width = count * this->Margin();
        widget->setPosition(content.x + average_count_width + margin_count_width, content.y);
        widget->setSize(average_width, content.h);
        count++;
    }
}
