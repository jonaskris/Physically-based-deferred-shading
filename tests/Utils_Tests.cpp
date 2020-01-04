#include <gtest/gtest.h>

#include <Utils.h>

#include <TestUtils.h>

namespace math
{
    TEST(AngleConversion, DegreesToRadians)
    {
        float d1 = 0.0f;
        float d2 = 45.0f;
        float d3 = 90.0f;
        float d4 = 360.0f;
        float d5 = 420.0f;

        float d1N = -0.0f;
        float d2N = -45.0f;
        float d3N = -90.0f;
        float d4N = -360.0f;    
        float d5N = -420.0f;

        EXPECT_FLOAT_EQ(toRadians(d1), 0.0f);
        EXPECT_FLOAT_EQ(toRadians(d2), (1.0f / 4.0f) * M_PI);
        EXPECT_FLOAT_EQ(toRadians(d3), (1.0f / 2.0f) * M_PI);
        EXPECT_FLOAT_EQ(toRadians(d4), 2.0f * M_PI);
        EXPECT_FLOAT_EQ(toRadians(d5), (7.0f / 3.0f) * M_PI);

        EXPECT_FLOAT_EQ(toRadians(d1N), -0.0f);
        EXPECT_FLOAT_EQ(toRadians(d2N), -(1.0f / 4.0f) * M_PI);
        EXPECT_FLOAT_EQ(toRadians(d3N), -(1.0f / 2.0f) * M_PI);
        EXPECT_FLOAT_EQ(toRadians(d4N), -2.0f * M_PI);
        EXPECT_FLOAT_EQ(toRadians(d5N), -(7.0f / 3.0f) * M_PI);
    }

    TEST(AngleConversion, RadiansToDegrees)
    {
        float r1 = 0.0f;
        float r2 = (1.0f / 4.0f) * M_PI;
        float r3 = (1.0f / 2.0f) * M_PI;
        float r4 = 2.0f * M_PI;
        float r5 = (7.0f / 3.0f) * M_PI;

        float r1N = -0.0f;
        float r2N = -(1.0f / 4.0f) * M_PI;
        float r3N = -(1.0f / 2.0f) * M_PI;
        float r4N = -2.0f * M_PI;
        float r5N = -(7.0f / 3.0f) * M_PI;

        EXPECT_FLOAT_EQ(toDegrees(r1), 0.0f);
        EXPECT_FLOAT_EQ(toDegrees(r2), 45.0f);
        EXPECT_FLOAT_EQ(toDegrees(r3), 90.0f);
        EXPECT_FLOAT_EQ(toDegrees(r4), 360.0f);
        EXPECT_FLOAT_EQ(toDegrees(r5), 420.0f);

        EXPECT_FLOAT_EQ(toDegrees(r1N), -0.0f);
        EXPECT_FLOAT_EQ(toDegrees(r2N), -45.0f);
        EXPECT_FLOAT_EQ(toDegrees(r3N), -90.0f);
        EXPECT_FLOAT_EQ(toDegrees(r4N), -360.0f);
        EXPECT_FLOAT_EQ(toDegrees(r5N), -420.0f);
    }

    TEST(AngleStructs, RadiansToDegreesAndBack)
    {
        Radians r1((1.0f / 4.0f) * M_PI);

        Degrees d(r1);

        Radians r2(d);

        EXPECT_FLOAT_EQ(r2, (1.0f / 4.0f) * M_PI);
    }

    TEST(AngleStructs, DegreesToRadiansAndBack)
    {
        Degrees d1(45.0f);

        Radians r(d1);

        Degrees d2(r);

        EXPECT_FLOAT_EQ(d2, 45.0f);
    }

    int main(int argc, char **argv)
    {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
}