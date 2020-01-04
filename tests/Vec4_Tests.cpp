#include <gtest/gtest.h>

#include <Vec3.h>
#include <Vec4.h>
#include <Mat4.h>

#include <TestUtils.h>

namespace math
{
    TEST(Initialization, Default)
    {
        using namespace TestUtils;

        Vec4 vec1;

        EXPECT_VEC4_EQ_FLOAT(vec1, 0.0f);
    }

    TEST(Initialization, Floats)
    {
        using namespace TestUtils;

        float const EXPECTED[4] {1.0f, 2.0f, 3.0f, 4.0f};

        Vec4 vec1(1.0f, 2.0f, 3.0f, 4.0f);

        EXPECT_VEC4_EQ_FLOAT_ARRAY(vec1, EXPECTED);
    }

    TEST(Operations, VecMultMat)
    {
        using namespace TestUtils;

        float const EXPECTED[4] {2.2f, 6.6f, 13.2f, 46.2f};

        // Scale by [2, 3, 4] then translate by [5, 6, 7]
        const Mat4 mat1 = Mat4::translate({5, 6, 7}) * Mat4::scale({2, 3, 4});

        const Vec4 v1(1.1f, 2.2f, 3.3f, 4.4f);

        Vec4 v2 = v1 * mat1;

        EXPECT_VEC4_EQ_FLOAT_ARRAY(v2, EXPECTED); 
    }

    TEST(Operations, Negation)
    {
        using namespace TestUtils;

        float const EXPECTED[4] {-1.0f, 2.0f, -3.0f, 4.0f};

        const Vec4 v1(1.0f, -2.0f, 3.0f, -4.0f);
        const Vec4 v2 = -v1;

        EXPECT_VEC4_EQ_FLOAT_ARRAY(v2, EXPECTED); 
    }

    TEST(Operations, Magnitude)
    {
        const float EXPECTED = 6.0249481f;

        const Vec4 v1(1.1f, 2.2f, 3.3f, 4.4f);

        float f = v1.magnitude();

        EXPECT_FLOAT_EQ(f, EXPECTED); 
    }

    TEST(Operations, Dot)
    {
        const float EXPECTED = 58.630005f;

        const Vec4 v1(1.1f, 2.2f, 3.3f, 4.4f);
        const Vec4 v2(7.2f, 6.1f, 4.9f, 4.8f);

        float f1 = v1.dot(v2);
        float f2 = v2.dot(v1);

        EXPECT_FLOAT_EQ(f1, EXPECTED); 
        EXPECT_FLOAT_EQ(f2, EXPECTED); 
    }

    TEST(Operations, Normalize)
    {
        using namespace TestUtils;

        const float EXPECTED1[4] {0.18257418f, -0.36514837f, 0.54772258f, 0.73029673f};
        const float EXPECTED2[4] {-0.61716801f, 0.52287847f, 0.42001712f, -0.41144535f};

        const Vec4 v1(1.1f, -2.2f, 3.3f, 4.4f);
        const Vec4 v2(-7.2f, 6.1f, 4.9f, -4.8f);

        Vec4 n1 = v1.normalize();
        Vec4 n2 = v2.normalize();

        EXPECT_VEC4_EQ_FLOAT_ARRAY(n1, EXPECTED1); 
        EXPECT_VEC4_EQ_FLOAT_ARRAY(n2, EXPECTED2); 
    }

    int main(int argc, char **argv)
    {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
}