#pragma once

#include "fire-engine.h"
#include "fire-palette.h"

namespace doom_fire
{
    class IFireRenderer
    {
    public:
        virtual ~IFireRenderer() = default;

        virtual bool Init(const FireBuffer &buffer) = 0;
        virtual void DeInit() = 0;
        virtual void DrawBuffer(const FireBuffer &buffer) = 0;
        virtual bool IsExitRequested() = 0;
        virtual bool ProcessAdditionalArgs(int argc, char **argv) = 0;
        virtual uint8_t GetMaxIgnitionValue() const = 0;
        virtual void Wait() const = 0;
    };
}