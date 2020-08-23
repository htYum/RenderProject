#include "Matrix4x4.h"

mat4x4::mat4x4():
    value{vec4(1.0f,0,0,0),vec4(0,1.0f,0,0),vec4(0,0,1.0f,0),vec4(0,0,0,1.0f)}
{
}

mat4x4 mat4x4::getTranspose() const
{
    return mat4x4(vec4(value[0].x, value[1].x, value[2].x, value[3].x),
            vec4(value[0].y, value[1].y, value[2].y, value[3].y),
            vec4(value[0].z, value[1].z, value[2].z, value[3].z),
            vec4(value[0].w, value[1].w, value[2].w, value[3].w));
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
        result.value[i].x = value[0].x*rhs.value[i].x+
                            value[1].x*rhs.value[i].y+
                            value[2].x*rhs.value[i].z+
                            value[3].x*rhs.value[i].w;
        result.value[i].y = value[0].y*rhs.value[i].x+
                            value[1].y*rhs.value[i].y+
                            value[2].y*rhs.value[i].z+
                            value[3].y*rhs.value[i].w;
        result.value[i].z = value[0].z*rhs.value[i].x+
                            value[1].z*rhs.value[i].y+
                            value[2].z*rhs.value[i].z+
                            value[3].z*rhs.value[i].w;
        result.value[i].w = value[0].w*rhs.value[i].x+
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


mat4x4 translate(mat4x4& matrix, const vec3 &_trans)
{
    matrix.value[3].x = _trans.x;
    matrix.value[3].y = _trans.y;
    matrix.value[3].z = _trans.z;
    return matrix;
}

mat4x4 scale(mat4x4& matrix, const vec3 &_scale)
{
    mat4x4 result;
    result.value[0].x = _scale.x;
    result.value[1].y = _scale.y;
    result.value[2].z = _scale.z;
    matrix = matrix * result;
    return matrix;
}

mat4x4 rotate(mat4x4& matrix, float angle, const vec3 &axis)
{
    float radians = PI*angle/180;
    float cosx = cos(radians);
    float sinx = sin(radians);
    vec3 v = normalize(axis);
    float x = v.x;
    float y = v.y;
    float z = v.z;

    mat4x4 result;
    result.value[0].x = x*x + (1-x*x)*cosx;
    result.value[1].x = x*y*(1-cosx) - z*sinx;
    result.value[2].x = x*z*(1-cosx) + y*sinx;
    result.value[0].y = x*y*(1-cosx) + z*sinx;
    result.value[1].y = y*y + (1-y*y)*cosx;
    result.value[2].y = y*z*(1-cosx) - x*sinx;
    result.value[0].z = x*z*(1-cosx) - y*sinx;
    result.value[1].z = y*z*(1-cosx) + x*sinx;
    result.value[2].z = z*z + (1-z*z)*cosx;
    matrix = matrix * result;

    return matrix;
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
