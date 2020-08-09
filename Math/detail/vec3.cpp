#include "vec3.h"

vec3::vec3(float newX, float newY, float newZ):
    x(newX),
    y(newY), 
    z(newZ)
{}

vec3::vec3(const vec3& vec):
    x(vec.x), 
    y(vec.y), 
    z(vec.z)
{}

vec3::vec3(float val):
    x(val),
    y(val), 
    z(val)
{}

void vec3::setX(float newX)
{
    x = newX;
}

void vec3::setY(float newY)
{
    y = newY;
}

void vec3::setZ(float newZ)
{
    z = newZ;
}

void vec3::set(float newX, float newY, float newZ)
{
    x = newX;
    y = newY;
    z = newZ;
}

float vec3::getX()
{
    return x;

}
float vec3:: getY()
{
    return y;
}

float vec3::getZ()
{
    return z;
}

float vec3::length()
{
    return sqrt(x*x + y*y + z*z);
}

vec3 vec3::operator+(const vec3& rhs)const 
{
    return vec3(x+rhs.x, y+rhs.y, z+rhs.z);
}

vec3 vec3::operator-(const vec3& rhs)const 
{
    return vec3(x-rhs.x, y-rhs.y, z-rhs.z);
}

vec3 vec3::operator*(const float rhs)const 
{
    return vec3(x*rhs, y*rhs, z*rhs);
}

vec3 vec3::operator/(const float rhs)const 
{
    return (rhs == 0)? vec3(0.0f, 0.0f, 0.0f):vec3(x/rhs, y/rhs, z/rhs);
}

vec3 vec3::operator=(const vec3& rhs) 
{
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    return *this;
}

bool vec3::operator==(const vec3& rhs)const 
{
    return (x == rhs.x)&&(y == rhs.y)&&(z == rhs.z);
}

bool vec3::operator!=(const vec3& rhs)const 
{
    return !(*this == rhs);
}

void vec3::operator+=(const vec3& rhs)
{
    x+=rhs.x;
    y+=rhs.y;
    z+=rhs.z;
}

void vec3::operator-=(const vec3& rhs)
{
    x-=rhs.x;
    y-=rhs.y;
    z-=rhs.z;
}

void vec3::operator*=(const float rhs)
{
    x*=rhs;
    y*=rhs;
    z*=rhs;
}

void vec3::operator/=(const float rhs)
{
    if(rhs!=0){
        x/=rhs;
        y/=rhs;
        z/=rhs;
    }
}

vec3 vec3::operator-()const 
{
    return vec3(-x, -y, -z);
}

float dot(const vec3& lhs, const vec3& rhs)
{
    return lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z;
}

vec3 cross(const vec3& lhs, const vec3& rhs)
{
    float x = lhs.y*rhs.z - lhs.z*rhs.y;
    float y = lhs.z*rhs.x - lhs.x*rhs.z;
    float z = lhs.x*rhs.y - lhs.y*rhs.x;
    return vec3(x,y,z);
}

vec3 normalize(const vec3& vec)
{
    vec3 result;
    float div = sqrt(vec.x*vec.x+vec.y*vec.y+vec.z*vec.z);
    result = vec/div;
    return result;
}

vec3 normalize(vec3 &vec)
{
    float div = sqrt(vec.x*vec.x+vec.y*vec.y+vec.z*vec.z);
    vec = vec/div;
    return vec;
}

vec3 lerp(const vec3& a, const vec3& b, float factor)
{
    return a*(1.0f-factor)+b*factor;
}

