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
    // Initialization
	mat4::mat4() : elements{} {};

	mat4::mat4(
        float x0, float y0, float z0, float w0,
        float x1, float y1, float z1, float w1,
        float x2, float y2, float z2, float w2,
        float x3, float y3, float z3, float w3
    ) : elements {
		x0, x1, x2, x3, // Column 0
		y0, y1, y2, y3, // Column 1
		z0, z1, z2, z3, // Column 2
		w0, w1, w2, w3  // Column 3
	} {};

    mat4::mat4(
        const vec4& row0,
        const vec4& row1,
        const vec4& row2,
        const vec4& row3
    ) : elements {
		row0.elements[0], row1.elements[0], row2.elements[0], row3.elements[0],
		row0.elements[1], row1.elements[1], row2.elements[1], row3.elements[1],
		row0.elements[2], row1.elements[2], row2.elements[2], row3.elements[2],
		row0.elements[3], row1.elements[3], row2.elements[3], row3.elements[3]
	} {};

    // Accessors
	vec4 mat4::getRow(size_t row) const
	{
		return vec4(elements[row + 4 * 0], elements[row + 4 * 1], elements[row + 4 * 2], elements[row + 4 * 3]);
	}

    void mat4::setRow(size_t row, const vec4& vector)
	{
		elements[4 * 0 + row] = vector.elements[0];
		elements[4 * 1 + row] = vector.elements[1];
		elements[4 * 2 + row] = vector.elements[2];
		elements[4 * 3 + row] = vector.elements[3];
	}


    vec4 mat4::getColumn(size_t column) const
	{
		return vec4(elements[column * 4 + 0], elements[column * 4 + 1], elements[column * 4 + 2], elements[column * 4 + 3]);
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

        for(size_t row = 0; row < 4; row++)
            for(size_t column = 0; column < 4; column++)
            {
                float sum = 0.0f;
                for(size_t e = 0; e < 4; e++)
                    sum += elements[row + e * 4] * other.elements[e + column * 4];
                temp.elements[row + column * 4] = sum;
            }                

        memcpy(elements, temp.elements, 4 * 4 * sizeof(float));
        return *this;
    }

    vec4 mat4::multiply(const vec4& vector) const
    {
        return vec4
		(
			vector.elements[0] * elements[0] + vector.elements[1] * elements[4] + vector.elements[2] * elements[8]  + vector.elements[3] * elements[12],
			vector.elements[0] * elements[1] + vector.elements[1] * elements[5] + vector.elements[2] * elements[9]  + vector.elements[3] * elements[13],
			vector.elements[0] * elements[2] + vector.elements[1] * elements[6] + vector.elements[2] * elements[10] + vector.elements[3] * elements[14],
			vector.elements[0] * elements[3] + vector.elements[1] * elements[7] + vector.elements[2] * elements[11] + vector.elements[3] * elements[15]
		);
    }

    // Operators
    vec4 mat4::operator*(const vec4& vector) const { return multiply(vector); }

    mat4 mat4::operator*(const mat4& other) const { return mat4(*this).multiply(other); }
    mat4& mat4::operator*=(const mat4& other) { return multiply(other); }

	std::ostream& operator<<(std::ostream& out, const math::mat4& matrix)
	{
    	for(size_t row = 0; row < 4; row++)
    	{
    		for(size_t column = 0; column < 4; column++)
    	        out << std::setw(3) << matrix.elements[column * 4 + row] << ", ";
    	    out << "\n";
    	}

		return out;
	}

    // Generators
    mat4 mat4::identity()
    {
        return mat4
		(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
    }

    mat4 mat4::translate(const vec3& vector)
    {
		return mat4 
		(
			1.0f,		0.0f,		0.0f,		vector.elements[0],
			0.0f,		1.0f,		0.0f,		vector.elements[1],
			0.0f,		0.0f,		1.0f,		vector.elements[2],
			0.0f,		0.0f,		0.0f,		1.0f
		);
    }

    mat4 mat4::rotate(float angle, const vec3& axis)
    {
		float r = toRadians(angle);
		float c = cosf(r);
		float s = sinf(r);
		float omc = 1.0f - c;

		float x = axis.elements[0], y = axis.elements[1], z = axis.elements[2];

		// Source for the math used: https://apprize.info/game/3d/3.html
		return mat4 
		(
			c+omc*x*x, 		omc*x*y+s*z, 	omc*x*z-s*y, 	0.0f,
			omc*x*y-s*z,	c+omc*y*y,		omc*y*z+s*x, 	0.0f,
			omc*x*z+s*y,	omc*y*z-s*x,	c+omc*z*z, 		0.0f,
			0.0f, 			0.0f, 			0.0f, 			1.0f
		);
    }

    mat4 mat4::scale(const vec3& vector)
	{
		return mat4 
		(
			vector.elements[0], 	0.0f, 				0.0f, 				0.0f,
			0.0f, 					vector.elements[1], 0.0f, 				0.0f,
			0.0f, 					0.0f, 				vector.elements[2], 0.0f,
			0.0f, 					0.0f, 				0.0f, 				1.0f
		);
	}

	mat4 mat4::perspective(float fov, float aspectratio, float near, float far)
	{	
		fov = toRadians(fov);

		// Source for the math used: http://ogldev.atspace.co.uk/www/tutorial12/tutorial12.html
		return mat4
		(
			1.0f/(aspectratio*tanf(fov/2.0f)),	0.0f,					0.0f,						0.0f,
			0.0f, 								1.0f/tanf(fov/2.0f),	0.0f,						0.0f,
			0.0f, 								0.0f, 					(-near-far)/(near-far), 	(2.0f*far*near)/(near-far),
			0.0f, 								0.0f, 					1.0f,						0.0f
		);
	}

    mat4 mat4::view(const vec3& lookFrom, const vec3& lookAt, const vec3& up)
	{
		vec3 zaxis = (lookFrom - lookAt).normalize();
		vec3 xaxis = (up.cross(zaxis)).normalize();
		vec3 yaxis = zaxis.cross(xaxis);

		// Source for the math used: https://www.3dgep.com/understanding-the-view-matrix/
		return mat4
		(
			xaxis.elements[0], 		yaxis.elements[0], 		zaxis.elements[0],		0.0f,
			xaxis.elements[1], 		yaxis.elements[1], 		zaxis.elements[1],		0.0f,
			xaxis.elements[2], 		yaxis.elements[2], 		zaxis.elements[2],		0.0f,
			-xaxis.dot(lookFrom),	-yaxis.dot(lookFrom),	-zaxis.dot(lookFrom),	1.0f
		);
	}
}