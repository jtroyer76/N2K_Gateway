#pragma once

#include "Display.h"
#include "Settings.h"

#include <vector>

namespace N2kGateway
{
    using std::vector;

    class DisplayController
    {
        const Settings &_settings;
        vector<Display *> _screens{};
        vector<Display *>::size_type _currentScreen;

    public:
        DisplayController(const Settings &settings);
        void Show();
        void Update();
        void AddDisplay(Display *display);
        void NextScreen();
        void PreviousScreen();
    };
}