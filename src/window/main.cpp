#include "window/main.h"
#include <SDL3/SDL_log.h>
#include "core/application.h"
#include "widget/layout/horizontal.h"
#include "window/settings.h"

MainWindow::MainWindow() : Window("STimer", 800, 600, SDL_WINDOW_RESIZABLE,std::make_unique<HorizontalLayout>()) {
    addWindow(std::make_unique<SettingsWindow>());
    this->resize();
}

void MainWindow::render(SDL_Renderer* renderer) {

}

void MainWindow::update(SDL_Event& event) {
    if(event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        SDL_Log("Main");
    }
    if(event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED){
        Application::quit();
    }
}
