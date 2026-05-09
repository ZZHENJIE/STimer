#pragma once

#include "window.h"

class Application {
private:
    std::unique_ptr<Window> main_window;
public:
    template<typename T>
    Application(std::unique_ptr<T> main_window): main_window(std::move(main_window)) {}

    ~Application() = default;

    void run();

    static void init();

    static int cleanup();

    static void quit();
};
