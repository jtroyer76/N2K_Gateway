#ifdef ARDUINO_M5STACK_Core2

#include "StatusDisplay.h"

#include <M5Core2.h>

#include "Free_Fonts.h"

//#include "FreeSansBold90pt7b.h"
//#include "FreeSansBold50pt7b.h"

// IDisplay header locations
#define NAME_X 10
#define NAME_Y 10
#define UNIT_X 270
#define UNIT_Y 10

// Canvas size
#define CANVAS_WIDTH 320
#define CANVAS_HEIGHT 200

// Location to draw canvas on screen
#define CANVAS_X 0
#define CANVAS_Y 40

// Location to start value if single digit
#define SINGLE_X 105
#define SINGLE_Y 30

// Location to start valu if double digits
#define DOUBLE_X 10
#define DOUBLE_Y 30

// Dimension of decimal point
#define DEC_HEIGHT_WIDTH 10
#define DEC_X 210
#define DEC_Y 150

// Location of tenths digit
#define TENTHS_X 240
#define TENTHS_Y 85

namespace N2kGateway
{
    StatusDisplay::StatusDisplay(const Status &status) : _status(status)
    {
    }

    void StatusDisplay::Begin()
    {
        // Draw header
        M5.Lcd.clear();
        M5.Lcd.setTextColor(TFT_WHITE);
        M5.Lcd.setFreeFont(FSSB12);
        M5.Lcd.drawString("Status", NAME_X, NAME_Y);

        Update();
    }

    void StatusDisplay::Update()
    {
        M5.Lcd.drawString("Wifi:", 10, 50);
        M5.Lcd.drawString(_status.IpAddress, 65, 50);
    }
}
#endif