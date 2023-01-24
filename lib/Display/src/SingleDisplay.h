#pragma once

#include "IDisplay.h"

namespace N2kGateway
{
    class SingleDisplay : public IDisplay
    {
        const char *_name;
        const char *_units;
        const double &_value;

    public:
        SingleDisplay(const char *name, const char *units, const double &value);
        void Begin();
        void Update();
    };
}
