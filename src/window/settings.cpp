#include "window/settings.h"
#include "core/httpclient.h"
#include <SDL3/SDL_log.h>
#include "widget/button.h"
#include "widget/layout/horizontal.h"
#include "widget/layout/vertical.h"

SettingsWindow::SettingsWindow() : Window("Settings", 400, 300, SDL_WINDOW_RESIZABLE,std::make_unique<HorizontalLayout>()) {
    auto button_test_1 = std::make_unique<Button>("Test1");
    button_test_1->setOnClick([this]() {
        auto res = HttpClient::instance().get("http://iposcoop.com/", [this](Response res) {
            if(res.code == 200){
                this->ok_count+=1;
            }
            SDL_Log("success %ld.", res.body.length());
        });
        SDL_Log("Ok Count: %d",this->ok_count);
    });

    auto button_test_2 = std::make_unique<Button>("Test2");
    button_test_2->setOnClick([]{
        SDL_Log("Test2 clicked");
    });
    auto button_test_3 = std::make_unique<Button>("Test3");
    button_test_3->setOnClick([]{
        SDL_Log("Test3 clicked");
    });
    auto subLayout = std::make_unique<VerticalLayout>();
    subLayout->addWidget(std::move(button_test_2));
    subLayout->addWidget(std::move(button_test_3));
    this->getLayout()->addWidget(std::move(button_test_1));
    this->getLayout()->addWidget(std::move(subLayout));
    this->resize();
}

void SettingsWindow::render(SDL_Renderer* renderer) {

}
void SettingsWindow::update(SDL_Event& event) {

}
