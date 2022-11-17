#pragma once

#include "Display.h"
#include "config\Configuration.h"
#include "boatdata.h"
#include "data\Status.h"

#include <vector>

namespace N2kGateway
{
    using std::vector;

    class DisplayController
    {
        const Configuration &_config;
        const tBoatData &_data;
        const Status &_status;
        vector<Display *> _screens;
        vector<Display *>::size_type _currentScreen;

    public:
        DisplayController(const Configuration &config, const tBoatData &data, const Status &status);
        void Show();
        void Update();
        void AddDisplay(Display *display);
        void NextScreen();
        void PreviousScreen();
        void ReLoad();
    };
}