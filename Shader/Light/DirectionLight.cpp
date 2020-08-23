#include "DirectionLight.h"

vec3 DirectionLight::calDirLight(const vec3 &normal, const vec3 &viewDir)
{
    dir = normalize(dir);
    float diff = fmax(dot(normal, -dir), 0.0f);
    vec3 halfDir = normalize(viewDir - dir);
    float spec = pow(fmax(dot(halfDir, normal), 0.0f), 16);

    ambient = AMBIENT;
    diffuse = color * diff * 0.9f;
    specular = color * spec * 0.5f;
    return ambient + diffuse + specular;
}
