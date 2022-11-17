#pragma once

#include "Display.h"
#include "WString.h"

namespace N2kGateway
{
    class SingleDisplay : public Display
    {
        const char *_name;
        const char *_units;
        const double &_value;

    public:
        SingleDisplay(const char *name, const char *units, const double &value);
        void Show();
        void Update();
    };
}