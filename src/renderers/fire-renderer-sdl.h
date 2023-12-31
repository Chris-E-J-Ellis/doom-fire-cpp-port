#pragma once
#define SDL_MAIN_HANDLED

#include "SDL.h"
#include "fire-renderer.h"

namespace doom_fire::renderers
{
    class FireRendererSDL final : public IFireRenderer
    {
    public:
        explicit FireRendererSDL(const FirePalette &palette);
        ~FireRendererSDL() override = default;
        bool Init(const FireBuffer &buffer) override;
        void DeInit() override;
        void DrawBuffer(const FireBuffer &buffer) override;
        bool IsExitRequested() override;
        bool ProcessAdditionalArgs(int argc, char **argv) override;
        uint8_t GetMaxIgnitionValue() const override;
        void Wait() const override;

    private:
        SDL_Window *_window;
        SDL_Renderer *_renderer;
        SDL_Surface *_window_surface;
        SDL_Surface *_buffer_surface;
        SDL_Rect _render_rect;
        const FirePalette &_fire_palette;
    };
}