#ifndef MESH_H
#define MESH_H

#include <vector>

#include "vertex.h"
#include "RenderLoop/Model/Material.h"

class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    Material* material;

    Mesh() = default;
    ~Mesh() = default;
    Mesh(const Mesh& _m):
        vertices(_m.vertices),
        indices(_m.indices){}

    Mesh& operator=(const Mesh& rhs){
        if(&rhs == this)
            return *this;
        else{
            vertices = rhs.vertices;
            indices = rhs.indices;
            return *this;
        }
    }
    void testTriangle(const vec3& v1, const vec3& v2, const vec3& v3,
                      const vec4& col1, const vec4& col2, const vec4& col3);
    void testSquare(const vec3& v1,const vec3& v2,const vec3& v3,const vec3& v4,
                    const vec4& col1,const vec4& col2,const vec4& col3,const vec4& col4);
    void testBox(float x,float y,float z);

    void setMaterial(Material* _mat);
};

#endif // MESH_H
