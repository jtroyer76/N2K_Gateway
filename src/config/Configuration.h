#pragma once

#include <ArduinoJson.h>

#include <vector>
#include <string>
#include <unordered_map>

#include "CategoryType.h"

namespace N2kGateway
{
    using std::unordered_map;
    using std::vector;
    using std::string;

    class Configuration
    {
        vector<void (*)(CategoryType)> _listeners;
        JsonDocument *_config;

        void NotifyUpdate(CategoryType category);

    public:
        Configuration();
        const JsonDocument &Config() const;
        
        void Update(string json, CategoryType category);
        void Save();
        
        void RegisterListener(void (*)(CategoryType category));
    };
}