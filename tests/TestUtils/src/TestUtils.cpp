#include <TestUtils.h>

#include <gtest/gtest.h>

#include <Vec2.h>
#include <Vec3.h>
#include <Vec4.h>
#include <Mat4.h>
#include <Quaternion.h>
#include <Transform.h>

namespace TestUtils
{
    // Vec2
        // Expects elements of Vec2 to equal elements in float array
        void EXPECT_VEC2_EQ_FLOAT_ARRAY(const math::Vec2& v, const float* fa)
        {
            for(size_t i = 0; i < 2; i++)
                EXPECT_FLOAT_EQ(v.elements[i], fa[i]);
        }

        // Expects every element of Vec2 to equal float
        void EXPECT_VEC2_EQ_FLOAT(const math::Vec2& v, float f)
        {
            for(size_t i = 0; i < 2; i++)
                EXPECT_FLOAT_EQ(v.elements[i], f);
        }

    // Vec3
        // Expects elements of Vec3 to equal elements in float array
        void EXPECT_VEC3_EQ_FLOAT_ARRAY(const math::Vec3& v, const float* fa)
        {
            for(size_t i = 0; i < 3; i++)
                EXPECT_FLOAT_EQ(v.elements[i], fa[i]);
        }

        // Expects every element of Vec3 to equal float
        void EXPECT_VEC3_EQ_FLOAT(const math::Vec3& v, float f)
        {
            for(size_t i = 0; i < 3; i++)
                EXPECT_FLOAT_EQ(v.elements[i], f);
        }

    // Vec4
        // Expects elements of Vec4 to equal elements in float array
        void EXPECT_VEC4_EQ_FLOAT_ARRAY(const math::Vec4& v, const float* fa)
        {
            for(size_t i = 0; i < 4; i++)
                EXPECT_FLOAT_EQ(v.elements[i], fa[i]);
        }

        // Expects every element of Vec4 to equal float
        void EXPECT_VEC4_EQ_FLOAT(const math::Vec4& v, float f)
        {
            for(size_t i = 0; i < 4; i++)
                EXPECT_FLOAT_EQ(v.elements[i], f);
        }

        // Expects elements in Vec4 equals elements in float array along row
        void EXPECT_VEC4_EQ_FLOAT_ARRAY_ROW(const math::Vec4& v, const float* fa, size_t row)
        {
            for(size_t i = 0; i < 4; i++)
                EXPECT_FLOAT_EQ(v.elements[i], fa[row * 4 + i]);
        }

        // Expects elements in Vec4 equals elements in float array along column
        void EXPECT_VEC4_EQ_FLOAT_ARRAY_COLUMN(const math::Vec4& v, const float* fa, size_t column)
        {
            for(size_t i = 0; i < 4; i++)
                EXPECT_FLOAT_EQ(v.elements[i], fa[i * 4 + column]);
        }

    // Mat4
        // Expects elements of Mat4 equals elements in float array
        void EXPECT_MAT4_EQ_FLOAT_ARRAY(const math::Mat4& m, const float* fa)
        {
            for(size_t column = 0; column < 4; column++)
                for(size_t row = 0; row < 4; row++)
                    EXPECT_FLOAT_EQ(m.elements[column * 4 + row], fa[row * 4 + column]);
        }

        // Expects every element of Mat4 to equal float
        void EXPECT_MAT4_EQ_FLOAT(const math::Mat4& m, float f)
        {
            for(size_t i = 0; i < 4*4; i++)
                EXPECT_FLOAT_EQ(m.elements[i], f);
        }

        // Expects Mat4 left to be equal Mat4 right
        void EXPECT_MAT4_EQ_MAT4(const math::Mat4& ml, const math::Mat4& mr)
        {
            for(size_t i = 0; i < 4*4; i++)
                EXPECT_FLOAT_EQ(ml.elements[i], mr.elements[i]);
        }

    // Quaternion
        // Expects elements in Quaternion equals elements in float array (x, y, z, w)
        void EXPECT_QUAT_EQ_FLOAT_ARRAY(const math::Quaternion& q, const float* fa)
        {
            for(size_t i = 0; i < 3; i++)
                EXPECT_FLOAT_EQ(q.vector.elements[i], fa[i]);

            EXPECT_FLOAT_EQ(q.scalar, fa[3]);
        }

    // Transform
}