#include "Quaternion.h"

#include <QDebug>

Quaternion::Quaternion():
    x(0),
    y(0),
    z(0),
    w(1)
{

}

Quaternion::Quaternion(float _x, float _y, float _z, float _w)
{
    float mag = _x*_x +_y*_y + _z*_z + _w*_w;
    x = _x / mag;
    y = _y / mag;
    z = _z / mag;
    w = _w / mag;
}

Quaternion::Quaternion(float yaw, float pitch, float roll)
{
    this->setAngles(yaw,pitch,roll);
}

void Quaternion::setValues(float _x, float _y, float _z, float _w)
{
    x = _x;
    y = _y;
    z = _z;
    w = _w;
}

void Quaternion::setAngles(float yaw, float pitch, float roll)
{
    float angle = yaw * 0.5f;
    float sinYaw = sin(angle);
    float cosYaw = cos(angle);

    angle = pitch * 0.5f;
    float sinPitch = sin(angle);
    float cosPitch = cos(angle);

    angle = roll * 0.5f;
    float sinRoll = sin(angle);
    float cosRoll = cos(angle);

    float _x = cosRoll*cosPitch*sinYaw - sinRoll*sinPitch*cosYaw;
    float _y = cosRoll*sinPitch*cosYaw + sinRoll*cosPitch*sinYaw;
    float _z = sinRoll*cosPitch*cosYaw - cosRoll*sinPitch*sinYaw;
    float _w = cosRoll*cosPitch*cosYaw + sinRoll*sinPitch*sinYaw;

    float mag = _x*_x +_y*_y + _z*_z + _w*_w;
    x = _x / mag;
    y = _y / mag;
    z = _z / mag;
    w = _w / mag;
}

void Quaternion::rotate(vec3 axis, float angle)
{
    angle = radians(angle);
    axis = normalize(axis);
    angle *= 0.5f;
    float sinAngle = sin(angle);
    x = axis.x * sinAngle;
    y = axis.y * sinAngle;
    z = axis.z * sinAngle;
    w = cos(angle);
}

Quaternion Quaternion::inverse() const
{
    return Quaternion(-x, -y, -z, w);
}

Quaternion Quaternion::conjugate() const
{
    return Quaternion(-x, -y, -z, w);
}

vec3 Quaternion::eulerAngle() const
{
    float yaw = atan2(2*(w*x + z*y), 1 - 2*(x*x + y*y));
    float pitch = asin(2*(w*y - x*z));
    float roll = atan2(2*(w*z + x*y), 1 - 2*(z*z + y*y));
    return vec3(angles(yaw), angles(pitch), angles(roll));
}

mat4x4 Quaternion::toMatrix()
{
    mat4x4 result(1.0f - 2.0f*y*y - 2.0f*z*z,   2.0f*x*y - 2.0f*z*w,        2.0f*x*z + 2.0f*y*w,        0.0f,
                  2.0f*x*y + 2.0f*z*w,          1.0f - 2.0f*x*x - 2.0f*z*z, 2.0f*y*z - 2.0f*x*w,        0.0f,
                  2.0f*x*z - 2.0f*y*w,          2.0f*y*z + 2.0f*x*w,        1.0f - 2.0f*x*x - 2.0f*y*y, 0.0f,
                  0.0f,                         0.0f,                       0.0f,                       1.0f);
    result = result.getTranspose();
    return result;
}

float Quaternion::dotQuaternion(const Quaternion &lhs, const Quaternion &rhs)
{
    return lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z + lhs.w*rhs.w;
}

Quaternion Quaternion::lerp(const Quaternion &lhs, const Quaternion &rhs,float factor)
{
    return Quaternion((1-factor)*lhs.x + factor*rhs.x,
                      (1-factor)*lhs.y + factor*rhs.y,
                      (1-factor)*lhs.z + factor*rhs.z,
                      (1-factor)*lhs.w + factor*rhs.w);
}

Quaternion Quaternion::slerp(const Quaternion &lhs, const Quaternion &rhs, float factor)
{
    float cosAngle = dotQuaternion(lhs, rhs);

    float flag;
    if(cosAngle < 0){
        cosAngle = -cosAngle;
        flag = -1.0f;
    }
    else flag = 1.0f;

    float f1, f2;
    if(cosAngle < 1.0f - 0.000001f){
        f1 = 1.0f - factor;
        f2 = factor;
    }
    else{
        float angle = acos(cosAngle);
        float sinAngle = sin(angle);
        float facAngle = factor*angle;
        float oneDivSinAngle = 1.0f/sinAngle;
        f2 = sin(facAngle)*oneDivSinAngle;
        f1 = sin(angle - facAngle)*oneDivSinAngle;
    }
    f2 *= flag;

    return Quaternion(f1*lhs.x + f2*rhs.x,
                      f1*lhs.y + f2*rhs.y,
                      f1*lhs.z + f2*rhs.z,
                      f1*lhs.w + f2*rhs.w);
}

float Quaternion::getAngle(const Quaternion &lhs, const Quaternion &rhs)
{
    float cosAngle = dotQuaternion(lhs, rhs);
    if(cosAngle < 0){
        cosAngle = -cosAngle;
    }
    return 2.0f*angles(acos(cosAngle));
}

Quaternion Quaternion::operator+(const Quaternion &rhs) const
{
    Quaternion result(x+rhs.x, y+rhs.y, z+rhs.z, w+rhs.w);
    return result;
}

Quaternion Quaternion::operator-(const Quaternion &rhs) const
{
    Quaternion result(x-rhs.x, y-rhs.y, z-rhs.z, w-rhs.w);
    return result;
}

Quaternion Quaternion::operator*(float rhs) const
{
    Quaternion result(x*rhs, y*rhs, z*rhs, w*rhs);
    return result;
}

vec3 Quaternion::operator*(const vec3& rhs) const
{
    vec3 v(x,y,z);
    return v*2.0f* dot(v,rhs) + rhs*(w*w - dot(v,v)) + dot(v,rhs)*2.0f*w;
}

Quaternion Quaternion::operator/(float rhs) const
{
    if(rhs != 0){
        Quaternion result(x/rhs, y/rhs, z/rhs, w/rhs);
        return result;
    }
    else return Quaternion(0,0,0,1);
}

Quaternion Quaternion::operator*(const Quaternion &rhs) const
{
    vec3 v1(x,y,z);
    vec3 v2(rhs.x, rhs.y, rhs.z);
    vec3 v3 = cross(v1, v2) + v2*w + v1*rhs.w;
    return Quaternion(v3.x, v3.y, v3.z, w*rhs.w - dot(v1, v2));
}
