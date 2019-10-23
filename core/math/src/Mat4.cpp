#include <cstring>
#include <Utils.h>
#include <Mat4.h>
#include <Vec3.h>
#include <Vec4.h>

namespace math
{
    mat4::mat4() : columns{ vec4(), vec4(), vec4(), vec4() } {};
    mat4::mat4(const mat4& other) : columns{other.columns[0], other.columns[1], other.columns[2], other.columns[3]} {};

    mat4& mat4::multiply(const mat4& other)
    {
        mat4 temp;

        for(size_t row = 0; row < 4; row++)
        {
            for(size_t column = 0; column < 4; column++)
            {
                float sum = 0.0f;
                for(size_t e = 0; e < 4; e++)
                {
                    sum += elements[row + e * 4] * other.elements[e + column * 4];
                }
                temp.elements[row + column * 4] = sum;
            }                
        }

        memcpy(elements, temp.elements, 4 * 4 * sizeof(float));
        return *this;
    }

    vec4 mat4::multiply(const vec4& vector) const
    {
        vec4 returnVector;

        returnVector.x = vector.x * elements[0] + vector.y * elements[4] + vector.z * elements[8] + vector.w * elements[12];
        returnVector.y = vector.x * elements[1] + vector.y * elements[5] + vector.z * elements[9] + vector.w * elements[13];
        returnVector.z = vector.x * elements[2] + vector.y * elements[6] + vector.z * elements[10] + vector.w * elements[14];
        returnVector.w = vector.x * elements[3] + vector.y * elements[7] + vector.z * elements[11] + vector.w * elements[15];

        return returnVector;
    }

    vec4 mat4::operator *(const vec4& vector) const { return multiply(vector); }

    mat4 mat4::operator *(const mat4& other) const { return mat4(*this).multiply(other); }
    mat4& mat4::operator *=(const mat4& other) { return multiply(other); }

    mat4 mat4::identity()
    {
        mat4 returnMatrix;

        for(size_t i = 0; i < 4; i++)
            returnMatrix.columns[i].elements[i] = 0.0f;

        return returnMatrix;
    }

    mat4 mat4::translate(const vec3& vector)
    {
        mat4 returnMatrix = identity();

        returnMatrix.columns[3].x = vector.x;
        returnMatrix.columns[3].y = vector.y;
        returnMatrix.columns[3].z = vector.z;

        return returnMatrix;
    }

    mat4 mat4::rotate(float angle, const vec3& axis)
    {
        mat4 returnMatrix = identity();
		
		float r = toRadians(angle);
		float c = cosf(r);
		float s = sinf(r);
		float omc = 1.0f - c;
			
		float x = axis.x;
		float y = axis.y;
		float z = axis.z;

		returnMatrix.columns[0].x = x * x * omc + c;
		returnMatrix.columns[0].y = x * y * omc + z * s;
		returnMatrix.columns[0].z = x * z * omc - y * s;
		returnMatrix.columns[0].w = 0.0f;

		returnMatrix.columns[1].x = x * y * omc - z * s;
		returnMatrix.columns[1].y = y * y * omc + c;
		returnMatrix.columns[1].z = y * z * omc + x * s;
		returnMatrix.columns[1].w = 0.0f;

		returnMatrix.columns[2].x = x * z * omc + y * s;
		returnMatrix.columns[2].y = y * z * omc - x * s;
		returnMatrix.columns[2].z = z * z * omc + c;
		returnMatrix.columns[2].w = 0.0f;

		returnMatrix.columns[3].x = 0.0f;
		returnMatrix.columns[3].y = 0.0f;
		returnMatrix.columns[3].z = 0.0f;
		returnMatrix.columns[3].w = 1.0f;

		return returnMatrix;
    }

    mat4 mat4::scale(const vec3& vector)
	{
		mat4 returnMatrix = identity();
	
		returnMatrix.columns[0].x = vector.x;
		returnMatrix.columns[1].y = vector.y;
		returnMatrix.columns[2].z = vector.z;
	
		return returnMatrix;
	}

	mat4 mat4::perspective(float fov, float aspectRatio, float near, float far)
	{
		mat4 returnMatrix = mat4();
	
		fov = toRadians(fov);
	
		returnMatrix.columns[0].x = 1 / (aspectRatio * tanf(fov / 2));
		returnMatrix.columns[0].y = 0;
		returnMatrix.columns[0].z = 0;
		returnMatrix.columns[0].w = 0;
	
		returnMatrix.columns[1].x = 0;
		returnMatrix.columns[1].y = 1 / (tanf(fov / 2));
		returnMatrix.columns[1].z = 0;
		returnMatrix.columns[1].w = 0;
	
		returnMatrix.columns[2].x = 0;
		returnMatrix.columns[2].y = 0;
		returnMatrix.columns[2].z = -(far + near) / (far - near);
		returnMatrix.columns[2].w = -1;
	
		returnMatrix.columns[3].x = 0;
		returnMatrix.columns[3].y = 0;
		returnMatrix.columns[3].z = -(2 * far * near) / (far - near);
		returnMatrix.columns[3].w = 0;
	
		return returnMatrix;
	}

    mat4 mat4::view(const vec3& lookFrom, const vec3& lookAt, const vec3& up)
	{
		vec3 zaxis = (lookFrom - lookAt).normalize();
		vec3 xaxis = (up.cross(zaxis)).normalize();
		vec3 yaxis = zaxis.cross(xaxis);

		mat4 orientation = identity();
		orientation.columns[0] = vec4(xaxis.x, yaxis.x, zaxis.x, 0.0f);
		orientation.columns[1] = vec4(xaxis.y, yaxis.y, zaxis.y, 0.0f);
		orientation.columns[2] = vec4(xaxis.z, yaxis.z, zaxis.z, 0.0f);
		orientation.columns[3] = vec4(0.0f, 0.0f, 0.0f, 1.0f);

		mat4 translation = identity();
		translation.columns[0] = vec4(1.0f, 0.0, 0.0f, 0.0f);
		translation.columns[1] = vec4(0.0f, 1.0f, 0.0f, 0.0f);
		translation.columns[2] = vec4(0.0f, 0.0f, 1.0f, 0.0f);
		translation.columns[3] = vec4(-lookFrom.x, -lookFrom.y, -lookFrom.z, 1.0f);
		
		return orientation * translation;
	}
    
}