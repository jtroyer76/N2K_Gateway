#include "DisplayConfig.h"

#include "esp32-hal-log.h"
#include "LittleFS.h"

namespace N2kGateway
{
    using namespace std;

    DisplayConfig::DisplayConfig(const char *fileName) : _fileName(fileName), _configs(vector<DisplayConfigItem>())
    {
        Load();
    }

    const vector<DisplayConfigItem> &DisplayConfig::Items() const
    {
        return _configs;
    }

    void DisplayConfig::Load()
    {
        if (!LittleFS.exists(_fileName))
        {
            LoadDefaults();
            return;
        }

        Clear();

        // ifstream fin(_fileName, ios::in | ios::binary);
        auto fin = LittleFS.open(_fileName);
        DisplayConfigItem item = DisplayConfigItem();
        while (fin.read((uint8_t *)&item, sizeof(DisplayConfigItem)))
        {
            _configs.push_back(item);
        }
        fin.close();
    }

    void DisplayConfig::LoadDefaults()
    {
        _configs.push_back(DisplayConfigItem{
            DisplayType::Status,
        });

        Save(true);
    }

    void DisplayConfig::Save(bool create)
    {
        auto fout = LittleFS.open(_fileName, "w+", create);
        for (DisplayConfigItem config : _configs)
        {
            fout.write((uint8_t *)&config, sizeof(DisplayConfigItem));
        }
        fout.close();
    }

    void DisplayConfig::Add(DisplayConfigItem config)
    {
        _configs.push_back(config);
    }

    void DisplayConfig::Clear()
    {
        _configs.clear();
    }
}