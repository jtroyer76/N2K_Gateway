#include "DisplayController.h"
#include "DisplayFactory.h"

#include "esp32-hal-log.h"

namespace N2kGateway
{
    DisplayController::DisplayController(const DisplayConfig &config, const BoatData &data, const Status &status)
        : _currentScreen(0), _config(config), _data(data), _status(status)
    {
        ReLoad();
    }

    void DisplayController::ReLoad()
    {
        for (auto &display : _config.Items())
        {
            AddDisplay(DisplayFactory::GetDisplay(display, _data, _status));
        }
        log_d("Loaded %d configs", _config.Items().size());
    }

    void DisplayController::AddDisplay(IDisplay *display)
    {
        _screens.push_back(display);
    }

    void DisplayController::Begin()
    {
        _screens[_currentScreen]->Begin();
    }

    void DisplayController::Update()
    {
        _screens[_currentScreen]->Update();
    }

    void DisplayController::NextScreen()
    {
        if (_screens.size() == 1)
            return;

        _currentScreen++;
        if (_currentScreen > _screens.size() - 1)
        {
            _currentScreen = 0;
        }

        _screens[_currentScreen]->Begin();
    }

    void DisplayController::PreviousScreen()
    {
        if (_screens.size() == 1)
            return;

        if (_currentScreen == 0)
        {
            _currentScreen = _screens.size() - 1;
        }
        else
        {
            _currentScreen--;
        }

        _screens[_currentScreen]->Begin();
    }
}