#pragma once

#include <cstring>
#include <cstdint>
#include <map>

namespace N2kGateway
{
    enum class BoatDataType : uint8_t
    {
        Heading,
        SOG,
        COG,
        STW,
        Variation,
        AWS,
        TWS,
        MaxAws,
        MaxTws,
        AWA,
        TWA,
        AWD,
        TWD,
        TripLog,
        Log,
        RudderPosition,
        WaterTemperature,
        WaterDepth,
        GPSTime,
        Latitude,
        Longitude,
        Altitude,
        None,
    };

    class BoatData
    {
        std::map<BoatDataType, const double &> values{
            {BoatDataType::Heading, Heading},
            {BoatDataType::SOG, SOG},
            {BoatDataType::COG, COG},
            {BoatDataType::STW, STW},
            {BoatDataType::AWS, AWS},
            {BoatDataType::TWS, TWS},
            {BoatDataType::MaxAws, MaxAws},
            {BoatDataType::MaxTws, MaxTws},
            {BoatDataType::AWA, AWS},
            {BoatDataType::TWA, TWA},
            {BoatDataType::AWD, AWD},
            {BoatDataType::TWD, TWD},
            {BoatDataType::TripLog, TripLog},
            {BoatDataType::Log, Log},
            {BoatDataType::RudderPosition, RudderPosition},
            {BoatDataType::WaterTemperature, WaterTemperature},
            {BoatDataType::WaterDepth, WaterDepth},
            {BoatDataType::GPSTime, GPSTime},
            {BoatDataType::Latitude, Latitude},
            {BoatDataType::Longitude, Longitude},
            {BoatDataType::Altitude, Altitude},
        };

    public:
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

        const double &GetValue(BoatDataType type) const
        {
            // return AWS;
            return values.find(type)->second;
        };
    };
}