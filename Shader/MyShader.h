#ifndef MYSHADER_H
#define MYSHADER_H

#include "baseshader.h"
#include "RenderLoop/Texture2D.h"

class MyShader : public BaseShader
{
private:
    mat4x4 model;
    mat4x4 view;
    mat4x4 projection;

    Texture2D* texture;

public:
    MyShader() = default;
    virtual ~MyShader();

    virtual V2F vertexShader(const Vertex& _ver);
    virtual vec4 fragmentShader(const V2F& _v2f);
    virtual void setMat4Moedl(const mat4x4& _world);
    virtual void setMat4View(const mat4x4& _view);
    virtual void setMat4Projection(const mat4x4& _projection);
    void setTexture(Texture2D* _tex);
};

#endif // MYSHADER_H
