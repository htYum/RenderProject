#include "mesh.h"


void Mesh::testTriangle(const vec3 &v1, const vec3 &v2, const vec3 &v3, const vec4 &col1, const vec4 &col2, const vec4 &col3)
{
    vertices.resize(3);
    indices.resize(3);
    vertices[0].position = v1;
    vertices[0].normal = vec3(0,0,1.0f);
    vertices[0].color = col1;
    vertices[0].texCoord = vec2(0,0);
    vertices[1].position = v2;
    vertices[1].normal = vec3(0,0,1.0f);
    vertices[1].color = col2;
    vertices[1].texCoord = vec2(0,0);
    vertices[2].position = v3;
    vertices[2].normal = vec3(0,0,1.0f);
    vertices[2].color = col3;
    vertices[2].texCoord = vec2(0,0);
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
}

void Mesh::testSquare(const vec3 &v1, const vec3 &v2, const vec3 &v3, const vec3 &v4, const vec4 &col1, const vec4 &col2, const vec4 &col3, const vec4 &col4)
{
    vertices.resize(4);
    indices.resize(6);
    vertices[0].position = v1;
    vertices[0].normal = vec3(0,0,1.0f);
    vertices[0].color = col1;
    vertices[0].texCoord = vec2(0,0);
    vertices[1].position = v2;
    vertices[1].normal = vec3(0,0,1.0f);
    vertices[1].color = col2;
    vertices[1].texCoord = vec2(0,0);
    vertices[2].position = v3;
    vertices[2].normal = vec3(0,0,1.0f);
    vertices[2].color = col3;
    vertices[2].texCoord = vec2(0,0);
    vertices[3].position = v4;
    vertices[3].normal = vec3(0,0,1.0f);
    vertices[3].color = col4;
    vertices[3].texCoord = vec2(0,0);
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 0;
    indices[4] = 2;
    indices[5] = 3;
}
