#pragma once

struct AppMenuOpen {
    bool show_demo_window = false;
    bool show_settings_window = false;
};

class Application {
private:
    AppMenuOpen app_menu_open;
public:
    Application();
    ~Application();
    void render();
};
