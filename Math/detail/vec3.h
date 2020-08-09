#pragma once

#include <cmath>

class vec3
{
public:
    float x,y,z;

    vec3() = default;
    ~vec3() = default;
    vec3(float newX, float newY, float newZ);
    vec3(const vec3& vec);
    vec3(float val);

    void setX(float newX);
    void setY(float newY);
    void setZ(float newZ);
    void set(float newX, float newY, float newZ);
    float getX();
    float getY();
    float getZ();

    float length();

    vec3 operator+(const vec3& rhs)const;
    vec3 operator-(const vec3& rhs)const;
    vec3 operator*(const float rhs)const;
    vec3 operator/(const float rhs)const;
    vec3 operator=(const vec3& rhs);

    bool operator==(const vec3& rhs)const;
    bool operator!=(const vec3& rhs)const;

    void operator+=(const vec3& rhs);
    void operator-=(const vec3& rhs);
    void operator*=(const float rhs);
    void operator/=(const float rhs);

    vec3 operator-()const;
};

float dot(const vec3& lhs, const vec3& rhs);

vec3 cross(const vec3& lhs, const vec3& rhs);

vec3 normalize(const vec3& vec);
vec3 normalize(vec3& vec);

vec3 lerp(const vec3& a,const vec3& b,float factor);
