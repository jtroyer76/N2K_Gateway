#include "SingleDisplay.h"

#include <M5Core2.h>

#include "FreeSansBold90pt7b.h"
#include "FreeSansBold50pt7b.h"

// Display header locations
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

SingleDisplay::SingleDisplay(std::string name, std::string units, double &value) : value_(value)
{
    name_ = name;
    units_ = units;
}

void SingleDisplay::Show()
{
    // Draw header
    M5.Lcd.clear();
    M5.Lcd.setTextColor(TFT_WHITE);
    M5.Lcd.setFreeFont(FSSB12);
    M5.Lcd.drawString(name_.c_str(), NAME_X, NAME_Y);
    M5.Lcd.drawString(units_.c_str(), UNIT_X, UNIT_Y);

    Update();
}

void SingleDisplay::Update()
{
    // Split integer and decimal portions
    char buf[8];
    int num, dec;
    sprintf(buf, "%.1f", value_);
    sscanf(buf, "%d.%d", &num, &dec);

    // Use sprite to double buffer to avoid flashing
    TFT_eSprite read = TFT_eSprite(&M5.Lcd);
    read.createSprite(CANVAS_WIDTH, CANVAS_HEIGHT);

    // Draw value Single digit
    if (num < 10)
    {
        read.setFreeFont(&FreeSansBold90pt7b);
        read.drawNumber(num, SINGLE_X, SINGLE_Y);
    }

    // Draw value double digit
    else
    {
        read.setFreeFont(&FreeSansBold90pt7b);
        read.drawNumber(num, DOUBLE_X, DOUBLE_Y);
    }

    // Draw decimal portion
    if (num < 100)
    {
        read.setFreeFont(&FreeSansBold50pt7b);
        read.fillRect(DEC_X, DEC_Y, DEC_HEIGHT_WIDTH, DEC_HEIGHT_WIDTH, TFT_WHITE);
        read.drawNumber(dec, TENTHS_X, TENTHS_Y);
    }

    read.pushSprite(CANVAS_X, CANVAS_Y);
    read.deleteSprite();
}