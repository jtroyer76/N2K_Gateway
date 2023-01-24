#pragma once

#include "IDisplay.h"
#include "DisplayConfig.h"
#include "BoatData.h"
#include "Status.h"

#include <vector>

namespace N2kGateway
{
    using std::vector;

    class DisplayController
    {
        const DisplayConfig &_config;
        const BoatData &_data;
        const Status &_status;
        vector<IDisplay *> _screens;
        vector<IDisplay *>::size_type _currentScreen;

    public:
        DisplayController(const DisplayConfig &config, const BoatData &data, const Status &status);
        void Begin();
        void Update();
        void AddDisplay(IDisplay *display);
        void NextScreen();
        void PreviousScreen();
        void ReLoad();
    };
}