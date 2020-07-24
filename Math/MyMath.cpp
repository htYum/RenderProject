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
