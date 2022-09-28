#include "DisplayController.h"

DisplayController::DisplayController() :
    _currentScreen(0) {}

void DisplayController::AddDisplay(Display* display)
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
    if(_screens.size() == 1)
        return;

    _currentScreen++;
    if(_currentScreen > _screens.size() - 1) {
        _currentScreen = 0;
    }

    _screens[_currentScreen]->Show();
}

void DisplayController::PreviousScreen()
{
    if(_screens.size() == 1)
        return;
        
    if(_currentScreen == 0) {
        _currentScreen = _screens.size() - 1;
    } 
    else {
        _currentScreen--;
    }  

    _screens[_currentScreen]->Show();
}