#include <gtest/gtest.h>

#include <Vec3.h>
#include <Vec4.h>
#include <Mat4.h>

void EXPECT_VEC4_EQ_FLOAT_ARRAY(const float* v4, const float* fa)
{
    for(size_t i = 0; i < 4; i++)
        EXPECT_FLOAT_EQ(v4[i], fa[i]);
}

void EXPECT_VEC4_EQ_FLOAT(const float* v4, float f)
{
    for(size_t i = 0; i < 4; i++)
        EXPECT_FLOAT_EQ(v4[i], f);
}

TEST(Initialization, Default)
{
    using namespace math;

    vec4 vec1;

    EXPECT_VEC4_EQ_FLOAT(vec1.elements, 0.0f);
}

TEST(Initialization, Floats)
{
    using namespace math;

    float const EXPECTED[4] {1.0f, 2.0f, 3.0f, 4.0f};

    vec4 vec1{1.0f, 2.0f, 3.0f, 4.0f};

    EXPECT_VEC4_EQ_FLOAT_ARRAY(vec1.elements, EXPECTED);
}

TEST(Operations, VecMultMat)
{
    using namespace math;

    float const EXPECTED[4] {2.2f, 6.6f, 13.2f, 46.2f};

    // Scale by [2, 3, 4] then translate by [5, 6, 7]
    const mat4 mat1 = mat4::translate({5, 6, 7}) * mat4::scale({2, 3, 4});

    const vec4 v1 {1.1f, 2.2f, 3.3f, 4.4f};

    vec4 v2 = v1 * mat1;

    EXPECT_VEC4_EQ_FLOAT_ARRAY(v2.elements, EXPECTED); 
}

TEST(Operations, Magnitude)
{
    using namespace math;

    const float EXPECTED = 6.0249481f;

    const vec4 v1 {1.1f, 2.2f, 3.3f, 4.4f};

    float f = v1.magnitude();

    EXPECT_FLOAT_EQ(f, EXPECTED); 
}

TEST(Operations, Dot)
{
    using namespace math;

    const float EXPECTED = 58.630005f;

    const vec4 v1 {1.1f, 2.2f, 3.3f, 4.4f};

    const vec4 v2 {7.2f, 6.1f, 4.9f, 4.8f};

    float f1 = v1.dot(v2);
    float f2 = v2.dot(v1);

    EXPECT_FLOAT_EQ(f1, EXPECTED); 
    EXPECT_FLOAT_EQ(f2, EXPECTED); 
}

TEST(Operations, Normalize)
{
    using namespace math;

    const float EXPECTED1[4] {0.18257418f, -0.36514837f, 0.54772258f, 0.73029673f};

    const float EXPECTED2[4] {-0.61716801f, 0.52287847f, 0.42001712f, -0.41144535f};

    const vec4 v1 {1.1f, -2.2f, 3.3f, 4.4f};

    const vec4 v2 {-7.2f, 6.1f, 4.9f, -4.8f};

    vec4 n1 = v1.normalize();
    vec4 n2 = v2.normalize();

    EXPECT_VEC4_EQ_FLOAT_ARRAY(n1.elements, EXPECTED1); 
    EXPECT_VEC4_EQ_FLOAT_ARRAY(n2.elements, EXPECTED2); 
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}