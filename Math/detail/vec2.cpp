#include "vec2.h"

vec2::vec2(float newX, float newY):
    x(newX),
    y(newY)
{}

vec2::vec2(const vec2& vec):
x(vec.x),
y(vec.y)
{}

vec2::vec2(float val):
x(val), 
y(val)
{}

void vec2::setX(float newX)
{
    x = newX;
}

void vec2::setY(float newY)
{
    y = newY;
}

void vec2::set(float newX, float newY)
{
    x = newX;
    y = newY;
}

float vec2::getX()
{
    return x;
}

float vec2::getY()
{
    return y;
}

float vec2::length()
{
    return sqrt(x*x + y*y);
}

vec2 vec2::operator+(const vec2& rhs)const 
{
    return vec2(x+rhs.x, y+rhs.y);
}

vec2 vec2::operator-(const vec2& rhs)const 
{
    return vec2(x-rhs.x, y-rhs.y);
}

vec2 vec2::operator*(const float rhs)const 
{
    return vec2(x*rhs, y*rhs);
}

vec2 vec2::operator/(const float rhs)const 
{
    return (rhs == 0)? vec2(0.0f, 0.0f):vec2(x/rhs, y/rhs);
}

vec2 vec2::operator=(const vec2& rhs) 
{
    x = rhs.x;
    y = rhs.y;
    return *this;
}

bool vec2::operator==(const vec2& rhs)const 
{
    return (x == rhs.x)&&(y == rhs.y);
}

bool vec2::operator!=(const vec2& rhs)const 
{
    return !(*this == rhs);
}

void vec2::operator+=(const vec2& rhs)
{
    x+=rhs.x;y+=rhs.y;
}

void vec2::operator-=(const vec2& rhs)
{
    x-=rhs.x;
    y-=rhs.y;
}

void vec2::operator*=(const float rhs)
{
    x*=rhs;
    y*=rhs;
}

void vec2::operator/=(const float rhs)
{
    if(rhs!=0){
        x/=rhs;
        y/=rhs;
    }
}

vec2 vec2::operator-()const 
{
    return vec2(-x, -y);
}

float dot(const vec2& lhs, const vec2& rhs)
{
    return lhs.x*rhs.x + lhs.y*rhs.y;
}

vec2 lerp(const vec2 &a, const vec2 &b, float factor)
{
    return a*(1.0f-factor)+b*factor;
}

vec2 normalize(vec2 &vec)
{
    float div = sqrt(vec.x*vec.x+vec.y*vec.y);
    vec = vec/div;
    return vec;
}
