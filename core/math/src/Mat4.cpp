#include <cstring>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <Utils.h>

#include <Mat4.h>
#include <Vec3.h>
#include <Vec4.h>

namespace math
{
    // Accessors
	vec4 mat4::getRow(size_t row) const
	{
		return vec4{elements[row + 4 * 0], elements[row + 4 * 1], elements[row + 4 * 2], elements[row + 4 * 3]};
	}

    void mat4::setRow(size_t row, const vec4& vector)
	{
		elements[row + 4 * 0] = vector.elements[0];
		elements[row + 4 * 1] = vector.elements[1];
		elements[row + 4 * 2] = vector.elements[2];
		elements[row + 4 * 3] = vector.elements[3];
	}


    vec4 mat4::getColumn(size_t column) const
	{
		return vec4{elements[column * 4 + 0], elements[column * 4 + 1], elements[column * 4 + 2], elements[column * 4 + 3]};
	}

    void mat4::setColumn(size_t column, const vec4& vector)
	{
		elements[column * 4 + 0] = vector.elements[0];
		elements[column * 4 + 1] = vector.elements[1];
		elements[column * 4 + 2] = vector.elements[2];
		elements[column * 4 + 3] = vector.elements[3];
	}

    // Operations
    mat4& mat4::multiply(const mat4& other)
    {
        mat4 temp;

        for(size_t column = 0; column < 4; column++)
            for(size_t row = 0; row < 4; row++)
            {
                for(size_t e = 0; e < 4; e++)
                    temp.elements[row + column * 4] += elements[row + e * 4] * other.elements[e + column * 4];
            }                

        memcpy(elements, temp.elements, 4 * 4 * sizeof(float));
        return *this;
    }

    vec4 mat4::multiply(const vec4& vector) const
    {
        return vec4
		{
			elements[0] * vector.elements[0] + elements[4] * vector.elements[1] + elements[8]  * vector.elements[2] + elements[12] * vector.elements[3],
			elements[1] * vector.elements[0] + elements[5] * vector.elements[1] + elements[9]  * vector.elements[2] + elements[13] * vector.elements[3],
			elements[2] * vector.elements[0] + elements[6] * vector.elements[1] + elements[10] * vector.elements[2] + elements[14] * vector.elements[3],
			elements[3] * vector.elements[0] + elements[7] * vector.elements[1] + elements[11] * vector.elements[2] + elements[15] * vector.elements[3]
        };
    }

    // Operators
    vec4 mat4::operator*(const vec4& vector) const { return multiply(vector); }

    mat4 mat4::operator*(const mat4& other) const { return mat4(*this).multiply(other); }
    mat4& mat4::operator*=(const mat4& other) { return multiply(other); }

	std::ostream& operator<<(std::ostream& out, const math::mat4& matrix)
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
    mat4 mat4::identity()
    {
        return mat4
		{
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
        };
    }

    mat4 mat4::translate(const vec3& vector)
    {
		return mat4 
		{
			1.0f,		        0.0f,		        0.0f,		        0.0f,
			0.0f,		        1.0f,		        0.0f,		        0.0f,
			0.0f,		        0.0f,		        1.0f,		        0.0f,
			vector.elements[0], vector.elements[1], vector.elements[2], 1.0f
        };
    }

    mat4 mat4::rotate(float angle, const vec3& axis)
    {
		float r = toRadians(angle);
		float c = cosf(r);
		float s = sinf(r);
		float omc = 1.0f - c;

		float x = axis.elements[0], y = axis.elements[1], z = axis.elements[2];

		return mat4 
		{
			c+omc*x*x, 		omc*x*y-s*z, 	omc*x*z+s*y, 	0.0f,
			omc*x*y+s*z,	c+omc*y*y,		omc*y*z-s*x, 	0.0f,
			omc*x*z-s*y,	omc*y*z+s*x,	c+omc*z*z, 		0.0f,
			0.0f, 			0.0f, 			0.0f, 			1.0f
        };
    }

    mat4 mat4::scale(const vec3& vector)
	{
		return mat4 
		{
			vector.elements[0], 	0.0f, 				0.0f, 				0.0f,
			0.0f, 					vector.elements[1], 0.0f, 				0.0f,
			0.0f, 					0.0f, 				vector.elements[2], 0.0f,
			0.0f, 					0.0f, 				0.0f, 				1.0f
        };
	}

    mat4 mat4::perspective(float left, float right, float bottom, float top, float near, float far)
    {
        return mat4
        {
            (2.0f*near)/(right-left),   0.0f,                           0.0f,                           0.0f,
            0.0f,                       (2.0f*near)/(top-bottom),       0.0f,                           0.0f,
            (right+left)/(right-left),  (top+bottom)/(top-bottom),      -(far+near)/(far-near),        -1.0f,
            0.0f,                       0.0f,                           -(2.0f*far*near)/(far-near),    0.0f
        };
    }

	mat4 mat4::perspective(float fov, float aspectratio, float near, float far)
	{	
		fov = toRadians(fov);

        float tangent = tanf(fov/2.0f);
        float top = near * tangent;
        float right = top * aspectratio;

		return perspective(-right, right, -top, top, near, far);
	}

    mat4 mat4::view(const vec3& lookFrom, const vec3& lookAt, const vec3& up)
	{
        vec3 forward = (lookFrom-lookAt).normalize(); // Direction from lookAt to lookFrom
        vec3 left = (up.cross(forward)).normalize();  // Left vector from lookAt to lookFrom
        vec3 ups = forward.cross(left);

        return mat4
        {
            left.elements[0],    ups.elements[0],    forward.elements[0],    0.0f,
            left.elements[1],    ups.elements[1],    forward.elements[1],    0.0f,
            left.elements[2],    ups.elements[2],    forward.elements[2],    0.0f,
            -left.elements[0] * lookFrom.elements[0] - left.elements[1] * lookFrom.elements[1] - left.elements[2] * lookFrom.elements[2],   -ups.elements[0] * lookFrom.elements[0] - ups.elements[1] * lookFrom.elements[1] - ups.elements[2] * lookFrom.elements[2],  -forward.elements[0] * lookFrom.elements[0] - forward.elements[1] * lookFrom.elements[1] - forward.elements[2] * lookFrom.elements[2],                   1.0f
        };
    }
}