#include "SingleDisplay.h"
#include "Platform.h"

namespace N2kGateway
{
    SingleDisplay::SingleDisplay(const char *name, const char *units, const double &value) : _name(name), _units(units), _value(value)
    {
    }

    void SingleDisplay::Begin()
    {
        Platform::SingleDisplay_Begin(_name, _units);
        Update();
    }

    void SingleDisplay::Update()
    {
        Platform::SingleDisplay_Update(_name, _units, _value);
    }
}