#pragma once

#include <ArduinoJson.h>
#include "WString.h"

#include <vector>
#include <unordered_map>

#include "CategoryType.h"

namespace N2kGateway
{
    using std::unordered_map;
    using std::vector;

    class Configuration
    {
        vector<void (*)(CategoryType)> _listeners;
        JsonDocument *_config;

        void NotifyUpdate(CategoryType category);
        void Load();

    public:
        Configuration();
        const JsonDocument &Config() const;
        
        void Update(String json, CategoryType category);
        void Save();
        
        void RegisterListener(void (*)(CategoryType category));
    };
}