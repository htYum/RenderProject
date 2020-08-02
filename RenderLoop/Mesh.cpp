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

void Mesh::testBox(float x, float y, float z)
{
    vertices.resize(24);
    indices.resize(36);

    float halfW = x * 0.5f;
    float halfH = y * 0.5f;
    float halfD = z * 0.5f;
    //front
    vertices[0].position = vec3(halfW, halfH, halfD);
    vertices[0].normal = vec3(0.f, 0.f, 1.f);
    vertices[0].color = vec4(1.f, 0.f, 0.f, 1.f);
    vertices[0].texCoord = vec2(1, 1);
    vertices[1].position = vec3(-halfW, halfH, halfD);
    vertices[1].normal = vec3(0.f, 0.f, 1.f);
    vertices[1].color = vec4(0.f, 1.f, 0.f, 1.f);
    vertices[1].texCoord = vec2(0, 1);
    vertices[2].position = vec3(-halfW,-halfH, halfD);
    vertices[2].normal = vec3(0.f, 0.f, 1.f);
    vertices[2].color = vec4(0.f, 0.f, 1.f, 1.f);
    vertices[2].texCoord = vec2(0, 0);
    vertices[3].position = vec3(halfW, -halfH, halfD);
    vertices[3].normal = vec3(0.f, 0.f, 1.f);
    vertices[3].color = vec4(0.f, 1.f, 1.f, 1.f);
    vertices[3].texCoord = vec2(1.f, 0.f);
    //left
    vertices[4].position = vec3(-halfW, +halfH, halfD);
    vertices[4].normal = vec3(-1.f, 0.f, 0.f);
    vertices[4].color = vec4(0.f, 0.f, 1.f, 1.f);
    vertices[4].texCoord = vec2(1.f, 1.f);
    vertices[5].position = vec3(-halfW, +halfH, -halfD);
    vertices[5].normal = vec3(-1.f, 0.f, 0.f);
    vertices[5].color = vec4(1.f, 1.f, 0.f, 1.f);
    vertices[5].texCoord = vec2(0.f, 1.f);
    vertices[6].position = vec3(-halfW, -halfH, -halfD);
    vertices[6].normal = vec3(-1.f, 0.f, 0.f);
    vertices[6].color = vec4(0.f, 1.f, 0.f, 1.f);
    vertices[6].texCoord = vec2(0.f, 0.f);
    vertices[7].position = vec3(-halfW, -halfH, halfD);
    vertices[7].normal = vec3(-1.f, 0.f, 0.f);
    vertices[7].color = vec4(1.f, 1.f, 1.f, 1.f);
    vertices[7].texCoord = vec2(1.f, 0.f);
    //back
    vertices[8].position = vec3(-halfW, +halfH, -halfD);
    vertices[8].normal = vec3(0.f, 0.f, -1.f);
    vertices[8].color = vec4(1.f, 0.f, 1.f, 1.f);
    vertices[8].texCoord = vec2(0.f, 0.f);
    vertices[9].position = vec3(+halfW, +halfH, -halfD);
    vertices[9].normal = vec3(0.f, 0.f, -1.f);
    vertices[9].color = vec4(0.f, 1.f, 1.f, 1.f);
    vertices[9].texCoord = vec2(1.f, 0.f);
    vertices[10].position = vec3(+halfW, -halfH, -halfD);
    vertices[10].normal = vec3(0.f, 0.f, -1.f);
    vertices[10].color = vec4(1.f, 1.f, 0.f, 1.f);
    vertices[10].texCoord = vec2(1.f, 1.f);
    vertices[11].position = vec3(-halfW, -halfH, -halfD);
    vertices[11].normal = vec3(0.f, 0.f, -1.f);
    vertices[11].color = vec4(0.f, 0.f, 1.f, 1.f);
    vertices[11].texCoord = vec2(0.f, 1.f);
    //right
    vertices[12].position = vec3(halfW, +halfH, -halfD);
    vertices[12].normal = vec3(1.f, 0.f, 0.f);
    vertices[12].color = vec4(0.f, 1.f, 0.f, 1.f);
    vertices[12].texCoord = vec2(0.f, 0.f);
    vertices[13].position = vec3(halfW, +halfH, +halfD);
    vertices[13].normal = vec3(1.f, 0.f, 0.f);
    vertices[13].color = vec4(1.f, 0.f, 0.f, 1.f);
    vertices[13].texCoord = vec2(1.f, 0.f);
    vertices[14].position = vec3(halfW, -halfH, +halfD);
    vertices[14].normal = vec3(1.f, 0.f, 0.f);
    vertices[14].color = vec4(0.f, 1.f, 1.f, 1.f);
    vertices[14].texCoord = vec2(1.f, 1.f);
    vertices[15].position = vec3(halfW, -halfH, -halfD);
    vertices[15].normal = vec3(1.f, 0.f, 0.f);
    vertices[15].color = vec4(1.f, 0.f, 1.f, 1.f);
    vertices[15].texCoord = vec2(0.f, 1.f);
    //top
    vertices[16].position = vec3(+halfW, halfH, -halfD);
    vertices[16].normal = vec3(0.f, 1.f, 0.f);
    vertices[16].color = vec4(0.f, 0.f, 0.f, 1.f);
    vertices[16].texCoord = vec2(0.f, 0.f);
    vertices[17].position = vec3(-halfW, halfH, -halfD);
    vertices[17].normal = vec3(0.f, 1.f, 0.f);
    vertices[17].color = vec4(1.f, 1.f, 0.f, 1.f);
    vertices[17].texCoord = vec2(1.f, 0.f);
    vertices[18].position = vec3(-halfW, halfH, halfD);
    vertices[18].normal = vec3(0.f, 1.f, 0.f);
    vertices[18].color = vec4(0.f, 1.f, 1.f, 1.f);
    vertices[18].texCoord = vec2(1.f, 1.f);
    vertices[19].position = vec3(+halfW, halfH, halfD);
    vertices[19].normal = vec3(0.f, 1.f, 0.f);
    vertices[19].color = vec4(1.f, 0.f, 0.f, 1.f);
    vertices[19].texCoord = vec2(0.f, 1.f);
    //down
    vertices[20].position = vec3(+halfW, -halfH, -halfD);
    vertices[20].normal = vec3(0.f, -1.f, 0.f);
    vertices[20].color = vec4(0.f, 0.f, 1.f, 1.f);
    vertices[20].texCoord = vec2(0.f, 0.f);
    vertices[21].position = vec3(+halfW, -halfH, +halfD);
    vertices[21].normal = vec3(0.f, -1.f, 0.f);
    vertices[21].color = vec4(1.f, 1.f, 1.f, 1.f);
    vertices[21].texCoord = vec2(1.f, 0.f);
    vertices[22].position = vec3(-halfW, -halfH, +halfD);
    vertices[22].normal = vec3(0.f, -1.f, 0.f);
    vertices[22].color = vec4(0.f, 1.f, 0.f, 1.f);
    vertices[22].texCoord = vec2(1.f, 1.f);
    vertices[23].position = vec3(-halfW, -halfH, -halfD);
    vertices[23].normal = vec3(0.f, -1.f, 0.f);
    vertices[23].color = vec4(1.f, 0.f, 1.f, 1.f);
    vertices[23].texCoord = vec2(0.f, 1.f);

    //front
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 0;
    indices[4] = 2;
    indices[5] = 3;
    //left
    indices[6] = 4;
    indices[7] = 5;
    indices[8] = 6;
    indices[9] = 4;
    indices[10] = 6;
    indices[11] = 7;
    //back
    indices[12] = 8;
    indices[13] = 9;
    indices[14] = 10;
    indices[15] = 8;
    indices[16] = 10;
    indices[17] = 11;
    //right
    indices[18] = 12;
    indices[19] = 13;
    indices[20] = 14;
    indices[21] = 12;
    indices[22] = 14;
    indices[23] = 15;
    //top
    indices[24] = 16;
    indices[25] = 17;
    indices[26] = 18;
    indices[27] = 16;
    indices[28] = 18;
    indices[29] = 19;
    //down
    indices[30] = 20;
    indices[31] = 21;
    indices[32] = 22;
    indices[33] = 20;
    indices[34] = 22;
    indices[35] = 23;
}
