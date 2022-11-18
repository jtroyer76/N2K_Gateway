#include "DisplayController.h"
#include "SingleDisplay.h"
#include "StatusDisplay.h"

namespace N2kGateway
{
    DisplayController::DisplayController(const Configuration &config, const BoatData &data, const Status &status)
        : _currentScreen(0), _config(config), _data(data), _status(status)
    {
        ReLoad();
    }

    void DisplayController::ReLoad()
    {
        Serial.println("Loading display");
        JsonArrayConst conf = _config.Config()["display"];
        for (JsonObjectConst display : conf)
        {
            Serial.println("Checking type");
            const char *type = display["type"];
            if (strcmp(type, "SingleUnit") == 0)
            {
                Serial.println("Adding SingleUnit");
                Serial.println(display["name"].as<const char *>());
                Serial.println(display["unit"].as<const char *>());
                Serial.println(display["data"].as<const char *>());
                AddDisplay(new SingleDisplay(display["name"].as<const char *>(), display["unit"].as<const char *>(), _data.GetValue(display["data"].as<const char *>())));
            }
            else if(strcmp(type, "Status") == 0)
            {
                AddDisplay(new StatusDisplay(_status));
            }
        }
    }

    void DisplayController::AddDisplay(Display *display)
    {
        _screens.push_back(display);
    }

    void DisplayController::Show()
    {
        _screens[_currentScreen]->Show();
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

        _screens[_currentScreen]->Show();
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

        _screens[_currentScreen]->Show();
    }
}