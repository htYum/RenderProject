#ifndef LIGHT_H
#define LIGHT_H

#include "Math/MyMath.h"

const vec3 AMBIENT = vec3(0.2f, 0.2f, 0.2f);

class Light
{
public:
    vec3 color;
    vec3 diffuse;
    vec3 specular;

    Light():
        color(vec3(1.0f, 1.0f, 1.0f)),
        diffuse(vec3(1.0f, 1.0f, 1.0f)),
        specular(vec3(0.5f, 0.5f, 0.5f)){}
    virtual ~Light(){}
};

#endif // LIGHT_H
