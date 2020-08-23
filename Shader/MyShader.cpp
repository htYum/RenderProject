#include "myshader.h"

#include <QDebug>
MyShader::~MyShader()
{
}

V2F MyShader::vertexShader(const Vertex &_ver)
{
    V2F result;
    result.worldTransPos = model * _ver.position;
    result.proPos =  projection * view * result.worldTransPos;
    result.oneDivZ = 1.0/result.proPos.w;
    result.color = _ver.color*result.oneDivZ;
    result.texCoord = _ver.texCoord*result.oneDivZ;
    mat3x3 transMat(model);
    result.normal = transMat * _ver.normal*result.oneDivZ;
    result.worldTransPos *= result.oneDivZ;
    return result;
}

vec4 MyShader::fragmentShader(const V2F &_v2f, Texture2D* texture)
{
    vec4 color = texture->sampler2D(_v2f.texCoord);
    vec3 normal = normalize(_v2f.normal);
    vec3 fragPos(_v2f.worldTransPos.x, _v2f.worldTransPos.y, _v2f.worldTransPos.z);
    vec3 viewDir = normalize(camera->getPostion() - fragPos);
    vec3 result = dirLight->calDirLight(normal, viewDir);
    color.x *= result.x;
    color.y *= result.y;
    color.z *= result.z;
    color.w = 1;
    if(color.x > 1) color.x = 1;
    if(color.y > 1) color.y = 1;
    if(color.z > 1) color.z = 1;
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

