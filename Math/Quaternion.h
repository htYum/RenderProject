#ifndef QUATERNION_H
#define QUATERNION_H

#include "Math/detail/vec3.h"
#include "Math/detail/Matrix4x4.h"
#include "Math/detail/functions.h"

class Quaternion
{
public:
    float x,y,z,w;

    Quaternion();
    Quaternion(float _x,float _y, float _z, float _w);
    Quaternion(float yaw, float pitch, float roll);
    ~Quaternion() = default;

    void setValues(float _x, float _y, float _z, float _w);
    void setAngles(float yaw, float pitch, float roll);
    void rotate(vec3 axis, float angle);

    Quaternion inverse() const;
    Quaternion conjugate() const;
    vec3 eulerAngle() const;
    mat4x4 toMatrix();

    static float dotQuaternion(const Quaternion& lhs, const Quaternion& rhs);
    static Quaternion lerp(const Quaternion& lhs, const Quaternion& rhs, float factor);
    static Quaternion slerp(const Quaternion& lhs, const Quaternion& rhs, float factor);
    static float getAngle(const Quaternion& lhs, const Quaternion& rhs);

    Quaternion operator+(const Quaternion& rhs) const;
    Quaternion operator-(const Quaternion& rhs) const;
    Quaternion operator*(float rhs) const;
    Quaternion operator/(float rhs) const;
    Quaternion operator*(const Quaternion& rhs) const;
    vec3 operator*(const vec3& rhs) const;
};

#endif // QUATERNION_H
