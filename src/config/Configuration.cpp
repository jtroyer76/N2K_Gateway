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

    const JsonDocument &Configuration::Config()
    {
        return *_config;
    }

    void Configuration::Save()
    {
    }

    void Configuration::NotifyUpdate(vector<ConfigCategory> categories)
    {
        for(void (*callback)(vector<ConfigCategory>) : _listeners)
        {
            callback(categories);
        }
    }

    void Configuration::RegisterListener(void (*callback)(vector<ConfigCategory>))
    {
        _listeners.push_back(callback);
    }
}