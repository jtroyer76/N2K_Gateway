#ifndef _SingleDisplay_H_
#define _SingleDisplay_H_

#include "Display.h"

#include <Arduino.h>

class SingleDisplay : public Display
{
    public:
        SingleDisplay(String name, String units,  double &value);
        void Show();
        void Update();

    private:
      String name_;
      String units_;
      double &value_;
};

#endif // _SingleDisplay_H_