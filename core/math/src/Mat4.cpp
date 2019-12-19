#include <cstring>
#include <iostream>
#include <iomanip>
#include <algorithm>

#include <Mat4.h>

#include <Utils.h>
#include <Vec3.h>
#include <Vec4.h>

namespace math
{

    // Initialization
    Mat4::Mat4(float diagonal) : elements
    {
        diagonal, 0.0f, 0.0f, 0.0f,
        0.0f, diagonal, 0.0f, 0.0f,
        0.0f, 0.0f, diagonal, 0.0f,
        0.0f, 0.0f, 0.0f, diagonal
    } {}

    Mat4::Mat4() : Mat4(1.0f) {}

    Mat4::Mat4(
        float x0, float y0, float z0, float w0,
        float x1, float y1, float z1, float w1,
        float x2, float y2, float z2, float w2,
        float x3, float y3, float z3, float w3
    ) : elements
    {
        x0, y0, z0, w0,
        x1, y1, z1, w1,
        x2, y2, z2, w2,
        x3, y3, z3, w3
    } {}

    // Accessors
	Vec4 Mat4::getRow(size_t row) const
	{
		return Vec4{elements[row + 4 * 0], elements[row + 4 * 1], elements[row + 4 * 2], elements[row + 4 * 3]};
	}

    void Mat4::setRow(size_t row, const Vec4& vector)
	{
		elements[row + 4 * 0] = vector.elements[0];
		elements[row + 4 * 1] = vector.elements[1];
		elements[row + 4 * 2] = vector.elements[2];
		elements[row + 4 * 3] = vector.elements[3];
	}


    Vec4 Mat4::getColumn(size_t column) const
	{
		return Vec4(elements[column * 4 + 0], elements[column * 4 + 1], elements[column * 4 + 2], elements[column * 4 + 3]);
	}

    void Mat4::setColumn(size_t column, const Vec4& vector)
	{
		elements[column * 4 + 0] = vector.elements[0];
		elements[column * 4 + 1] = vector.elements[1];
		elements[column * 4 + 2] = vector.elements[2];
		elements[column * 4 + 3] = vector.elements[3];
	}

    // Operations
    Mat4& Mat4::multiply(const Mat4& other)
    {
        Mat4 temp(0.0f);

        for(size_t column = 0; column < 4; column++)
            for(size_t row = 0; row < 4; row++)
            {
                for(size_t e = 0; e < 4; e++)
                    temp.elements[row + column * 4] += elements[row + e * 4] * other.elements[e + column * 4];
            }                

        memcpy(elements, temp.elements, 4 * 4 * sizeof(float));
        return *this;
    }

    Vec4 Mat4::multiply(const Vec4& vector) const
    {
        return Vec4
		(
			elements[0] * vector.elements[0] + elements[4] * vector.elements[1] + elements[8]  * vector.elements[2] + elements[12] * vector.elements[3],
			elements[1] * vector.elements[0] + elements[5] * vector.elements[1] + elements[9]  * vector.elements[2] + elements[13] * vector.elements[3],
			elements[2] * vector.elements[0] + elements[6] * vector.elements[1] + elements[10] * vector.elements[2] + elements[14] * vector.elements[3],
			elements[3] * vector.elements[0] + elements[7] * vector.elements[1] + elements[11] * vector.elements[2] + elements[15] * vector.elements[3]
        );
    }

    // Operators
    Vec4 Mat4::operator*(const Vec4& vector) const { return multiply(vector); }

    Mat4 Mat4::operator*(const Mat4& other) const { return Mat4(*this).multiply(other); }
    Mat4& Mat4::operator*=(const Mat4& other) { return multiply(other); }

	std::ostream& operator<<(std::ostream& out, const math::Mat4& matrix)
	{
    	for(size_t column = 0; column < 4; column++)
        {
    	    for(size_t row = 0; row < 4; row++)
    	    {
    	        out << std::setw(3) << matrix.elements[column * 4 + row] << ", ";
    	    }
    	    out << "\n";
        }

		return out;
	}

    // Generators
    Mat4 Mat4::identity()
    {
        return Mat4();
    }

    Mat4 Mat4::translate(const Vec3& vector)
    {
		return Mat4 
		(
			1.0f,		        0.0f,		        0.0f,		        0.0f,
			0.0f,		        1.0f,		        0.0f,		        0.0f,
			0.0f,		        0.0f,		        1.0f,		        0.0f,
			vector.elements[0], vector.elements[1], vector.elements[2], 1.0f
        );
    }

    Mat4 Mat4::rotate(Radians angle, const Vec3& axis)
    {
		float c = cosf(angle);
		float s = sinf(angle);
		float omc = 1.0f - c;

		float x = axis.elements[0], y = axis.elements[1], z = axis.elements[2];

		return Mat4 
		(
			c+omc*x*x, 		omc*x*y-s*z, 	omc*x*z+s*y, 	0.0f,
			omc*x*y+s*z,	c+omc*y*y,		omc*y*z-s*x, 	0.0f,
			omc*x*z-s*y,	omc*y*z+s*x,	c+omc*z*z, 		0.0f,
			0.0f, 			0.0f, 			0.0f, 			1.0f
        );
    }

    Mat4 Mat4::scale(const Vec3& vector)
	{
		return Mat4 
		(
			vector.elements[0], 	0.0f, 				0.0f, 				0.0f,
			0.0f, 					vector.elements[1], 0.0f, 				0.0f,
			0.0f, 					0.0f, 				vector.elements[2], 0.0f,
			0.0f, 					0.0f, 				0.0f, 				1.0f
        );
	}

    Mat4 Mat4::perspective(float left, float right, float bottom, float top, float near, float far)
    {
        return Mat4
        (
            (2.0f*near)/(right-left),   0.0f,                           0.0f,                           0.0f,
            0.0f,                       (2.0f*near)/(top-bottom),       0.0f,                           0.0f,
            (right+left)/(right-left),  (top+bottom)/(top-bottom),      -(far+near)/(far-near),        -1.0f,
            0.0f,                       0.0f,                           -(2.0f*far*near)/(far-near),    0.0f
        );
    }

	Mat4 Mat4::perspective(Radians fov, float aspectratio, float near, float far)
	{	
        float tangent = tanf(fov/2.0f);
        float top = near * tangent;
        float right = top * aspectratio;

		return perspective(-right, right, -top, top, near, far);
	}

    Mat4 Mat4::view(const Vec3& lookFrom, const Vec3& lookAt, const Vec3& up)
	{
        Vec3 forward = (lookFrom-lookAt).normalize(); // Direction from lookAt to lookFrom
        Vec3 left = (up.cross(forward)).normalize();  // Left vector from lookAt to lookFrom
        Vec3 ups = forward.cross(left);

        return Mat4
        (
            left.elements[0],    ups.elements[0],    forward.elements[0],    0.0f,
            left.elements[1],    ups.elements[1],    forward.elements[1],    0.0f,
            left.elements[2],    ups.elements[2],    forward.elements[2],    0.0f,
            -left.elements[0] * lookFrom.elements[0] - left.elements[1] * lookFrom.elements[1] - left.elements[2] * lookFrom.elements[2],   -ups.elements[0] * lookFrom.elements[0] - ups.elements[1] * lookFrom.elements[1] - ups.elements[2] * lookFrom.elements[2],  -forward.elements[0] * lookFrom.elements[0] - forward.elements[1] * lookFrom.elements[1] - forward.elements[2] * lookFrom.elements[2],                   1.0f
        );
    }
}