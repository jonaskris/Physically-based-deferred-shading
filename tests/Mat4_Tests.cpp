#include <gtest/gtest.h>

#include <Vec3.h>
#include <Vec4.h>
#include <Mat4.h>

// Helper methods

// Compares a float array a and mat4 elements as if the float array is transposed,
// so that the float array can be represented in code correctly despite having a different
// memory layout.
void EXPECT_MAT4_EQ_FLOAT_ARRAY(const float* m4, const float* fa)
{
    for(size_t column = 0; column < 4; column++)
        for(size_t row = 0; row < 4; row++)
            EXPECT_FLOAT_EQ(m4[column * 4 + row], fa[row * 4 + column]);
}

// Compares all elements of array with float
void EXPECT_MAT4_EQ_FLOAT(const float* m4, float f)
{
    for(size_t i = 0; i < 4*4; i++)
        EXPECT_FLOAT_EQ(m4[i], f);
}

// Compares vec4 with row of matrix
void EXPECT_VEC4_EQ_FLOAT_ARRAY_ROW(const float* v4, const float* fa, size_t row)
{
    for(size_t i = 0; i < 4; i++)
        EXPECT_FLOAT_EQ(v4[i], fa[row * 4 + i]);
}

// Compares vec4 with column of matrix
void EXPECT_VEC4_EQ_FLOAT_ARRAY_COLUMN(const float* v4, const float* fa, size_t column)
{
    for(size_t i = 0; i < 4; i++)
        EXPECT_FLOAT_EQ(v4[i], fa[i * 4 + column]);
}

TEST(Initialization, Default)
{
    using namespace math;

    mat4 mat1;

    EXPECT_MAT4_EQ_FLOAT(mat1.elements, 0.0f);
}

TEST(Initialization, Floats)
{
    using namespace math;

    float const EXPECTED[16]
    {
        11.01f, 21.02f, 31.03f, 41.04f,
        12.05f, 22.06f, 32.07f, 42.08f,
        13.09f, 23.10f, 33.11f, 43.12f,
        14.13f, 24.14f, 34.15f, 44.16f
    };

    mat4 mat1 
    {
        11.01f, 12.05f, 13.09f, 14.13f,
        21.02f, 22.06f, 23.10f, 24.14f,
        31.03f, 32.07f, 33.11f, 34.15f,
        41.04f, 42.08f, 43.12f, 44.16f
    };

    EXPECT_MAT4_EQ_FLOAT_ARRAY(mat1.elements, EXPECTED);
}

TEST(Accessors, GetRow)
{
    using namespace math;

    float const EXPECTED[16]
    {
        11.01f, 21.02f, 31.03f, 41.04f,
        12.05f, 22.06f, 32.07f, 42.08f,
        13.09f, 23.10f, 33.11f, 43.12f,
        14.13f, 24.14f, 34.15f, 44.16f
    };

    mat4 mat1
    {
        11.01f, 12.05f, 13.09f, 14.13f,
        21.02f, 22.06f, 23.10f, 24.14f,
        31.03f, 32.07f, 33.11f, 34.15f,
        41.04f, 42.08f, 43.12f, 44.16f
    };

    vec4 row0 = mat1.getRow(0);
    EXPECT_VEC4_EQ_FLOAT_ARRAY_ROW(row0.elements, EXPECTED, 0);

    vec4 row1 = mat1.getRow(1);
    EXPECT_VEC4_EQ_FLOAT_ARRAY_ROW(row1.elements, EXPECTED, 1);

    vec4 row2 = mat1.getRow(2);
    EXPECT_VEC4_EQ_FLOAT_ARRAY_ROW(row2.elements, EXPECTED, 2);

    vec4 row3 = mat1.getRow(3);
    EXPECT_VEC4_EQ_FLOAT_ARRAY_ROW(row3.elements, EXPECTED, 3);
}

TEST(Accessors, SetRow)
{
    using namespace math;

    float const EXPECTED[16]
    {
        11.01f, 21.02f, 31.03f, 41.04f,
        12.05f, 22.06f, 32.07f, 42.08f,
        13.09f, 23.10f, 33.11f, 43.12f,
        14.13f, 24.14f, 34.15f, 44.16f
    };

    mat4 mat1;

    mat1.setRow(0, vec4{11.01f, 21.02f, 31.03f, 41.04f});
    mat1.setRow(1, vec4{12.05f, 22.06f, 32.07f, 42.08f});
    mat1.setRow(2, vec4{13.09f, 23.10f, 33.11f, 43.12f});
    mat1.setRow(3, vec4{14.13f, 24.14f, 34.15f, 44.16f});

    EXPECT_MAT4_EQ_FLOAT_ARRAY(mat1.elements, EXPECTED);
}

TEST(Accessors, GetColumn)
{
    using namespace math;

    float const EXPECTED[16]
    {
        11.01f, 21.02f, 31.03f, 41.04f,
        12.05f, 22.06f, 32.07f, 42.08f,
        13.09f, 23.10f, 33.11f, 43.12f,
        14.13f, 24.14f, 34.15f, 44.16f
    };

    mat4 mat1
    {
        11.01f, 12.05f, 13.09f, 14.13f,
        21.02f, 22.06f, 23.10f, 24.14f,
        31.03f, 32.07f, 33.11f, 34.15f,
        41.04f, 42.08f, 43.12f, 44.16f
    };

    vec4 column0 = mat1.getColumn(0);
    EXPECT_VEC4_EQ_FLOAT_ARRAY_COLUMN(column0.elements, EXPECTED, 0);

    vec4 column1 = mat1.getColumn(1);
    EXPECT_VEC4_EQ_FLOAT_ARRAY_COLUMN(column1.elements, EXPECTED, 1);

    vec4 column2 = mat1.getColumn(2);
    EXPECT_VEC4_EQ_FLOAT_ARRAY_COLUMN(column2.elements, EXPECTED, 2);

    vec4 column3 = mat1.getColumn(3);
    EXPECT_VEC4_EQ_FLOAT_ARRAY_COLUMN(column3.elements, EXPECTED, 3);

}

TEST(Accessors, SetColumn)
{
    using namespace math;

    float const EXPECTED[16]
    {
        11.01f, 12.05f, 13.09f, 14.13f,
        21.02f, 22.06f, 23.10f, 24.14f,
        31.03f, 32.07f, 33.11f, 34.15f,
        41.04f, 42.08f, 43.12f, 44.16f
    };

    mat4 mat1;

    mat1.setColumn(0, vec4{11.01f, 21.02f, 31.03f, 41.04f});
    mat1.setColumn(1, vec4{12.05f, 22.06f, 32.07f, 42.08f});
    mat1.setColumn(2, vec4{13.09f, 23.10f, 33.11f, 43.12f});
    mat1.setColumn(3, vec4{14.13f, 24.14f, 34.15f, 44.16f});

    // Check correct columns were set
    EXPECT_MAT4_EQ_FLOAT_ARRAY(mat1.elements, EXPECTED);
}

TEST(Operations, MatMultMat)
{
    using namespace math;

    float const EXPECTED[16]
    {
        92.67f,  162.74f, 232.81f, 302.88f,
        120.93f, 211.02f, 301.11f, 391.2f,
        151.27f, 261.38f, 371.49f, 481.6f,
        14.13f,  24.14f,  34.15f,  44.16f 
    };

    // Scale by [2, 3, 4] then translate by [5, 6, 7]
    const mat4 mat1 = mat4::translate({5, 6, 7}) * mat4::scale({2, 3, 4});

    const mat4 mat2 
    {
        11.01f, 12.05f, 13.09f, 14.13f,
        21.02f, 22.06f, 23.10f, 24.14f,
        31.03f, 32.07f, 33.11f, 34.15f,
        41.04f, 42.08f, 43.12f, 44.16f
    };

    mat4 mat3 = mat1 * mat2;

    EXPECT_MAT4_EQ_FLOAT_ARRAY(mat3.elements, EXPECTED);   
}

TEST(Operations, MatMultVec)
{
    using namespace math;

    float const EXPECTED[16] {24.2f, 33.0f, 44.0f, 4.4f};

    // Scale by [2, 3, 4] then translate by [5, 6, 7]
    const mat4 mat1 = mat4::translate({5, 6, 7}) * mat4::scale({2, 3, 4});

    const vec4 v1 {1.1f, 2.2f, 3.3f, 4.4f};

    vec4 v2 = mat1 * v1;

    EXPECT_VEC4_EQ_FLOAT_ARRAY_ROW(v2.elements, EXPECTED, 0);   
}

TEST(Generators, Identity)
{
    using namespace math;

    float const EXPECTED[16]
    {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    const mat4 mat1 = mat4::identity();

    EXPECT_MAT4_EQ_FLOAT_ARRAY(mat1.elements, EXPECTED);   
}

TEST(Generators, Translate)
{
    using namespace math;

    float const EXPECTED[16]
    {
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 2.0f,
        0.0f, 0.0f, 1.0f, 3.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    const mat4 mat1 = mat4::translate({1, 2, 3});

    EXPECT_MAT4_EQ_FLOAT_ARRAY(mat1.elements, EXPECTED);   
}

TEST(Generators, Rotate)
{
    using namespace math;

    float const EXPECTEDX[16]
    {
        1.0f, 0.0f,                 0.0f,               0.0f,
        0.0f, cosf(0.785398163f),   sinf(0.785398163f), 0.0f,
        0.0f, -sinf(0.785398163f),  cosf(0.785398163f), 0.0f,
        0.0f, 0.0f,                 0.0f,               1.0f
    };

    float const EXPECTEDY[16]
    {
        cosf(0.785398163f), 0.0f, -sinf(0.785398163f),  0.0f,
        0.0f,               1.0f, 0.0f,                 0.0f,
        sinf(0.785398163f), 0.0f, cosf(0.785398163f),   0.0f,
        0.0f,               0.0f, 0.0f,                 1.0f
    };

    float const EXPECTEDZ[16]
    {
        cosf(0.785398163f),     sinf(0.785398163f), 0.0f, 0.0f,
        -sinf(0.785398163f),    cosf(0.785398163f), 0.0f, 0.0f,
        0.0f,                   0.0f,               1.0f, 0.0f,
        0.0f,                   0.0f,               0.0f, 1.0f
    };

    const mat4 matX = mat4::rotate(45.0f, {1.0f, 0.0f, 0.0f});
    const mat4 matY = mat4::rotate(45.0f, {0.0f, 1.0f, 0.0f});
    const mat4 matZ = mat4::rotate(45.0f, {0.0f, 0.0f, 1.0f});

    EXPECT_MAT4_EQ_FLOAT_ARRAY(matX.elements, EXPECTEDX);   
    EXPECT_MAT4_EQ_FLOAT_ARRAY(matY.elements, EXPECTEDY);   
    EXPECT_MAT4_EQ_FLOAT_ARRAY(matZ.elements, EXPECTEDZ);   
}

TEST(Generators, Scale)
{
    using namespace math;

    float const EXPECTED[16]
    {
        2.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 3.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 4.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    mat4 mat1 = mat4::scale({2, 3, 4});
    
    EXPECT_MAT4_EQ_FLOAT_ARRAY(mat1.elements, EXPECTED);   
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}