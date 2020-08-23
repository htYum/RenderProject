#pragma once

#include <cmath>

#include "vec3.h"
#include "vec4.h"

const float PI = 3.14159265;

class mat4x4
{
public:
    vec4 value[4] = {
        vec4(1.0f,0,0,0),
        vec4(0,1.0f,0,0),
        vec4(0,0,1.0f,0),
        vec4(0,0,0,1.0f)};  // colume

    mat4x4();
    ~mat4x4() = default;
    mat4x4(const vec4& vec):
        value{vec,vec,vec,vec}{}
    mat4x4(const vec4& v1,
           const vec4& v2,
           const vec4& v3,
           const vec4& v4):
        value{v1,v2,v3,v4}{}
    mat4x4(const float& f1,const float& f2,const float& f3,const float& f4,
           const float& f5,const float& f6,const float& f7,const float& f8,
           const float& f9,const float& f10,const float& f11,const float& f12,
           const float& f13,const float& f14,const float& f15,const float& f16):
        value{vec4(f1,f2,f3,f4),vec4(f5,f6,f7,f8),vec4(f9,f10,f11,f12),vec4(f13,f14,f15,f16)}{}

    mat4x4 getTranspose() const;

    mat4x4 operator+(const mat4x4& rhs) const;
    mat4x4 operator-(const mat4x4& rhs) const;
    mat4x4 operator*(const float& rhs) const;
    mat4x4 operator/(const float& rhs) const;
    mat4x4 operator*(const mat4x4& rhs) const;
    vec4 operator*(const vec4& rhs) const;

    bool operator==(const mat4x4& rhs) const;
    bool operator!=(const mat4x4& rhs) const;

    mat4x4 operator-() const;
};

mat4x4 getViewPortMatrix(int x, int y, int width, int height);


mat4x4 translate(mat4x4& matrix, const vec3& _trans);
mat4x4 scale(mat4x4& matrix, const vec3& _scale);
mat4x4 rotate(mat4x4& matrix, float angle, const vec3& axis);

mat4x4 perspective(float fovy, float aspect, float near, float far);    // input angle

mat4x4 lookAt(const vec3& eye, const vec3& center, const vec3& up);
// eye      相机在世界中的位置
// center   相机对准的物体在世界中的位置
// up       相机的up在世界中的方向

mat4x4 rotateX(mat4x4& matrix, float angle);
