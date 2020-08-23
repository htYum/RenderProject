#include "Matrix3x3.h"

mat3x3::mat3x3():
    value{vec3(1.0f, 0, 0), vec3(0, 1.0f, 0), vec3(0, 0, 1.0f)}
{

}

mat3x3::mat3x3(const mat4x4 &rhs):
    value{vec3(rhs.value[0].x, rhs.value[0].y, rhs.value[0].z),
    vec3(rhs.value[1].x, rhs.value[1].y, rhs.value[1].z),
    vec3(rhs.value[2].x, rhs.value[2].y, rhs.value[2].z)}
{

}

mat3x3 mat3x3::getTranspose() const
{
    return mat3x3(vec3(value[0].x, value[1].x, value[2].x),
            vec3(value[0].y, value[1].y, value[2].y),
            vec3(value[0].z, value[1].z, value[2].z));
}

mat3x3 mat3x3::operator+(const mat3x3 &rhs) const
{
    mat3x3 temp;
    for(int i = 0; i < 3; ++i){
        temp.value[i] = (*this).value[i]+rhs.value[i];
    }
    return temp;
}

mat3x3 mat3x3::operator-(const mat3x3 &rhs) const
{
    mat3x3 temp;
    for(int i = 0; i < 3; ++i){
        temp.value[i] = (*this).value[i]-rhs.value[i];
    }
    return temp;
}

mat3x3 mat3x3::operator*(const mat3x3 &rhs) const
{
    mat3x3 result;
    for(int i = 0; i < 3; ++i){
        result.value[i].x = value[0].x*rhs.value[i].x+
                            value[1].x*rhs.value[i].y+
                            value[2].x*rhs.value[i].z;
        result.value[i].y = value[0].y*rhs.value[i].x+
                            value[1].y*rhs.value[i].y+
                            value[2].y*rhs.value[i].z;
        result.value[i].z = value[0].z*rhs.value[i].x+
                            value[1].z*rhs.value[i].y+
                            value[2].z*rhs.value[i].z;
    }
    return result;
}

mat3x3 mat3x3::operator/(float rhs) const
{
    if(rhs == 0)return *this;
    else {
        mat3x3 temp;
        for(int i = 0; i < 3; ++i){
            temp.value[i]/=rhs;
        }
        return temp;
    }
}

mat3x3 mat3x3::operator*(float rhs) const
{
    mat3x3 temp;
    for(int i = 0; i < 3; ++i){
        temp.value[i]*=rhs;
    }
    return temp;
}

vec3 mat3x3::operator*(const vec3 &rhs) const
{
    float x = 0;
    x = value[0].x*rhs.x+value[1].x*rhs.y+value[2].x*rhs.z;
    float y = 0;
    y = value[0].y*rhs.x+value[1].y*rhs.y+value[2].y*rhs.z;
    float z = 0;
    z = value[0].z*rhs.x+value[1].z*rhs.y+value[2].z*rhs.z;
    return vec3(x,y,z);
}

bool mat3x3::operator==(const mat3x3 &rhs) const
{
    for(int i = 0; i < 3; ++i){
        if(value[i] != rhs.value[i])
            return false;
    }
    return true;
}

bool mat3x3::operator!=(const mat3x3 &rhs) const
{
    return !((*this)==rhs);
}

mat3x3 mat3x3::operator-() const
{
    return mat3x3(vec3(-value[0]), vec3(-value[1]), vec3(-value[2]));
}
