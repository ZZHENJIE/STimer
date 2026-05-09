#include "SDL3/SDL_events.h"
#include "SDL3/SDL_video.h"
#include "SDL3/SDL_render.h"
#include "core/window.h"
#include <memory>

void Window::_render(){
    for (auto &window : windows){
        window->_render();
    }
    this->layout->render(this->renderer_ptr.get());
    this->render(this->renderer_ptr.get());
    SDL_RenderPresent(this->renderer_ptr.get());
}

void Window::resize(){
    int width,height;
    SDL_GetWindowSize(this->window_ptr.get(), &width, &height);
    this->layout->resize(width, height);
}

void Window::_update(SDL_Event& event){
    SDL_WindowID event_window_id = event.window.windowID;
    if(event_window_id == this->window_id){
        if(event.type == SDL_EVENT_WINDOW_RESIZED){
            this->resize();
        }
        this->layout->update(event);
        this->update(event);
    }else{
        for (auto &window : windows){
            if(event_window_id == window->window_id){
                window->_update(event);
            }
        }
    }
}

Layout* Window::getLayout() const{
    return this->layout.get();
}
