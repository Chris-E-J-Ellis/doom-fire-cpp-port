#pragma once

#include <cstdint>

namespace doom_fire
{
    typedef struct
    {
        const uint8_t *rgb_data;
        size_t size;
    } doom_fire_palette_t;

    class FirePalette final
    {
    public:
        static const doom_fire_palette_t &Get();
    };
}