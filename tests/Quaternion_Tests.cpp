#include <gtest/gtest.h>

#include <Quaternion.h>
#include <Vec3.h>
#include <Vec4.h>
#include <Mat4.h>

#include <TestUtils.h>

namespace math
{
    TEST(Initialization, Default)
    {
        using namespace TestUtils;
            
        float const EXPECTED[4] {0.0f, 0.0f, 0.0f, 1.0f}; // Multiplicative identity

        const Quaternion q;

        EXPECT_QUAT_EQ_FLOAT_ARRAY(q, EXPECTED);
    }

    TEST(Initialization, AxisAngle)
    {
        using namespace TestUtils;
        
        float const EXPECTEDX[4] {0.38268346f, 0.0f, 0.0f, 0.9238795325f};
        float const EXPECTEDY[4] {0.0f, 0.38268346f, 0.0f, 0.9238795325f};
        float const EXPECTEDZ[4] {0.0f, 0.0f, 0.38268346f, 0.9238795325f};

        const Quaternion qX = Quaternion::fromAxisAngle({1.0f, 0.0f, 0.0f}, math::Degrees(45.0f));  // 45 degree rotation around x axis
        const Quaternion qY = Quaternion::fromAxisAngle({0.0f, 1.0f, 0.0f}, math::Degrees(45.0f));  // 45 degree rotation around y axis
        const Quaternion qZ = Quaternion::fromAxisAngle({0.0f, 0.0f, 1.0f}, math::Degrees(45.0f));  // 45 degree rotation around z axis

        EXPECT_QUAT_EQ_FLOAT_ARRAY(qX, EXPECTEDX);
        EXPECT_QUAT_EQ_FLOAT_ARRAY(qY, EXPECTEDY);
        EXPECT_QUAT_EQ_FLOAT_ARRAY(qZ, EXPECTEDZ);
    }

    TEST(Initialization, EulerAngles)
    {
        using namespace TestUtils;
        
        float const EXPECTEDX[4] {0.38268346f, 0.0f, 0.0f, 0.9238795325f};
        float const EXPECTEDY[4] {0.0f, 0.38268346f, 0.0f, 0.9238795325f};
        float const EXPECTEDZ[4] {0.0f, 0.0f, 0.38268346f, 0.9238795325f};

        const Quaternion qX = Quaternion::fromEulerAngles(Degrees(45.0f), Degrees(0.0f), Degrees(0.0f));    // 45 degree rotation around x axis
        const Quaternion qY = Quaternion::fromEulerAngles(Degrees(0.0f), Degrees(45.0f), Degrees(0.0f));    // 45 degree rotation around y axis
        const Quaternion qZ = Quaternion::fromEulerAngles(Degrees(0.0f), Degrees(0.0f), Degrees(45.0f));    // 45 degree rotation around z axis

        EXPECT_QUAT_EQ_FLOAT_ARRAY(qX, EXPECTEDX);
        EXPECT_QUAT_EQ_FLOAT_ARRAY(qY, EXPECTEDY);
        EXPECT_QUAT_EQ_FLOAT_ARRAY(qZ, EXPECTEDZ);
    }

    TEST(Operations, SuccessiveMultiplicationsAndInverse)
    {
        using namespace TestUtils;
        
        float const EXPECTED1[4] {0.0f, 0.0f, 0.0f, 1.0f}; // Multiplicative identity
        float const EXPECTED2[4] {0.38268346f, 0.0f, 0.0f, 0.9238795325f}; // 45 degree rotation around x axis

        const Quaternion q1 = Quaternion::fromAxisAngle({1.0f, 0.0f, 0.0f}, math::Degrees(45.0f));
        const Quaternion q2 = Quaternion::fromAxisAngle({0.0f, 1.0f, 0.0f}, math::Degrees(90.0f));

        // A rotation and its inverse should result in the multiplicative identity
        const Quaternion q3 = q1 * q1.inverse();
        EXPECT_QUAT_EQ_FLOAT_ARRAY(q3, EXPECTED1);

        // Two rotations and the inverse of the last should result in the first rotation
        const Quaternion q4 = q1 * q2 * q2.inverse();
        EXPECT_QUAT_EQ_FLOAT_ARRAY(q4, EXPECTED2);
    }

    TEST(Operations, Magnitude)
    {
        const float EXPECTED = 6.0249481f;

        const Quaternion v1(1.1f, 2.2f, 3.3f, 4.4f);

        float f = v1.magnitude();

        EXPECT_FLOAT_EQ(f, EXPECTED); 
    }

    TEST(Operations, QuaternionMultiplyVec3)
    {
        using namespace TestUtils;
        
        const float EXPECTEDX[3] {1.0f, 0.0f, 0.0f};
        const float EXPECTEDY[3] {0.0f, 0.0f, -1.0f};
        const float EXPECTEDZ[3] {0.0f, 1.0f, 0.0f};

        const Vec3 v(1.0f, 0.0f, 0.0f);
        const Quaternion qx = Quaternion::fromAxisAngle({1.0f, 0.0f, 0.0}, math::Degrees(90.0f));
        const Quaternion qy = Quaternion::fromAxisAngle({0.0f, 1.0f, 0.0}, math::Degrees(90.0f));
        const Quaternion qz = Quaternion::fromAxisAngle({0.0f, 0.0f, 1.0}, math::Degrees(90.0f));

        const Vec3 vx = qx * v;
        const Vec3 vy = qy * v;
        const Vec3 vz = qz * v;


        EXPECT_VEC3_EQ_FLOAT_ARRAY(vx, EXPECTEDX); 
        EXPECT_VEC3_EQ_FLOAT_ARRAY(vy, EXPECTEDY); 
        EXPECT_VEC3_EQ_FLOAT_ARRAY(vz, EXPECTEDZ); 
    }

    TEST(Operations, Dot)
    {
        const float EXPECTED = 58.630005f;

        const Quaternion q1(1.1f, 2.2f, 3.3f, 4.4f);
        const Quaternion q2(7.2f, 6.1f, 4.9f, 4.8f);

        float f1 = q1.dot(q2);
        float f2 = q2.dot(q1);

        EXPECT_FLOAT_EQ(f1, EXPECTED); 
        EXPECT_FLOAT_EQ(f2, EXPECTED); 
    }

    TEST(Operations, Normalize)
    {
        using namespace TestUtils;
        
        const float EXPECTED1[4] {0.18257418f, -0.36514837f, 0.54772258f, 0.73029673f};
        const float EXPECTED2[4] {-0.61716801f, 0.52287847f, 0.42001712f, -0.41144535f};

        const Quaternion q1(1.1f, -2.2f, 3.3f, 4.4f);
        const Quaternion q2(-7.2f, 6.1f, 4.9f, -4.8f);

        Quaternion n1 = q1.normalize();
        Quaternion n2 = q2.normalize();

        EXPECT_QUAT_EQ_FLOAT_ARRAY(n1, EXPECTED1); 
        EXPECT_QUAT_EQ_FLOAT_ARRAY(n2, EXPECTED2); 
    }

    TEST(Operations, AxisAngleToMatrix)
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

        const Mat4 matX = Quaternion::fromAxisAngle({1.0f, 0.0f, 0.0f}, Degrees(45.0f)).toMatrix();
        const Mat4 matY = Quaternion::fromAxisAngle({0.0f, 1.0f, 0.0f}, Degrees(45.0f)).toMatrix();
        const Mat4 matZ = Quaternion::fromAxisAngle({0.0f, 0.0f, 1.0f}, Degrees(45.0f)).toMatrix();

        EXPECT_MAT4_EQ_FLOAT_ARRAY(matX, EXPECTEDX);   
        EXPECT_MAT4_EQ_FLOAT_ARRAY(matY, EXPECTEDY);   
        EXPECT_MAT4_EQ_FLOAT_ARRAY(matZ, EXPECTEDZ);   
    }

    TEST(Operations, EulerAnglesToMatrix)
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

        const Mat4 matX = Quaternion::fromEulerAngles(Degrees(45.0f), Degrees(0.0f), Degrees(0.0f)).toMatrix();
        const Mat4 matY = Quaternion::fromEulerAngles(Degrees(0.0f), Degrees(45.0f), Degrees(0.0f)).toMatrix();
        const Mat4 matZ = Quaternion::fromEulerAngles(Degrees(0.0f), Degrees(0.0f), Degrees(45.0f)).toMatrix();

        EXPECT_MAT4_EQ_FLOAT_ARRAY(matX, EXPECTEDX);   
        EXPECT_MAT4_EQ_FLOAT_ARRAY(matY, EXPECTEDY);   
        EXPECT_MAT4_EQ_FLOAT_ARRAY(matZ, EXPECTEDZ);   
    }

    int main(int argc, char **argv)
    {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
}