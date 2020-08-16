#ifndef MATERIAL_H
#define MATERIAL_H

#include "RenderLoop/Model/Texture2D.h"
#include "Shader/MyShader.h"

class Material
{
public:
    Texture2D* texture;
    MyShader* shader;

    Material();
    ~Material() = default;

    void setTexture(Texture2D* _tex);
    void setShader(MyShader* _shader);
};

#endif // MATERIAL_H
