#include <gtest/gtest.h>

#include <Quaternion.h>
#include <Vec3.h>
#include <Vec4.h>
#include <Mat4.h>
#include <Transform.h>

#include <TestUtils.h>

namespace math
{
    TEST(Initialization, Default)
    {
        using namespace TestUtils;
        
        float const EXPECTEDPOS[3] {0.0f, 0.0f, 0.0f};      // Origin
        float const EXPECTEDORIENTATION[4] {0.0f, 0.0f, 0.0f, 1.0f}; // Multiplicative identity
        float const EXPECTEDSCALE[3] {1.0f, 1.0f, 1.0f};    // Unchanged scale

        const Transform t;

        EXPECT_VEC3_EQ_FLOAT_ARRAY(t.getPosition(), EXPECTEDPOS);
        EXPECT_QUAT_EQ_FLOAT_ARRAY(t.getOrientation(), EXPECTEDORIENTATION);
        EXPECT_VEC3_EQ_FLOAT_ARRAY(t.getScale(), EXPECTEDSCALE);
    }

    TEST(Accessors, DefaultInitToMatrix)
    {
        using namespace TestUtils;
        
        float const EXPECTED[16]
        {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };

        Transform t;

        EXPECT_MAT4_EQ_FLOAT_ARRAY(t.toMatrix(), EXPECTED);
    }

    TEST(Accessors, TranslationToMatrix)
    {
        using namespace TestUtils;
        
        float const EXPECTED[16]
        {
            1.0f, 0.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 0.0f, 2.0f,
            0.0f, 0.0f, 1.0f, 3.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };

        Transform t({1.0f, 2.0f, 3.0f}); // Orientation and scale are default initialized
        Mat4 m = t.toMatrix();

        EXPECT_MAT4_EQ_FLOAT_ARRAY(m, EXPECTED);   
    }

    TEST(Accessors, OrientationToMatrix)
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

        Transform tx( {}, Quaternion::fromAxisAngle({1.0f, 0.0f, 0.0f}, Degrees(45.0f)) );
        Transform ty( {}, Quaternion::fromAxisAngle({0.0f, 1.0f, 0.0f}, Degrees(45.0f)) );
        Transform tz( {}, Quaternion::fromAxisAngle({0.0f, 0.0f, 1.0f}, Degrees(45.0f)) );

        EXPECT_MAT4_EQ_FLOAT_ARRAY(tx.toMatrix(), EXPECTEDX);   
        EXPECT_MAT4_EQ_FLOAT_ARRAY(ty.toMatrix(), EXPECTEDY);   
        EXPECT_MAT4_EQ_FLOAT_ARRAY(tz.toMatrix(), EXPECTEDZ);   
    }

    TEST(Accessors, ScaleToMatrix)
    {
        using namespace TestUtils;
        
        float const EXPECTED[16]
        {
            2.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 3.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 4.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };

        Transform t({}, {}, {2.0f, 3.0f, 4.0f});

        EXPECT_MAT4_EQ_FLOAT_ARRAY(t.toMatrix(), EXPECTED);   
    }

    TEST(Accessors, TransformToMatrix)
    {
        using namespace TestUtils;
        
        const Mat4 mt = Mat4::translate({1.0f, 2.0f, 3.0f});
        const Mat4 mr = Mat4::rotate(Degrees(45.0f), {1.0f, 0.0f, 0.0f});
        const Mat4 ms = Mat4::scale({2.0f, 3.0f, 4.0f});

        const Mat4 EXPECTED = mt * mr * ms;

        // Transform should be applied in order: Scale -> Rotate -> Translate
        Transform t({1.0f, 2.0f, 3.0f}, Quaternion::fromAxisAngle({1.0f, 0.0f, 0.0f}, Degrees(45.0f)), {2.0f, 3.0f, 4.0f});

        EXPECT_MAT4_EQ_MAT4(t.toMatrix(), EXPECTED);
    }

    TEST(Operations, Multiplication)
    {
        using namespace TestUtils;

        const Mat4 EXPECTED = 
            Mat4::translate({0.0f, 0.0f, 2.0f})
            * Mat4::scale({2.0f, 2.0f, 2.0f})
            * Mat4::translate({1.0f, 1.0f, 0.0f})
            * Mat4::rotate(Degrees(45.0f), {1.0f, 0.0f, 0.0f})
            * Mat4::scale({2.0f, 2.0f, 2.0f});

        Transform t1({1.0f, 1.0f, 0.0f}, Quaternion::fromAxisAngle({1.0f, 0.0f, 0.0f}, Degrees(45.0f)), {2.0f, 2.0f, 2.0f});
        Transform t2({0.0f, 0.0f, 2.0f}, {}, {2.0f, 2.0f, 2.0f});

        // Transformation should result t2 being relative to t1,
        // or in other words; in the same order as EXPECTED matrix is built.
        const Mat4 transformation = t2 * t1;

        EXPECT_MAT4_EQ_MAT4(transformation, EXPECTED);
    }    

    int main(int argc, char **argv)
    {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
}