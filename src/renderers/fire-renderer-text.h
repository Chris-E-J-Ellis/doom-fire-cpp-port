#pragma once

#include "fire-renderer.h"

namespace doom_fire::renderers
{
    class FireRendererText final : public IFireRenderer
    {
    public:
        ~FireRendererText() override = default;

        bool Init(const FireBuffer &buffer) override;
        void DeInit() override;
        void DrawBuffer(const FireBuffer &buffer) override;
        bool IsExitRequested() override;
        bool ProcessAdditionalArgs(int argc, char **argv) override;
        uint8_t GetMaxIgnitionValue() const override;
        void Wait() const override;
    };
}