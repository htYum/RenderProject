#include "vec4.h"

vec4::vec4(float newX, float newY, float newZ, float newW):
    x(newX),
    y(newY),
    z(newZ),
    w(newW)
{}

vec4::vec4(const vec4& vec):
    x(vec.x),
    y(vec.y),
    z(vec.z),
    w(vec.w)
{}

vec4::vec4(float val):
    x(val), 
    y(val), 
    z(val), 
    w(val)
{}

vec4::vec4(const vec3& vec, float val):
    x(vec.x),
    y(vec.y),
    z(vec.z),
    w(val)
{}

vec4::vec4(const vec3& vec):
    x(vec.x),
    y(vec.y),
    z(vec.z),
    w(1.0f)
{}

vec4::vec4(float val, const vec3& vec):
    x(val),
    y(vec.x),
    z(vec.y),
    w(vec.z)
{}

void vec4::setX(float newX)
{
    x = newX;
}

void vec4::setY(float newY)
{
    y = newY;
}

void vec4::setZ(float newZ)
{
    z = newZ;
}
    
void vec4::setW(float newW)
{
    w = newW;
}

void vec4::set(float newX, float newY, float newZ, float newW)
{
    x = newX;
    y = newY;
    z = newZ;
    w = newW;
}

void vec4::set(float val, const vec3& vec)
{
    x = val;
    y = vec.x;
    z = vec.y;
    w = vec.z;
}

void vec4::set(const vec3& vec, float val)
{
    x = vec.x;
    y = vec.y;
    z = vec.z;
    w = val;
}

float vec4::getX()
{
    return x;
}

float vec4::getY()
{
    return y;
}

float vec4::getZ()
{
    return z;
}

float vec4::getW()
{
    return w;
}

float vec4::length()
{
    return sqrt(x*x + y*y + z*z + w*w);
}

vec4 vec4::operator+(const vec4& rhs)const 
{
    return vec4(x+rhs.x, y+rhs.y, z+rhs.z, w+rhs.w);
}

vec4 vec4::operator-(const vec4& rhs)const 
{
    return vec4(x-rhs.x, y-rhs.y, z-rhs.z, w-rhs.w);
}
   
vec4 vec4::operator*(const float rhs)const 
{
    return vec4(x*rhs, y*rhs, z*rhs, w*rhs);
}

vec4 vec4::operator/(const float rhs)const 
{
    return (rhs == 0)? vec4(0.0f, 0.0f, 0.0f, 0.0f):vec4(x/rhs, y/rhs, z/rhs, w/rhs);
}

vec4 vec4::operator=(const vec4& rhs) 
{
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    w = rhs.w;
    return *this;
}

bool vec4::operator==(const vec4& rhs)const 
{
    return (x == rhs.x)&&(y == rhs.y)&&(z == rhs.z)&&(w == rhs.w);
}

bool vec4::operator!=(const vec4& rhs)const 
{
    return !(*this == rhs);
}

void vec4::operator+=(const vec4& rhs)
{
    x+=rhs.x;
    y+=rhs.y;
    z+=rhs.z;
    w+=rhs.w;
}

void vec4::operator-=(const vec4& rhs)
{
    x-=rhs.x;
    y-=rhs.y;
    z-=rhs.z;
    w-=rhs.w;
}
    
void vec4::operator*=(const float rhs)
{
    x*=rhs;
    y*=rhs;
    z*=rhs;
    w*=rhs;
}
    
void vec4::operator/=(const float rhs)
{
    if(rhs!=0){
        x/=rhs;
        y/=rhs;
        z/=rhs;
        w/=rhs;
    }
}

vec4 vec4::operator-()const 
{
    return vec4(-x, -y, -z, -w);
}

float dot(const vec4& lhs, const vec4& rhs)
{
    return lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z + lhs.w*rhs.w;
}

vec4 lerp(const vec4& a, const vec4& b, float factor)
{
    return a*(1.0f-factor)+b*factor;
}

vec4 normalize(vec4 &vec)
{
    float div = sqrt(vec.x*vec.x+vec.y*vec.y*+vec.z*vec.z+vec.w*vec.w);
    vec = vec/div;
    return vec;
}
