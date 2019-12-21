#pragma once

#include <Quaternion.h>
#include <Vec3.h>

namespace math
{
    class Transform
    {
    private:
        Vec3 position;
        Quaternion orientation;
        Vec3 scale;
        
        Mat4 transform;
        bool dirtyFlag = true; // Dirty if transform matrix not updated according to position/orientation/scale

    public:
        Transform() {}
        Transform(const Vec3& position, const Quaternion& orientation, const Vec3& scale) : position(position), orientation(orientation), scale(scale) {}

        Mat4 toMatrix()
        {
            if(dirtyFlag)
            {
                transform = Mat4::translate(position) * orientation.toMatrix() * Mat4::scale(scale);
                dirtyFlag = false;
            }
            
            return transform;
        }

        Vec3 getPosition() const { return position; }
        Quaternion getOrientation() const { return orientation; }
        Vec3 getScale() const { return scale; }

        void setPosition(const Vec3& position) { this->position = position; dirtyFlag = true; }
        void setOrientation(const Quaternion& orientation) { this->orientation = orientation; dirtyFlag = true; }
        void setScale(const Vec3& scale) { this->scale = scale; dirtyFlag = true; }
    };
}