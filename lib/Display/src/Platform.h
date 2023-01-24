#pragma once

#include "BoatData.h"
#include "Status.h"

namespace N2kGateway
{
    namespace Platform
    {
        void SingleDisplay_Begin(const char *name, const char *units);
        void SingleDisplay_Update(const char *name, const char *units, const double &value);

        void StatusDisplay_Begin();
        void StatusDisplay_Update(const Status &status);
    }
}