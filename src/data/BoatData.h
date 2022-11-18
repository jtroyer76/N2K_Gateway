#pragma once

namespace N2kGateway
{
    struct BoatData
    {
        unsigned long DaysSince1970 = 0; // Days since 1970-01-01
        double Heading = 0;
        double SOG = 0;
        double COG = 0;
        double STW = 0;
        double Variation = 0;
        double AWS = 0;
        double TWS = 0;
        double MaxAws = 0;
        double MaxTws = 0;
        double AWA = 0;
        double TWA = 0;
        double AWD = 0;
        double TWD = 0;
        double TripLog = 0;
        double Log = 0;
        double RudderPosition = 0;
        double WaterTemperature = 0;
        double WaterDepth = 0;
        double GPSTime = 0; // Secs since midnight,
        double Latitude = 0;
        double Longitude = 0;
        double Altitude = 0;
        double None = 0;

        const double &GetValue(const char *byName) const
        {
            if (strcmp(byName, "WaterDepth") == 0)
                return WaterDepth;

            if (strcmp(byName, "STW") == 0)
                return STW;

            return None;
        };
    };
}