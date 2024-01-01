#include "fire-renderer-sdl.h"
#include <cstdio>
#include <unistd.h>

using namespace doom_fire::renderers;

FireRendererSDL::FireRendererSDL(const FirePalette &palette)
    : _window(nullptr),
      _renderer(nullptr),
      _window_surface(nullptr),
      _buffer_surface(nullptr),
      _render_rect{},
      _fire_palette(palette)
{
}

bool FireRendererSDL::Init(const FireBuffer &buffer)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    SDL_CreateWindowAndRenderer(buffer.width, buffer.height, SDL_WINDOW_RESIZABLE, &_window, &_renderer);
    if (_window == nullptr)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    _window_surface = SDL_GetWindowSurface(_window);
    if (_window_surface == nullptr)
    {
        printf("Window surface could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    _buffer_surface = SDL_CreateRGBSurface(0, buffer.width, buffer.height, 32, 0, 0, 0, 0);
    if (_buffer_surface == nullptr)
    {
        printf("Buffer surface could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    SDL_GetWindowSize(_window, &_render_rect.w, &_render_rect.h);
    return true;
}

void FireRendererSDL::DeInit()
{
    SDL_FreeSurface(_buffer_surface);
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    _buffer_surface = nullptr;
    _renderer = nullptr;
    _window_surface = nullptr;
    _window = nullptr;

    SDL_Quit();
}

void FireRendererSDL::DrawBuffer(const FireBuffer &buffer)
{
    for (int y = 0; y < buffer.height; y++)
    {
        for (int x = 0; x < buffer.width; x++)
        {
            int pixel = buffer.data[x + (y * buffer.width)];
            int palette_index = pixel * 3;
            Uint8 r = _fire_palette.rgb_data[palette_index];
            Uint8 g = _fire_palette.rgb_data[palette_index + 1];
            Uint8 b = _fire_palette.rgb_data[palette_index + 2];

            auto *buffer_pixels = (Uint8 *)_buffer_surface->pixels;
            auto *target_pixel = (Uint32 *)(buffer_pixels + y * _buffer_surface->pitch + x * sizeof(Uint32));

            *target_pixel = r << 16 | g << 8 | b;
        }
    }

    SDL_BlitScaled(_buffer_surface, nullptr, _window_surface, &_render_rect);
    SDL_UpdateWindowSurface(_window);
}

uint8_t FireRendererSDL::GetMaxIgnitionValue() const
{
    return _fire_palette.size - 1;
}

bool FireRendererSDL::IsExitRequested()
{
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
            return true;

        // Seems like this can hang out here.
        if (e.type == SDL_WINDOWEVENT)
        {
            if (e.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                SDL_FreeSurface(_window_surface);
                _window_surface = SDL_GetWindowSurface(_window);
                SDL_GetWindowSize(_window, &_render_rect.w, &_render_rect.h);
            }
        }
    }
    return false;
}

bool FireRendererSDL::ProcessAdditionalArgs(int argc, char **argv)
{
    (void)argv;

    if (argc > 0)
        return false;

    return true;
}

void FireRendererSDL::Wait() const
{
    usleep(1000);
}