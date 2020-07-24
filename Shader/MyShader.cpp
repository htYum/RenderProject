#include "myshader.h"

V2F MyShader::vertexShader(const Vertex &_ver)
{
    V2F result;
    result.worldPos = _ver.position;
    result.proPos = _ver.position;
    result.color = _ver.color;
    result.texCoord = _ver.texCoord;
    result.normal = _ver.normal;
    result.oneDivZ = 1.0;
    return result;
}

vec4 MyShader::fragmentShader(const V2F &_v2f)
{
    vec4 color;
    color = _v2f.color;
    return color;
}

void MyShader::setMat4Moedl(const mat4x4 &_world)
{

}

void MyShader::setMat4View(const mat4x4 &_view)
{

}

void MyShader::setMat4Projection(const mat4x4 &_projection)
{

}
