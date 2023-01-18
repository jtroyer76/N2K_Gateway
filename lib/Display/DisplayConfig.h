#pragma once

#include <vector>
#include <array>
#include <cstdint>

#include "BoatData.h"

namespace N2kGateway
{
    using namespace std;

    enum class DisplayType : uint8_t
    {
        Status,
        SingleDisplay,
    };

    struct DisplayConfigItem
    {
        DisplayType Type;
        BoatDataType DataType;
        char Description[20];
        char Units[10];
    };

    static_assert(sizeof(DisplayConfigItem) == 32);
    static_assert(is_standard_layout<DisplayConfigItem>::value);

    class DisplayConfig
    {
        const char *_fileName;
        vector<DisplayConfigItem> _configs;

        void Clear();
        void LoadDefaults();

    public:
        DisplayConfig(const char *fileName);

        const vector<DisplayConfigItem> &Items() const;

        void Add(DisplayConfigItem config);
        void Load();
        void Save(bool create);
    };
}