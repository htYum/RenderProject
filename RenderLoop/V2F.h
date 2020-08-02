#ifndef V2F_H
#define V2F_H

#include "Math/mymath.h"

class V2F
{
public:
    vec4 worldTransPos;
    vec4 proPos;    // projection space position
    vec4 color;
    vec2 texCoord;
    vec3 normal;
    double oneDivZ;// use of depth test

    V2F() = default;
    ~V2F() = default;
    V2F(const vec4& _wPos,const vec4& _pPos, const vec4& _col, const vec2& _tex, const vec3& _nor, double _oneDivZ):
        worldTransPos(_wPos),
        proPos(_pPos),
        color(_col),
        texCoord(_tex),
        normal(_nor),
        oneDivZ(_oneDivZ){}
    V2F(const V2F& _v2f):
        worldTransPos(_v2f.worldTransPos),
        proPos(_v2f.proPos),
        color(_v2f.color),
        texCoord(_v2f.texCoord),
        normal(_v2f.normal),
        oneDivZ(_v2f.oneDivZ){}
};

#endif // V2F_H
