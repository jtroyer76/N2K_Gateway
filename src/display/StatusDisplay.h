#pragma once

#include "Display.h"

namespace N2kGateway
{
    class StatusDisplay : public Display
    {
    public:
        void Show();
        void Update();
    };
}
