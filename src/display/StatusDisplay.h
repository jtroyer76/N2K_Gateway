#pragma once

#include "Display.h"
#include "data\Status.h"

namespace N2kGateway
{
    class StatusDisplay : public Display
    {
        const Status &_status;

    public:
        StatusDisplay(const Status &status);
        void Show();
        void Update();
    };
}
