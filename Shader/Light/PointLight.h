#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "Shader/Light/Light.h"
#include "Math/MyMath.h"

class PointLight : public Light
{
public:
    vec3 pos;

    PointLight():
        pos(vec3(0,0,0)){}
};

#endif // POINTLIGHT_H
