#include "DisplayFactory.h"

#ifdef ARDUINO_M5STACK_Core2
#include "SingleDisplay.h"
#include "StatusDisplay.h"
#include "esp32-hal-log.h"
#endif 

namespace N2kGateway
{
    IDisplay *DisplayFactory::GetDisplay(const DisplayConfigItem &config, const BoatData &data, const Status &status)
    {
        switch (config.Type)
        {

#ifdef ARDUINO_M5STACK_Core2
        case DisplayType::SingleDisplay:
            return new SingleDisplay(config.Description, config.Units, data.GetValue(config.DataType));

        case DisplayType::Status:
            return new StatusDisplay(status);
#endif

        default:
            return nullptr;
        }
    }
}