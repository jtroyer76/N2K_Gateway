#include "IDisplay.h"
#include "DisplayConfig.h"
#include "Status.h"

namespace N2kGateway
{
    class DisplayFactory
    {
    public:
        static IDisplay *GetDisplay(const DisplayConfigItem &config, const BoatData &data, const Status &status);
    };
}