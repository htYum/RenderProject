#pragma once

#include <cmath>

class vec2
{
public:
    float x, y;

    vec2() = default;
    ~vec2() = default;
    vec2(float newX, float newY);
    vec2(const vec2& vec);
    vec2(float val);

    void setX(float newX);
    void setY(float newY);
    void set(float newX, float newY);
    float getX();
    float getY();

    float length();

    vec2 operator+(const vec2& rhs)const;
    vec2 operator-(const vec2& rhs)const;
    vec2 operator*(const float rhs)const;
    vec2 operator/(const float rhs)const;
    vec2 operator=(const vec2& rhs);

    bool operator==(const vec2& rhs)const;
    bool operator!=(const vec2& rhs)const;

    void operator+=(const vec2& rhs);
    void operator-=(const vec2& rhs);
    void operator*=(const float rhs);
    void operator/=(const float rhs);

    vec2 operator-()const;
};

float dot(const vec2& lhs, const vec2& rhs);

vec2 lerp(const vec2& a,const vec2& b,float factor);

vec2 normalize(vec2& vec);
