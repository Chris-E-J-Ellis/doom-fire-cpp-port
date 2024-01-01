#pragma once

#include <cstdint>

namespace doom_fire
{
    struct FireBuffer
    {
        uint16_t height;
        uint16_t width;
        uint8_t *data;
    };

    class FireEngine final
    {
    public:
        explicit FireEngine(uint16_t width, uint16_t height);
        ~FireEngine();

        void Init(uint8_t ignition_value) const;
        void StepFire() const;
        const FireBuffer &GetBuffer() const;

    private:
        FireBuffer _buffer;

        void SpreadFire(uint32_t source_position) const;
    };
}