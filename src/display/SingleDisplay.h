#pragma once

#include "Display.h"
#include <string>

namespace N2kGateway
{
    using std::string;

    class SingleDisplay : public Display
    {
        string name_;
        string units_;
        double &value_;

    public:
        SingleDisplay(string name, string units, double &value);
        void Show();
        void Update();
    };
}