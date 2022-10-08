#pragma once

namespace N2kGateway
{
    class Display
    {
    public:
        virtual void Show() = 0;
        virtual void Update() = 0;
    };
}