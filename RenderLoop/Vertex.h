#ifndef VERTEX_H
#define VERTEX_H

#include "Math/mymath.h"

class Vertex
{
public:
    vec4 position;
    vec4 color;
    vec2 texCoord;
    vec3 normal;

    Vertex() = default;
    ~Vertex() = default;
    Vertex(const vec4& _pos, const vec4& _col, const vec2& _tex, const vec3& _nor):
        position(_pos),
        color(_col),
        texCoord(_tex),
        normal(_nor){}
    Vertex(const Vertex& _ver):
        position(_ver.position),
        color(_ver.color),
        texCoord(_ver.texCoord),
        normal(_ver.normal){}

    Vertex& operator=(const Vertex& rhs){
        if(&rhs == this)
            return *this;
        else{
            position = rhs.position;
            color = rhs.color;
            texCoord = rhs.texCoord;
            normal = rhs.normal;
            return *this;
        }
    }

};

#endif // VERTEX_H
