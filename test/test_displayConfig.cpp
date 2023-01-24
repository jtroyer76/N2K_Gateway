#include <gtest/gtest.h>
#include "DisplayConfig.h"
#include "Status.h"

using namespace N2kGateway;

TEST(IDisplay, Load_DisplayConfig_CorrectSize)
{
    auto displayConfig = DisplayConfig("test/data/displayConfig");
    displayConfig.Load();

    ASSERT_EQ(displayConfig.Items().size(), 1);
}

TEST(IDisplay, Load_DisplayConfig_CorrectValues)
{
    auto displayConfig = DisplayConfig("test/data/displayConfig");
    displayConfig.Load();
    
    auto config = displayConfig.Items()[0];

    EXPECT_EQ(config.Type, DisplayType::SingleDisplay);
    EXPECT_EQ(config.DataType, BoatDataType::SOG);
    EXPECT_STREQ(config.Description, "Speed Over Ground");
}
