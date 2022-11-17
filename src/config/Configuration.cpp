#include "Configuration.h"
#include "DefaultConfig.h"
#include <LittleFS.h>

namespace N2kGateway
{
    Configuration::Configuration()
    {
        Load();
    }

    void Configuration::Load()
    {
        File file = LittleFS.open("/settings.json");
        _config = new StaticJsonDocument<1000>();

        // Load the default config
        DeserializationError error = deserializeJson(*_config, file);

        // Test if parsing succeeds.
        if (error)
        {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.f_str());
            return;
        }

        file.close();
    }

    void Configuration::Save()
    {
        File file = LittleFS.open("/settings.json", FILE_WRITE);
        if (!file)
        {
            Serial.println(F("Failed to open file"));
            return;
        }

        // Serialize JSON to file
        if (serializeJson(*_config, file) == 0)
        {
            Serial.println(F("Failed to write to file"));
        }

        file.close();
    }

    const JsonDocument &Configuration::Config() const
    {
        return *_config;
    }

    void Configuration::Update(String json, CategoryType category)
    {
    }

    void Configuration::NotifyUpdate(CategoryType category)
    {
        for (void (*callback)(CategoryType) : _listeners)
        {
            callback(category);
        }
    }

    void Configuration::RegisterListener(void (*callback)(CategoryType))
    {
        _listeners.push_back(callback);
    }
}