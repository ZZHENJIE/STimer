#include "core/application.h"
#include "imgui/imgui.h"
#include <SDL3/SDL_log.h>
#include <cstddef>

Application::Application(){

}

Application::~Application(){

}

void Application::render(){
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Tool"))
        {
            if (ImGui::MenuItem("Show Demo Window", nullptr,this->app_menu_open.show_demo_window)) {
                this->app_menu_open.show_demo_window = !this->app_menu_open.show_demo_window;
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", nullptr)) {
                SDL_Log("Clicked Undo.");
            }
            if (ImGui::MenuItem("Redo", nullptr)) {}
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", nullptr)) {}
            if (ImGui::MenuItem("Copy", nullptr)) {}
            if (ImGui::MenuItem("Paste", nullptr)) {}
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
    if (this->app_menu_open.show_demo_window) {
        ImGui::ShowDemoWindow(&this->app_menu_open.show_demo_window);
    }
    if(ImGui::Begin("Main")){

        ImGui::End();
    }
}
