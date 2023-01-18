#pragma once

#include "WString.h"

namespace N2kGateway
{
    class ConfigurationItem
    {
        String name;
        String value;
        String defaultValue;
        bool secret = false;
    };
}