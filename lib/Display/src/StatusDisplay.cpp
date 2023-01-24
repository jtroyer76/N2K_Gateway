#include "StatusDisplay.h"

#include "Platform.h"

namespace N2kGateway
{
    StatusDisplay::StatusDisplay(const Status &status) : _status(status)
    {
    }

    void StatusDisplay::Begin()
    {
        Platform::StatusDisplay_Begin();        
        Update();
    }

    void StatusDisplay::Update()
    {
        Platform::StatusDisplay_Update(_status);
    }
}
