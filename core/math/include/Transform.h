#pragma once

#include <Quaternion.h>
#include <Vec3.h>
#include <Mat4.h>

namespace math
{
    class Transform
    {
    private:
        Vec3 position;
        Quaternion orientation;
        Vec3 scale;
        
        Mat4 transformMatrix;
        bool dirtyFlag = true; // Dirty if transform matrix not updated according to position/orientation/scale

    public:
        // Initialization
        Transform(const Vec3& position = {}, const Quaternion& orientation = {}, const Vec3& scale = { 1.0f, 1.0f, 1.0f }) : position(position), orientation(orientation), scale(scale) {}

        // Accessors
        Mat4 toMatrix()
        {
            if(dirtyFlag)
            {
                transformMatrix = Mat4::translate(position) * orientation.toMatrix() * Mat4::scale(scale);
                dirtyFlag = false;
            }
            
            return transformMatrix;
        }

        Vec3 getPosition() const { return position; }
        Quaternion getOrientation() const { return orientation; }
        Vec3 getScale() const { return scale; }

        void setPosition(const Vec3& position) { this->position = position; dirtyFlag = true; }
        void setOrientation(const Quaternion& orientation) { this->orientation = orientation; dirtyFlag = true; }
        void setScale(const Vec3& scale) { this->scale = scale; dirtyFlag = true; }

        // Operations
        Mat4 multiply(const Mat4& matrix)
        {
            return toMatrix() * matrix;
        }

        Mat4 multiply(Transform& transform)
        {
            return toMatrix() * transform.toMatrix();
        }

        // Operators
        Mat4 operator*(const Mat4& matrix) { return multiply(matrix); }
        Mat4 operator*(Transform& transform) { return multiply(transform); }
    };
}