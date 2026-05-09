#include "window/main.h"
#include "core/application.h"

int main(int argc, char* argv[]){
    Application::init();

    Application app(std::make_unique<MainWindow>());

    app.run();

    return Application::cleanup();
}
