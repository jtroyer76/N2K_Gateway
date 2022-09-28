#ifndef _DisplayController_H_
#define _DisplayController_H_

#include "Display.h"

#include <vector>

class DisplayController
{    
public:
    DisplayController();
    void Show();
    void Update();
    void AddDisplay(Display* display);
    void NextScreen();
    void PreviousScreen();

private:
    std::vector<Display*> _screens {};
    std::vector<Display*>::size_type _currentScreen;
};
#endif // _DisplayController_H_