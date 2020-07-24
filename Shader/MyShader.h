#ifndef MYSHADER_H
#define MYSHADER_H

#include "baseshader.h"

class MyShader : public BaseShader
{
public:
    MyShader() = default;
    ~MyShader() = default;

    virtual V2F vertexShader(const Vertex& _ver);
    virtual vec4 fragmentShader(const V2F& _v2f);
    virtual void setMat4Moedl(const mat4x4& _world);
    virtual void setMat4View(const mat4x4& _view);
    virtual void setMat4Projection(const mat4x4& _projection);
};

#endif // MYSHADER_H
