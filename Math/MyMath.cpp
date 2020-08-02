#include "mymath.h"

inline float dot(const vec2& lhs, const vec2& rhs){
    return lhs.x*rhs.x + lhs.y*rhs.y;
}

inline float dot(const vec3& lhs, const vec3& rhs){
    return lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z;
}

inline float dot(const vec4& lhs, const vec4& rhs){
    return lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z + lhs.w*rhs.w;
}

inline vec3 cross(const vec3& lhs, const vec3& rhs){
    float x = lhs.y*rhs.z - lhs.z*rhs.y;
    float y = lhs.z*rhs.x - lhs.x*rhs.z;
    float z = lhs.x*rhs.y - lhs.y*rhs.x;
    return vec3(x,y,z);
}

template<class T>
inline T normalize(T vec){
    return vec/sqrt(dot(vec, vec));
}

template<class T>
inline float length(T vec){
    return sqrt(dot(vec,vec));
}

mat4x4::mat4x4():
    value{vec4(1.0f,0,0,0),vec4(0,1.0f,0,0),vec4(0,0,1.0f,0),vec4(0,0,0,1.0f)}
{
}

mat4x4 mat4x4::operator+(const mat4x4 &rhs) const
{
    mat4x4 temp;
    for(int i = 0; i < 4; ++i){
        temp.value[i] = (*this).value[i]+rhs.value[i];
    }
    return temp;
}

mat4x4 mat4x4::operator-(const mat4x4 &rhs) const
{
    mat4x4 temp;
    for(int i = 0; i < 4; ++i){
        temp.value[i] = (*this).value[i]-rhs.value[i];
    }
    return temp;
}

mat4x4 mat4x4::operator*(const float &rhs) const
{
    mat4x4 temp;
    for(int i = 0; i < 4; ++i){
        temp.value[i]*=rhs;
    }
    return temp;
}

vec4 mat4x4::operator*(const vec4 &rhs) const
{
    float x = 0;
    x = value[0].x*rhs.x+value[1].x*rhs.y+value[2].x*rhs.z+value[3].x*rhs.w;
    float y = 0;
    y = value[0].y*rhs.x+value[1].y*rhs.y+value[2].y*rhs.z+value[3].y*rhs.w;
    float z = 0;
    z = value[0].z*rhs.x+value[1].z*rhs.y+value[2].z*rhs.z+value[3].z*rhs.w;
    float w = 0;
    w = value[0].w*rhs.x+value[1].w*rhs.y+value[2].w*rhs.z+value[3].w*rhs.w;
    return vec4(x,y,z,w);
}

mat4x4 mat4x4::operator/(const float &rhs) const
{
    if(rhs == 0)return *this;
    else {
        mat4x4 temp;
        for(int i = 0; i < 4; ++i){
            temp.value[i]/=rhs;
        }
        return temp;
    }
}

mat4x4 mat4x4::operator*(const mat4x4 &rhs) const
{
    mat4x4 result;
    for(int i = 0; i < 4; ++i){
        result.value[i].x = value[0].x*rhs.value[i].x +
                            value[1].x*rhs.value[i].y+
                            value[2].x*rhs.value[i].z+
                            value[3].x*rhs.value[i].w;
        result.value[i].y = value[0].y*rhs.value[i].x +
                            value[1].y*rhs.value[i].y+
                            value[2].y*rhs.value[i].z+
                            value[3].y*rhs.value[i].w;
        result.value[i].z = value[0].z*rhs.value[i].x +
                            value[1].z*rhs.value[i].y+
                            value[2].z*rhs.value[i].z+
                            value[3].z*rhs.value[i].w;
        result.value[i].w = value[0].w*rhs.value[i].x +
                            value[1].w*rhs.value[i].y+
                            value[2].w*rhs.value[i].z+
                            value[3].w*rhs.value[i].w;
    }
    return result;
}


mat4x4 getViewPortMatrix(int x, int y, int width, int height)
{
    mat4x4 result(vec4(width/2.0f,0,0,0),vec4(0,-height/2.0f,0,0),vec4(0,0,1.0f,0),vec4(x+width/2.0f,y+height/2.0f,0,1.0f));
    return result;
}

vec2 lerp(const vec2 &a, const vec2 &b, float factor)
{
    return a*(1.0f-factor)+b*factor;
}
vec3 lerp(const vec3& a, const vec3& b, float factor)
{
    return a*(1.0f-factor)+b*factor;
}
vec4 lerp(const vec4& a, const vec4& b, float factor)
{
    return a*(1.0f-factor)+b*factor;
}

mat4x4 translate(mat4x4& matrix, const vec3 &_trans)
{
    matrix.value[3].x = _trans.x;
    matrix.value[3].y = _trans.y;
    matrix.value[3].z = _trans.z;
    return matrix;
}

mat4x4 scale(mat4x4& matrix, const vec3 &_scale)
{
    matrix.value[0].x = _scale.x;
    matrix.value[1].y = _scale.y;
    matrix.value[2].z = _scale.z;
    return matrix;
}

mat4x4 rotate(mat4x4& matrix, float angle, const vec3 &axis)
{
    float radians = PI*angle/180;
    float cosx = cos(radians);
    float sinx = sin(radians);
    vec3 v = normalize(axis);
    int x = v.x;
    int y = v.y;
    int z = v.z;

    matrix.value[0].x = x*x + (1-x*x)*cosx;
    matrix.value[0].y = x*y*(1-cosx) - z*sinx;
    matrix.value[0].z = x*z*(1-cosx) + y*sinx;
    matrix.value[1].x = x*y*(1-cosx) + z*sinx;
    matrix.value[1].y = y*y + (1-y*y)*cosx;
    matrix.value[1].z = y*z*(1-cosx) - x*sinx;
    matrix.value[2].x = x*z*(1-cosx) - y*sinx;
    matrix.value[2].y = y*z*(1-cosx) + x*sinx;
    matrix.value[2].z = z*z + (1-z*z)*cosx;

    return matrix;
}

vec2 normalize(vec2 &vec)
{
    float div = sqrt(vec.x*vec.x+vec.y*vec.y);
    vec = vec/div;
    return vec;
}

vec3 normalize(vec3 &vec)
{
    float div = sqrt(vec.x*vec.x+vec.y*vec.y+vec.z*vec.z);
    vec = vec/div;
    return vec;
}

vec4 normalize(vec4 &vec)
{
    float div = sqrt(vec.x*vec.x+vec.y*vec.y*+vec.z*vec.z+vec.w*vec.w);
    vec = vec/div;
    return vec;
}

mat4x4 perspective(float fovy, float aspect, float near, float far)
{
    mat4x4 result;
    float f = fovy*PI/180;
    float tanx = tanf(f*0.5f);
    result.value[0].x = 1.0f/(aspect*tanx);
    result.value[1].y = 1.0f/tanx;
    result.value[2].z = -(far+near)/(far-near);
    result.value[2].w = -1.0f;
    result.value[3].z = (-2.0f*far*near)/(far-near);
    return result;
}

mat4x4 lookAt(const vec3 &eye, const vec3 &center, const vec3 &up)
{
    vec3 front = normalize(center-eye);
    vec3 x = normalize(cross(front,up));
    vec3 y = normalize(cross(x,front));

    mat4x4 result;
    result.value[0].x = x.x;
    result.value[1].x = x.y;
    result.value[2].x = x.z;
    result.value[0].y = y.x;
    result.value[1].y = y.y;
    result.value[2].y = y.z;
    result.value[0].z = -front.x;
    result.value[1].z = -front.y;
    result.value[2].z = -front.z;
    result.value[3].x = -dot(x,eye);
    result.value[3].y = -dot(y,eye);
    result.value[3].z = dot(front,eye);
    return result;
}

mat4x4 rotateX(mat4x4& matrix, float angle)
{
    matrix.value[1].y = cos(PI*angle/180);
    matrix.value[1].z = sin(PI*angle/180);
    matrix.value[2].y = -matrix.value[1].z;
    matrix.value[2].z = matrix.value[1].y;
    return matrix;
}
