#pragma once

#include <ArduinoJson.h>

#include <vector>
#include <string>
#include <unordered_map>

#include "ConfigCategory.h"

namespace N2kGateway
{
    using std::unordered_map;
    using std::vector;

    class Configuration
    {
        vector<void (*)(vector<ConfigCategory>)> _listeners;
        JsonDocument *_config;

    public:
        Configuration();
        const JsonDocument &Config();
        void Save();
        void NotifyUpdate(vector<ConfigCategory> categories);
        void RegisterListener(void (*)(vector<ConfigCategory>));
    };
}