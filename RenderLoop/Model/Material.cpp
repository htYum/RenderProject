#include "Material.h"

Material::Material():
    texture(nullptr),
    shader(nullptr)
{

}

void Material::setTexture(Texture2D* _tex)
{
    texture = _tex;
}

void Material::setShader(MyShader* _shader)
{
    shader = _shader;
}
