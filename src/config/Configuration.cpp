#include "Configuration.h"
#include "DefaultConfig.h"

namespace N2kGateway
{
    Configuration::Configuration()
    {
        _config = new StaticJsonDocument<1000>();

        // Deserialize the JSON document
        DeserializationError error = deserializeJson(*_config, default_config);

        // Test if parsing succeeds.
        if (error)
        {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.f_str());
            return;
        }
    }

    const JsonDocument &Configuration::Config() const
    {
        return *_config;
    }

    void Configuration::Update(string json, CategoryType category)
    {

    }          

    void Configuration::Save()
    {
    }

    void Configuration::NotifyUpdate(CategoryType category)
    {
        for(void (*callback)(CategoryType) : _listeners)
        {
            callback(category);
        }
    }

    void Configuration::RegisterListener(void (*callback)(CategoryType))
    {
        _listeners.push_back(callback);
    }
}