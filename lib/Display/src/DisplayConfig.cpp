#include "DisplayConfig.h"

#include "HalFs.h"

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
        if (!Hal::FsExists(_fileName))
        {
            LoadDefaults();
            return;
        }

        Clear();

        auto fin = Hal::FsOpen(_fileName, "r", false);
        DisplayConfigItem item = DisplayConfigItem();
        while (fin->Read((uint8_t *)&item, sizeof(DisplayConfigItem)))
        {
            _configs.push_back(item);
        }
        fin->Close();
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
        auto fout = Hal::FsOpen(_fileName, "w+", create);
        for (DisplayConfigItem config : _configs)
        {
            fout->Write((uint8_t *)&config, sizeof(DisplayConfigItem));
        }
        fout->Close();
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