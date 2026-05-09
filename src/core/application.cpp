#include <SDL3/SDL_init.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_timer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "core/application.h"
#include "core/httpclient.h"
#include "curl/curl.h"

void Application::init(){
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

int Application::cleanup(){
    SDL_Quit();
    TTF_Quit();
    curl_global_cleanup();
    return 0;
}

void Application::run(){
    bool running = true;
    while (running) {
        SDL_Event event{};
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_EVENT_QUIT){
                running = false;
            }
            this->main_window->_update(event);
        }
        this->main_window->_render();
        HttpClient::instance().poll();
        SDL_Delay(16);
    }
}

void Application::quit() {
    SDL_Event quitEvent{SDL_EVENT_QUIT};
    SDL_PushEvent(&quitEvent);
}
