#pragma once

#include "IDisplay.h"
#include "Status.h"

namespace N2kGateway
{
    class StatusDisplay : public IDisplay
    {
        const Status &_status;

    public:
        StatusDisplay(const Status &status);
        void Begin();
        void Update();
    };
}
