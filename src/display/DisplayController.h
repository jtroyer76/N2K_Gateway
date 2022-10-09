#pragma once

#include "Display.h"
#include "config\Configuration.h"

#include <vector>

namespace N2kGateway
{
    using std::vector;

    class DisplayController
    {
        const Configuration &_config;
        vector<Display *> _screens;
        vector<Display *>::size_type _currentScreen;

    public:
        DisplayController(const Configuration &config);
        void Show();
        void Update();
        void AddDisplay(Display *display);
        void NextScreen();
        void PreviousScreen();
    };
}