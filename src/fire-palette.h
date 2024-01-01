#pragma once

#include <cstdint>

namespace doom_fire
{
    class FirePalette final
    {
    public:
        static const FirePalette &Get();

        const uint8_t * const rgb_data;
        const size_t size;
    };
}