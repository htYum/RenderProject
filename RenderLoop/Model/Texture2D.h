#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <string>
#include <QDebug>
#include <QString>

#include "Math/MyMath.h"

class Texture2D
{
private:
    int width;
    int height;
    int nChannel;
    unsigned char* pixelBuffer;

public:
    Texture2D():width(0),height(0),nChannel(0),pixelBuffer(nullptr){}
    ~Texture2D();

    bool loadImage(const std::string& path);
    vec4 sampler2D(const vec2& texCoord);
};

#endif // TEXTURE2D_H
