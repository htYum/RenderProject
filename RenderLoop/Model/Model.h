#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>
#include <fstream>
#include <QDebug>
#include <sstream>

#include "Math/MyMath.h"
#include "Mesh.h"

class Model
{
public:
    std::vector<Mesh> meshes;

    Model(const std::string& path);

    void loadModel(const std::string& path);


};

#endif // MODEL_H
