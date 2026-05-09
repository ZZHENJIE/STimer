#pragma once

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_video.h"
#include "SDL3/SDL_render.h"
#include "layout.h"
#include <memory>
#include <vector>

class Window{
    friend class Application;
private:
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window_ptr;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer_ptr;
    SDL_WindowID window_id;
    std::vector<std::unique_ptr<Window>> windows;
    std::unique_ptr<Layout> layout;
private:
    void _render();
    void _update(SDL_Event& event);
public:
    template<typename T>
     Window(const char *title, int w, int h, SDL_WindowFlags flags, std::unique_ptr<T> layout)
        : window_ptr(SDL_CreateWindow(title, w, h, flags), SDL_DestroyWindow),
            renderer_ptr(SDL_CreateRenderer(window_ptr.get(), nullptr), SDL_DestroyRenderer),
            layout(std::move(layout)) {
        window_id = SDL_GetWindowID(window_ptr.get());
    }
    virtual ~Window() = default;
    virtual void render(SDL_Renderer* renderer) = 0;
    virtual void update(SDL_Event& event) = 0;
public:
    template<typename T>
    void addWindow(std::unique_ptr<T> window){
        windows.push_back(std::move(window));
    }

    Layout* getLayout() const;
    void resize();
};
