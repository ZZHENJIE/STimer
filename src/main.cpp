// Dear ImGui: SDL3 + SDL_Renderer 示例应用

#include "core/application.h"
#include "core/httpclient.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl3.h"
#include "imgui/imgui_impl_sdlrenderer3.h"
#include <SDL3/SDL_log.h>
#include <cstddef>
#include <curl/curl.h>
#include <stdio.h>
#include <SDL3/SDL.h>

#ifdef __EMSCRIPTEN__
#include "../libs/emscripten/emscripten_mainloop_stub.h"
#endif

int main(int, char**)
{
    // 初始化 SDL
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD))
    {
        printf("Error: SDL_Init(): %s\n", SDL_GetError());
        return 1;
    }

    curl_global_init(CURL_GLOBAL_DEFAULT);

    // 创建窗口和渲染器
    float main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
    SDL_WindowFlags window_flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN | SDL_WINDOW_HIGH_PIXEL_DENSITY;
    SDL_Window* window = SDL_CreateWindow("Dear ImGui SDL3+SDL_Renderer example", (int)(1280 * main_scale), (int)(800 * main_scale), window_flags);
    if (window == nullptr)
    {
        printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
        return 1;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
    SDL_SetRenderVSync(renderer, 1);
    if (renderer == nullptr)
    {
        SDL_Log("Error: SDL_CreateRenderer(): %s\n", SDL_GetError());
        return 1;
    }
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_ShowWindow(window);

    // 初始化 ImGui 上下文
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // 启用键盘控制
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // 启用 docking

    // 主题风格
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsLight();

    // 缩放设置
    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(main_scale);
    style.FontScaleDpi = main_scale;

    // 初始化平台/渲染器后端
    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);

    // 字体设置（取消注释启用）
    // - 如果没有显式加载字体，ImGui 会选择内置字体
    // - 可以加载多个字体，使用 PushFont()/PopFont() 选择
    // - 如果文件无法加载，AddFont 函数会返回 nullptr
    // - 注意：如果要在字符串中包含反斜杠，需要写成 \\
    // style.FontSizeBase = 20.0f;  // 设置基础字体大小
    // io.Fonts->AddFontDefaultVector();  // 使用默认矢量字体
    // io.Fonts->AddFontDefaultBitmap();  // 使用默认位图字体
    // io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 16.0f);  // 加载自定义字体
    // ImFont* font = io.Fonts->AddFontFromFileTTF("font.ttf", 16.0f);
    // IM_ASSERT(font != nullptr);

    // 状态变量
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    Application app;

    // 主循环
    bool done = false;
#ifdef __EMSCRIPTEN__
    io.IniFilename = nullptr;
    EMSCRIPTEN_MAINLOOP_BEGIN
#else
    while (!done)
#endif
    {
        // 处理事件
        // 可以通过 io.WantCaptureMouse 和 io.WantCaptureKeyboard 判断 ImGui 是否需要处理输入
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT)
                done = true;
            if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED && event.window.windowID == SDL_GetWindowID(window))
                done = true;
        }

        if (SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED)
        {
            SDL_Delay(10);
            continue;
        }

        // 开始 ImGui 帧
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        ImGuiViewport* viewport = ImGui::GetMainViewport();

        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);

        ImGui::Begin("Main", nullptr,
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoBringToFrontOnFocus
        );

        ImGui::DockSpaceOverViewport();

        ImGui::End();

        app.render();

        // 渲染
        ImGui::Render();
        HttpClient::instance().poll();
        SDL_SetRenderScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
        SDL_SetRenderDrawColorFloat(renderer, clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        SDL_RenderClear(renderer);
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
        SDL_RenderPresent(renderer);
    }
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_MAINLOOP_END;
#endif

    // 清理
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    curl_global_cleanup();
    SDL_Quit();

    return 0;
}
