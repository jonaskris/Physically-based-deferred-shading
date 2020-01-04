#include <gtest/gtest.h>

#include <Vec3.h>
#include <Vec4.h>
#include <Mat4.h>
#include <Utils.h>

#include <TestUtils.h>

namespace math
{
    TEST(Initialization, Default)
    {
        using namespace TestUtils;
        
        float const EXPECTED[16]
        {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };

        Mat4 mat1;

        EXPECT_MAT4_EQ_FLOAT_ARRAY(mat1, EXPECTED);
    }

    TEST(Initialization, Floats)
    {
        using namespace TestUtils;
        
        float const EXPECTED[16]
        {
            11.01f, 21.02f, 31.03f, 41.04f,
            12.05f, 22.06f, 32.07f, 42.08f,
            13.09f, 23.10f, 33.11f, 43.12f,
            14.13f, 24.14f, 34.15f, 44.16f
        };

        Mat4 mat1 
        (
            11.01f, 12.05f, 13.09f, 14.13f,
            21.02f, 22.06f, 23.10f, 24.14f,
            31.03f, 32.07f, 33.11f, 34.15f,
            41.04f, 42.08f, 43.12f, 44.16f
        );

        EXPECT_MAT4_EQ_FLOAT_ARRAY(mat1, EXPECTED);
    }

    TEST(Accessors, GetRow)
    {
        using namespace TestUtils;
        
        float const EXPECTED[16]
        {
            11.01f, 21.02f, 31.03f, 41.04f,
            12.05f, 22.06f, 32.07f, 42.08f,
            13.09f, 23.10f, 33.11f, 43.12f,
            14.13f, 24.14f, 34.15f, 44.16f
        };

        Mat4 mat1
        (
            11.01f, 12.05f, 13.09f, 14.13f,
            21.02f, 22.06f, 23.10f, 24.14f,
            31.03f, 32.07f, 33.11f, 34.15f,
            41.04f, 42.08f, 43.12f, 44.16f
        );

        Vec4 row0 = mat1.getRow(0);
        EXPECT_VEC4_EQ_FLOAT_ARRAY_ROW(row0, EXPECTED, 0);

        Vec4 row1 = mat1.getRow(1);
        EXPECT_VEC4_EQ_FLOAT_ARRAY_ROW(row1, EXPECTED, 1);

        Vec4 row2 = mat1.getRow(2);
        EXPECT_VEC4_EQ_FLOAT_ARRAY_ROW(row2, EXPECTED, 2);

        Vec4 row3 = mat1.getRow(3);
        EXPECT_VEC4_EQ_FLOAT_ARRAY_ROW(row3, EXPECTED, 3);
    }

    TEST(Accessors, SetRow)
    {
        using namespace TestUtils;
        
        float const EXPECTED[16]
        {
            11.01f, 21.02f, 31.03f, 41.04f,
            12.05f, 22.06f, 32.07f, 42.08f,
            13.09f, 23.10f, 33.11f, 43.12f,
            14.13f, 24.14f, 34.15f, 44.16f
        };

        Mat4 mat1;

        mat1.setRow(0, Vec4(11.01f, 21.02f, 31.03f, 41.04f) );
        mat1.setRow(1, Vec4(12.05f, 22.06f, 32.07f, 42.08f) );
        mat1.setRow(2, Vec4(13.09f, 23.10f, 33.11f, 43.12f) );
        mat1.setRow(3, Vec4(14.13f, 24.14f, 34.15f, 44.16f) );

        EXPECT_MAT4_EQ_FLOAT_ARRAY(mat1, EXPECTED);
    }

    TEST(Accessors, GetColumn)
    {
        using namespace TestUtils;
        
        float const EXPECTED[16]
        {
            11.01f, 21.02f, 31.03f, 41.04f,
            12.05f, 22.06f, 32.07f, 42.08f,
            13.09f, 23.10f, 33.11f, 43.12f,
            14.13f, 24.14f, 34.15f, 44.16f
        };

        Mat4 mat1
        (
            11.01f, 12.05f, 13.09f, 14.13f,
            21.02f, 22.06f, 23.10f, 24.14f,
            31.03f, 32.07f, 33.11f, 34.15f,
            41.04f, 42.08f, 43.12f, 44.16f
        );

        Vec4 column0 = mat1.getColumn(0);
        EXPECT_VEC4_EQ_FLOAT_ARRAY_COLUMN(column0, EXPECTED, 0);

        Vec4 column1 = mat1.getColumn(1);
        EXPECT_VEC4_EQ_FLOAT_ARRAY_COLUMN(column1, EXPECTED, 1);

        Vec4 column2 = mat1.getColumn(2);
        EXPECT_VEC4_EQ_FLOAT_ARRAY_COLUMN(column2, EXPECTED, 2);

        Vec4 column3 = mat1.getColumn(3);
        EXPECT_VEC4_EQ_FLOAT_ARRAY_COLUMN(column3, EXPECTED, 3);

    }

    TEST(Accessors, SetColumn)
    {
        using namespace TestUtils;
        
        float const EXPECTED[16]
        {
            11.01f, 12.05f, 13.09f, 14.13f,
            21.02f, 22.06f, 23.10f, 24.14f,
            31.03f, 32.07f, 33.11f, 34.15f,
            41.04f, 42.08f, 43.12f, 44.16f
        };

        Mat4 mat1;

        mat1.setColumn(0, Vec4(11.01f, 21.02f, 31.03f, 41.04f) );
        mat1.setColumn(1, Vec4(12.05f, 22.06f, 32.07f, 42.08f) );
        mat1.setColumn(2, Vec4(13.09f, 23.10f, 33.11f, 43.12f) );
        mat1.setColumn(3, Vec4(14.13f, 24.14f, 34.15f, 44.16f) );

        // Check correct columns were set
        EXPECT_MAT4_EQ_FLOAT_ARRAY(mat1, EXPECTED);
    }

    TEST(Operations, MatMultMat)
    {
        using namespace TestUtils;
        
        float const EXPECTED[16]
        {
            92.67f,  162.74f, 232.81f, 302.88f,
            120.93f, 211.02f, 301.11f, 391.2f,
            151.27f, 261.38f, 371.49f, 481.6f,
            14.13f,  24.14f,  34.15f,  44.16f 
        };

        // Scale by [2, 3, 4] then translate by [5, 6, 7]
        const Mat4 mat1 = Mat4::translate({5, 6, 7}) * Mat4::scale({2, 3, 4});

        const Mat4 mat2 
        (
            11.01f, 12.05f, 13.09f, 14.13f,
            21.02f, 22.06f, 23.10f, 24.14f,
            31.03f, 32.07f, 33.11f, 34.15f,
            41.04f, 42.08f, 43.12f, 44.16f
        );

        Mat4 mat3 = mat1 * mat2;

        EXPECT_MAT4_EQ_FLOAT_ARRAY(mat3, EXPECTED);   
    }

    TEST(Operations, MatMultVec)
    {
        using namespace TestUtils;
        
        float const EXPECTED[16] {24.2f, 33.0f, 44.0f, 4.4f};

        // Scale by [2, 3, 4] then translate by [5, 6, 7]
        const Mat4 mat1 = Mat4::translate({5, 6, 7}) * Mat4::scale({2, 3, 4});

        const Vec4 v1 {1.1f, 2.2f, 3.3f, 4.4f};

        Vec4 v2 = mat1 * v1;

        EXPECT_VEC4_EQ_FLOAT_ARRAY_ROW(v2, EXPECTED, 0);   
    }

    TEST(Operations, Inverse)
    {
        using namespace TestUtils;
        
        float const EXPECTED[16]
        {
            0.5f, 0.0f,         0.0f, -2.5f,
            0.0f, 1.0f / 3.0f,  0.0f, -2.0f,
            0.0f, 0.0f,         0.25f, -1.75f,
            0.0f, 0.0f,         0.0f, 1.0f
        };

        // Scale by [2, 3, 4] then translate by [5, 6, 7]
        const Mat4 mat1 = Mat4::translate({5, 6, 7}) * Mat4::scale({2, 3, 4});
        const Mat4 mat2 = mat1.inverse().value();
        
        EXPECT_MAT4_EQ_FLOAT_ARRAY(mat2, EXPECTED);
        EXPECT_MAT4_EQ_MAT4(mat1 * mat2, Mat4::identity());
    }

    TEST(Generators, Identity)
    {
        using namespace TestUtils;
        
        float const EXPECTED[16]
        {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };

        const Mat4 mat1 = Mat4::identity();

        EXPECT_MAT4_EQ_FLOAT_ARRAY(mat1, EXPECTED);   
    }

    TEST(Generators, Translate)
    {
        using namespace TestUtils;
        
        float const EXPECTED[16]
        {
            1.0f, 0.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 0.0f, 2.0f,
            0.0f, 0.0f, 1.0f, 3.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };

        const Mat4 mat1 = Mat4::translate({1, 2, 3});

        EXPECT_MAT4_EQ_FLOAT_ARRAY(mat1, EXPECTED);   
    }

    TEST(Generators, RotateAxisAngle)
    {
        using namespace TestUtils;
        
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

        const Mat4 matX = Mat4::rotate( Degrees(45.0f), {1.0f, 0.0f, 0.0f} );
        const Mat4 matY = Mat4::rotate( Degrees(45.0f), {0.0f, 1.0f, 0.0f} );
        const Mat4 matZ = Mat4::rotate( Degrees(45.0f), {0.0f, 0.0f, 1.0f} );

        EXPECT_MAT4_EQ_FLOAT_ARRAY(matX, EXPECTEDX);   
        EXPECT_MAT4_EQ_FLOAT_ARRAY(matY, EXPECTEDY);   
        EXPECT_MAT4_EQ_FLOAT_ARRAY(matZ, EXPECTEDZ);   
    }

    TEST(Generators, Scale)
    {
        using namespace TestUtils;
        
        float const EXPECTED[16]
        {
            2.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 3.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 4.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };

        Mat4 mat1 = Mat4::scale({2, 3, 4});

        EXPECT_MAT4_EQ_FLOAT_ARRAY(mat1, EXPECTED);   
    }

    int main(int argc, char **argv)
    {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
}