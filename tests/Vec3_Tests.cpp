#include <gtest/gtest.h>

#include <Vec3.h>

void EXPECT_VEC3_EQ_FLOAT_ARRAY(const float* v3, const float* fa)
{
    for(size_t i = 0; i < 3; i++)
        EXPECT_FLOAT_EQ(v3[i], fa[i]);
}

void EXPECT_VEC3_EQ_FLOAT(const float* v3, float f)
{
    for(size_t i = 0; i < 3; i++)
        EXPECT_FLOAT_EQ(v3[i], f);
}

TEST(Initialization, Default)
{
    using namespace math;

    vec3 vec1;

    EXPECT_VEC3_EQ_FLOAT(vec1.elements, 0.0f);
}

TEST(Initialization, Floats)
{
    using namespace math;

    float const EXPECTED[3]
    {
        1.0f, 2.0f, 3.0f
    };

    vec3 vec1{1.0f, 2.0f, 3.0f};

    EXPECT_VEC3_EQ_FLOAT_ARRAY(vec1.elements, EXPECTED);
}

TEST(Operations, Magnitude)
{
    using namespace math;

    const float EXPECTED = 4.1158228f;

    const vec3 v1 {1.1f, 2.2f, 3.3f};

    float f = v1.magnitude();

    EXPECT_FLOAT_EQ(f, EXPECTED); 
}

TEST(Operations, Dot)
{
    using namespace math;

    const float EXPECTED = 37.510002f;

    const vec3 v1 {1.1f, 2.2f, 3.3f};

    const vec3 v2 {7.2f, 6.1f, 4.9f};

    float f1 = v1.dot(v2);
    float f2 = v2.dot(v1);

    EXPECT_FLOAT_EQ(f1, EXPECTED); 
    EXPECT_FLOAT_EQ(f2, EXPECTED); 
}

TEST(Operations, Normalize)
{
    using namespace math;

    const float EXPECTED1[3] {0.26726127f, -0.53452253f, 0.8017838f};

    const float EXPECTED2[3] {-0.67713922f, 0.57368743f, 0.4608309f};

    const vec3 v1 {1.1f, -2.2f, 3.3f};

    const vec3 v2 {-7.2f, 6.1f, 4.9f};

    vec3 n1 = v1.normalize();
    vec3 n2 = v2.normalize();

    EXPECT_VEC3_EQ_FLOAT_ARRAY(n1.elements, EXPECTED1); 
    EXPECT_VEC3_EQ_FLOAT_ARRAY(n2.elements, EXPECTED2); 
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}