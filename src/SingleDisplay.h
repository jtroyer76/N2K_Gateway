#ifndef _SingleDisplay_H_
#define _SingleDisplay_H_

#include "Display.h"

#include <string>

class SingleDisplay : public Display
{
    public:
        SingleDisplay(std::string name, std::string units,  double &value);
        void Show();
        void Update();

    private:
      std::string name_;
      std::string units_;
      double &value_;
};

#endif // _SingleDisplay_H_