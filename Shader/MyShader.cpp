#include "myshader.h"

V2F MyShader::vertexShader(const Vertex &_ver)
{
    V2F result;
    result.worldTransPos = model * _ver.position;
    result.proPos =  projection * view * result.worldTransPos;
    result.oneDivZ = 1.0/result.proPos.w;
    result.color = _ver.color*result.oneDivZ;
    result.texCoord = _ver.texCoord*result.oneDivZ;
    result.normal = _ver.normal*result.oneDivZ;
    result.worldTransPos *= result.oneDivZ;
    return result;
}

vec4 MyShader::fragmentShader(const V2F &_v2f)
{
    vec4 color = texture->sampler2D(_v2f.texCoord);
    return color;
}

void MyShader::setMat4Moedl(const mat4x4 &_world)
{
    model = _world;
}

void MyShader::setMat4View(const mat4x4 &_view)
{
    view = _view;
}

void MyShader::setMat4Projection(const mat4x4 &_projection)
{
    projection = _projection;
}

void MyShader::setTexture(Texture2D *_tex)
{
    texture = _tex;
}
