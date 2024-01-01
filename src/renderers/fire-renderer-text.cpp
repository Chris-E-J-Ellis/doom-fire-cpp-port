#include "fire-renderer-text.h"

#include <cstdio>
#include <unistd.h>

namespace
{
    constexpr char TextPalette[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
}

using namespace doom_fire::renderers;

bool FireRendererText::Init(const FireBuffer &buffer)
{
    (void)buffer;
    return true;
}

void FireRendererText::DeInit()
{
}

void FireRendererText::DrawBuffer(const FireBuffer &buffer)
{
    for (int y = 0; y < buffer.height; ++y)
    {
        for (int x = 0; x < buffer.width; ++x)
        {
            const size_t buffer_position = x + (y * buffer.width);
            const uint8_t pixel = buffer.data[buffer_position] % sizeof(TextPalette);
            const char pixel_char = TextPalette[pixel];
            printf("%c", pixel_char);
        }
        printf("\n");
    }
    printf("\n");
}

uint8_t FireRendererText::GetMaxIgnitionValue() const
{
    return sizeof(TextPalette) - 1;
}

bool FireRendererText::IsExitRequested()
{
    return false;
}

bool FireRendererText::ProcessAdditionalArgs(int argc, char **argv)
{
    (void)argv;

    if (argc > 0)
        return false;

    return true;
}

void FireRendererText::Wait() const
{
    usleep(1000000);
}
