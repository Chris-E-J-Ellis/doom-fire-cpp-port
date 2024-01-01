#include "fire-engine.h"

#include <cstdlib>
#include <ctime>

using namespace doom_fire;

FireEngine::FireEngine(uint16_t width, uint16_t height)
    : _buffer{}
{
    const size_t buffer_size = width * height;
    _buffer = {.height = height,
               .width = width,
               .data = new uint8_t[buffer_size]};
}

FireEngine::~FireEngine()
{
    delete _buffer.data;
    _buffer.data = nullptr;
}

void FireEngine::Init(uint8_t ignition_value) const
{
    srand(time(nullptr));

    for (int i = 0; i < _buffer.height * _buffer.width; i++)
    {
        _buffer.data[i] = 0;
    }

    for (int i = (_buffer.height - 1) * _buffer.width; i < _buffer.height * _buffer.width; i++)
    {
        _buffer.data[i] = ignition_value;
    }
}

void FireEngine::StepFire() const
{
    for (int x = 0; x < _buffer.width; x++)
    {
        for (int y = 1; y < _buffer.height; y++)
        {
            const uint32_t buffer_position = (y * _buffer.width) + x;
            SpreadFire(buffer_position);
        }
    }
}

const FireBuffer &FireEngine::GetBuffer() const
{
    return _buffer;
}

void FireEngine::SpreadFire(uint32_t source_position) const
{
    const int pixel = _buffer.data[source_position];

    if (pixel <= 0)
    {
        _buffer.data[source_position - _buffer.width] = 0;
    }
    else
    {
        const int decay = rand() & 3;
        const int destination_position = ((int)source_position - _buffer.width) - decay + 1;
        if (destination_position < 0)
            return;

        _buffer.data[destination_position] = pixel - (decay & 1);
    }
}