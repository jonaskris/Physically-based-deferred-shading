#include <gtest/gtest.h>

#include <Vec2.h>

#include <TestUtils.h>


namespace math
{
    TEST(Initialization, Default)
    {
        using namespace TestUtils;

        Vec2 vec1;

        EXPECT_VEC2_EQ_FLOAT(vec1, 0.0f);
    }

    TEST(Initialization, Floats)
    {
        using namespace TestUtils;

        float const EXPECTED[2] {1.0f, 2.0f};

        Vec2 vec1(1.0f, 2.0f);

        EXPECT_VEC2_EQ_FLOAT_ARRAY(vec1, EXPECTED);
    }

    TEST(Operations, Negation)
    {
        using namespace TestUtils;

        float const EXPECTED[2] {-1.0f, 2.0f};

        const Vec2 v1(1.0f, -2.0f);
        const Vec2 v2 = -v1;

        EXPECT_VEC2_EQ_FLOAT_ARRAY(v2, EXPECTED); 
    }

    TEST(Operations, Magnitude)
    {
        const float EXPECTED = 2.4596748f;

        const Vec2 v1(1.1f, 2.2f);

        float f = v1.magnitude();

        EXPECT_FLOAT_EQ(f, EXPECTED); 
    }

    TEST(Operations, Dot)
    {
        const float EXPECTED = 21.34f;

        const Vec2 v1(1.1f, 2.2f);
        const Vec2 v2(7.2f, 6.1f);

        float f1 = v1.dot(v2);
        float f2 = v2.dot(v1);

        EXPECT_FLOAT_EQ(f1, EXPECTED); 
        EXPECT_FLOAT_EQ(f2, EXPECTED); 
    }

    TEST(Operations, Normalize)
    {
        using namespace TestUtils;

        const float EXPECTED1[2] {0.44721359f, -0.89442718f};
        const float EXPECTED2[2] {-0.76298422f, 0.6464172f};

        const Vec2 v1(1.1f, -2.2f);
        const Vec2 v2(-7.2f, 6.1f);

        Vec2 n1 = v1.normalize();
        Vec2 n2 = v2.normalize();

        EXPECT_VEC2_EQ_FLOAT_ARRAY(n1, EXPECTED1); 
        EXPECT_VEC2_EQ_FLOAT_ARRAY(n2, EXPECTED2); 
    }

    int main(int argc, char **argv)
    {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
}