#include "fire-engine.h"
#include "fire-palette.h"
#include "fire-renderer.h"
#include "fire-renderer-sdl.h"
#include "fire-renderer-text.h"

#include <iostream>

static constexpr int DefaultArgCount = 3;
static constexpr uint16_t DefaultWidth = 300;
static constexpr uint16_t DefaultHeight = 300;

namespace
{
    volatile bool keep_running = true;
    void sig_handler(int input)
    {
        (void)input;
        keep_running = false;
    }
}

using namespace doom_fire;
using namespace doom_fire::renderers;

int main(int argc, char **argv)
{
    const bool use_default_args = argc < DefaultArgCount;

    if (use_default_args)
    {
        printf("Insufficient arguments supplied, using default resolution: 300x300\n");
        printf("Usage: doom-fire [WIDTH] [HEIGHT]\n");
    }

    const uint16_t height = !use_default_args ? strtol(argv[2], nullptr, 10) : DefaultHeight;
    const uint16_t width = !use_default_args ? strtol(argv[1], nullptr, 10) : DefaultWidth;

    const doom_fire_palette_t palette = FirePalette::Get();
    FireRendererText textRenderer = FireRendererText();
    FireRendererSDL sdlRenderer = FireRendererSDL(palette);
    IFireRenderer &renderer = sdlRenderer;

    if (!renderer.ProcessAdditionalArgs(argc - DefaultArgCount, &argv[DefaultArgCount]))
    {
        printf("Unable to process additional arguments.");
        return 1;
    }

    const int ignition_value = renderer.GetMaxIgnitionValue();
    FireEngine fire_engine{width, height};
    fire_engine.InitBuffer(ignition_value);

    int init_success = renderer.Init(fire_engine.GetBuffer());
    if (!init_success)
        return 1;

    signal(SIGINT, sig_handler);

    while (keep_running)
    {
        if (renderer.IsExitRequested())
            keep_running = false;

        const auto &buffer = fire_engine.GetBuffer();
        renderer.DrawBuffer(buffer);
        fire_engine.StepFire();
        renderer.Wait();
    }

    renderer.DeInit();

    printf("Done...\n");

    return 0;
}
