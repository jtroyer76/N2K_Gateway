#pragma once

namespace N2kGateway
{
    class IDisplay
    {
    public:
        virtual void Begin() = 0;
        virtual void Update() = 0;
    };
}