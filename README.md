## MinGW (.clang)
```yaml
CompileFlags:
  Add:
    - --target=x86_64-w64-windows-gnu
```

## Build

1. ThirdParty Installation
  * [SDL3](https://github.com/libsdl-org/SDL/releases)
  * [SDL3_image](https://github.com/libsdl-org/SDL_image/releases)
  * [SDL3_ttf](https://github.com/libsdl-org/SDL_ttf/releases)
  * [SDL3_mixer](https://github.com/libsdl-org/SDL_mixer/releases)
  * [Libcurl](https://curl.se/download.html)

2. Macos
```bash
brew install curl
```

3. Build 命令
```bash
mkdir build && cd build && cmake .. && cmake --build .
```
