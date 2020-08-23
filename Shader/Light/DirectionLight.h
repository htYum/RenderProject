#ifndef DIRECTIONLIGHT_H
#define DIRECTIONLIGHT_H

#include "Shader/Light/Light.h"
#include "Math/MyMath.h"
#include "cmath"

class DirectionLight : public Light
{
public:
    vec3 ambient;
    vec3 dir;

    DirectionLight():
        dir(vec3(0, 0, -1.0f)){}
    DirectionLight(const vec3& _dir):
        dir(_dir){
        dir = normalize(dir);
    }
    DirectionLight(const vec3& _dir, const vec3& _col):
        dir(_dir){color = _col;}

    vec3 calDirLight(const vec3& normal, const vec3& viewDir);
};

#endif // DIRECTIONLIGHT_H
