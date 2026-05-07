#include "SDL3/SDL_video.h"
#include <SDL3/SDL.h>
#include <curl/curl.h>
#include <cstdio>

size_t write_callback(void* ptr, size_t size, size_t nmemb, void* stream) {
    size_t realsize = size * nmemb;
    printf("%.*s", (int)realsize, (char*)ptr);
    return realsize;
}

void send_curl_request() {
    CURL* curl = curl_easy_init();
    if (!curl) return;

    curl_easy_setopt(curl, CURLOPT_URL, "https://httpbin.org/get");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    printf("Sending request...\n");
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        printf("curl error: %s\n", curl_easy_strerror(res));
    }
    curl_easy_cleanup(curl);
}

int main(int argc, char* argv[]){

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("STimer", 800, 600, SDL_WINDOW_RESIZABLE);

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            } else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                printf("Mouse clicked, sending curl request...\n");
                send_curl_request();
            }
        }
        SDL_Delay(16);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
