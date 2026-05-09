#pragma once

#include "widget.h"
#include <memory>
#include <vector>

class Layout : public Widget{
private:
    float padding;
    float margin;
protected:
    std::vector<std::unique_ptr<Widget>> widgets;
public:
    virtual ~Layout() = default;
    virtual void calculate() = 0;
public:
    Layout();
    void resize(int width, int height);
    void update(SDL_Event& event) override;
    void render(SDL_Renderer* renderer) override;
    void setPadding(float padding);
    float Padding() const;
    void setMargin(float margin);
    float Margin() const;
    SDL_FRect Content() const;
    template<typename T>
    void addWidget(std::unique_ptr<T> widget){
        widgets.push_back(std::move(widget));
    }
};
