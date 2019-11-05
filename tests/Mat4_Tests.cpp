#include <gtest/gtest.h>

#include <Vec4.h>
#include <Mat4.h>

TEST(Initialization, InitializationList_Floats)
{
    using namespace math;

    mat4 mat1 (
        11.01f, 21.02f, 31.03f, 41.04f,
        12.05f, 22.06f, 32.07f, 42.08f,
        13.09f, 23.10f, 33.11f, 43.12f,
        14.13f, 24.14f, 34.15f, 44.16f
    );

    // First row
    EXPECT_EQ(11.01f, mat1.elements[0]); EXPECT_EQ(21.02f, mat1.elements[4]); EXPECT_EQ(31.03f, mat1.elements[8]); EXPECT_EQ(41.04f, mat1.elements[12]);
    
    // Second row
    EXPECT_EQ(12.05f, mat1.elements[1]); EXPECT_EQ(22.06f, mat1.elements[5]); EXPECT_EQ(32.07f, mat1.elements[9]); EXPECT_EQ(42.08f, mat1.elements[13]);
    
    // Third row
    EXPECT_EQ(13.09f, mat1.elements[2]); EXPECT_EQ(23.10f, mat1.elements[6]); EXPECT_EQ(33.11f, mat1.elements[10]); EXPECT_EQ(43.12f, mat1.elements[14]);
    
    // Fourth row
    EXPECT_EQ(14.13f, mat1.elements[3]); EXPECT_EQ(24.14f, mat1.elements[7]); EXPECT_EQ(34.15f, mat1.elements[11]); EXPECT_EQ(44.16f, mat1.elements[15]);
}

TEST(Initialization, InitializationList_Vec4)
{
    using namespace math;

    mat4 mat1 {
        vec4{11.01f, 21.02f, 31.03f, 41.04f},
        vec4{12.05f, 22.06f, 32.07f, 42.08f},
        vec4{13.09f, 23.10f, 33.11f, 43.12f},
        vec4{14.13f, 24.14f, 34.15f, 44.16f}
    };

    // First row
    EXPECT_EQ(11.01f, mat1.elements[0]); EXPECT_EQ(21.02f, mat1.elements[4]); EXPECT_EQ(31.03f, mat1.elements[8]); EXPECT_EQ(41.04f, mat1.elements[12]);
    
    // Second row
    EXPECT_EQ(12.05f, mat1.elements[1]); EXPECT_EQ(22.06f, mat1.elements[5]); EXPECT_EQ(32.07f, mat1.elements[9]); EXPECT_EQ(42.08f, mat1.elements[13]);
    
    // Third row
    EXPECT_EQ(13.09f, mat1.elements[2]); EXPECT_EQ(23.10f, mat1.elements[6]); EXPECT_EQ(33.11f, mat1.elements[10]); EXPECT_EQ(43.12f, mat1.elements[14]);
    
    // Fourth row
    EXPECT_EQ(14.13f, mat1.elements[3]); EXPECT_EQ(24.14f, mat1.elements[7]); EXPECT_EQ(34.15f, mat1.elements[11]); EXPECT_EQ(44.16f, mat1.elements[15]);
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}