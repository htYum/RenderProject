#pragma once

#include <cmath>
#include "vec3.h"

class vec4
{
public:
    float x,y,z,w;

    vec4() = default;
    ~vec4() = default;
    vec4(float newX, float newY, float newZ, float newW);
    vec4(const vec4& vec);
    vec4(float val);
    vec4(const vec3& vec, float val);
    vec4(const vec3& vec);
    vec4(float val, const vec3& vec);

    void setX(float newX);
    void setY(float newY);
    void setZ(float newZ);
    void setW(float newW);
    void set(float newX, float newY, float newZ, float newW);
    void set(float val, const vec3& vec);
    void set(const vec3& vec, float val);
    float getX();
    float getY();
    float getZ();
    float getW();

    float length();

    vec4 operator+(const vec4& rhs)const;
    vec4 operator-(const vec4& rhs)const;
    vec4 operator*(const float rhs)const;
    vec4 operator/(const float rhs)const;
    vec4 operator=(const vec4& rhs);

    bool operator==(const vec4& rhs)const;
    bool operator!=(const vec4& rhs)const;

    void operator+=(const vec4& rhs);
    void operator-=(const vec4& rhs);
    void operator*=(const float rhs);
    void operator/=(const float rhs);

    vec4 operator-()const;
};

float dot(const vec4& lhs, const vec4& rhs);

vec4 lerp(const vec4& a,const vec4& b,float factor);

vec4 normalize(vec4& vec);
