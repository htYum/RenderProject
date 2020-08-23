#ifndef MATRIX3X3_H
#define MATRIX3X3_H

#include "vec3.h"
#include "Matrix4x4.h"

class mat3x3
{
public:
    vec3 value[3] = {
        vec3(1.0f, 0, 0),
        vec3(0, 1.0f, 0),
        vec3(0, 0, 1.0f)};

    mat3x3();
    ~mat3x3() = default;
    mat3x3(const vec3& v1,
           const vec3& v2,
           const vec3& v3):
        value{v1, v2, v3}{}
    mat3x3(float f1, float f2, float f3,
           float f4, float f5, float f6,
           float f7, float f8, float f9):   // column
        value{vec3(f1, f2, f3), vec3(f4, f5, f6), vec3(f7, f8, f9)}{}
    mat3x3(const mat4x4& rhs);

    mat3x3 getTranspose() const;

    mat3x3 operator+(const mat3x3& rhs) const;
    mat3x3 operator-(const mat3x3& rhs) const;
    mat3x3 operator*(const mat3x3& rhs) const;
    mat3x3 operator/(float rhs) const;
    mat3x3 operator*(float rhs) const;
    vec3 operator*(const vec3& rhs) const;

    bool operator==(const mat3x3& rhs) const;
    bool operator!=(const mat3x3& rhs) const;

    mat3x3 operator-() const;
};

#endif // MATRIX3X3_H
