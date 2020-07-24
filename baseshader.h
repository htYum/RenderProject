#ifndef BASESHADER_H
#define BASESHADER_H

#include "v2f.h"
#include "mymath.h"
#include "vertex.h"
class BaseShader
{
public:
    BaseShader() = default;
    ~BaseShader() = default;

    virtual V2F vertexShader(const Vertex& _ver) = 0;
    virtual vec4 fragmentShader(const V2F& _v2f) = 0;
    virtual void setMat4Moedl(const mat4x4& _world) = 0;
    virtual void setMat4View(const mat4x4& _view) = 0;
    virtual void setMat4Projection(const mat4x4& _projection) = 0;
};

#endif // BASESHADER_H
