#include "Model.h"

Model::Model(const std::string &path)
{
    loadModel(path);
}

void Model::loadModel(const std::string &path)
{
    std::ifstream in;
    in.open(path.c_str(), std::ifstream::in);
    if(in.fail()){
        qDebug()<<"Model Load Error";
    }
    std::vector<vec3> vertices;
    std::vector<vec3> normals;
    std::vector<vec2> texCoords;
    std::string line;

    bool newMesh = true;
    int meshNum = 0;
    int index = 0;

    while(!in.eof()){
        std::getline(in, line);

        // vertex
        if(!line.compare(0, 2, "v ")){
            if(newMesh){
                newMesh = false;
                meshNum++;
                Mesh m;
                meshes.push_back(m);
            }
            line = line.substr(2);
            std::istringstream iss(line);
            vec3 vertex;
            iss >> vertex.x;
            iss >> vertex.y;
            iss >> vertex.z;
            vertices.push_back(vertex);
        }
        // normal
        else if(!line.compare(0, 3, "vn ")){
            line = line.substr(3);
            std::istringstream iss(line);
            vec3 normal;
            iss >> normal.x;
            iss >> normal.y;
            iss >> normal.z;
            normals.push_back(normal);
        }
        // texture
        else if(!line.compare(0, 3, "vt ")){
            line = line.substr(3);
            std::istringstream iss(line);
            vec2 tex;
            iss >> tex.x;
            iss >> tex.y;
            if(tex.y < 0){
                tex.y = 1 - tex.y;
            }
            texCoords.push_back(tex);
        }
        // index
        else if(!line.compare(0, 2, "f ")){
            if(!newMesh){
                newMesh = true;
            }
            line = line.substr(2);
            std::istringstream iss(line);
            int v, vt, vn;
            char temp;
            for(int i = 0; i < 3; ++i){
                iss >> v;
                iss>> temp;
                iss >> vt;
                iss >> temp;
                iss >> vn;
                Vertex vertex;
                vertex.position = vertices[v - 1];
                vertex.texCoord = texCoords[vt - 1];
                vertex.normal = normals[vn - 1];
                vertex.color = vec4(1,1,1,1);
                index = meshes[meshNum - 1].vertices.size();
                meshes[meshNum - 1].vertices.push_back(vertex);
                meshes[meshNum - 1].indices.push_back(index);
            }
        }
    }
    in.close();
}
