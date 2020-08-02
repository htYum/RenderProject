#include "Texture2D.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

const float COL_SCALE = (float)1/255;
Texture2D::~Texture2D()
{
    stbi_image_free(pixelBuffer);
    pixelBuffer = nullptr;
}

bool Texture2D::loadImage(const std::string &path)
{
    if(pixelBuffer)delete pixelBuffer;
    pixelBuffer = nullptr;
    width = 0;
    height = 0;
    nChannel = 0;
    pixelBuffer = stbi_load(path.c_str(), &width, &height, &nChannel, 0);
    if(pixelBuffer == nullptr){
        qDebug()<<"Failed to load image from : "<<QString::fromStdString(path);
    }
    unsigned char* p = pixelBuffer;
    return pixelBuffer != nullptr;
}

vec4 Texture2D::sampler2D(const vec2 &texCoord)
{
    vec4 result;
    if(pixelBuffer == nullptr)return result;
    int x = 0, y = 0;
    float u = 0, v = 0;
    if(texCoord.x >= 0 && texCoord.x <= 1.0f && texCoord.y >= 0 && texCoord.y <= 1.0f){
        float trueU = texCoord.x*(width - 1);
        float trueV = texCoord.y*(height - 1);
        x = static_cast<int>(trueU);
        y = static_cast<int>(trueV);
        u = trueU - x;
        v = trueV - y;
    }
    else{
        if(texCoord.x > 1.0f)
            u = texCoord.x - static_cast<int>(texCoord.x);
        else if(texCoord.x < 0)
            u = 1.0f - (static_cast<int>(texCoord.x) - texCoord.x);
        if(texCoord.y > 1.0f)
            v = texCoord.y - static_cast<int>(texCoord.y);
        else if(texCoord.y < 0)
            v = 1.0f - (static_cast<int>(texCoord.y) - texCoord.y);
        float trueU = u*(width - 1);
        float trueV = v*(width - 1);
        x = static_cast<int>(trueU);
        y = static_cast<int>(trueV);
        u = trueU - x;
        v = trueV - y;
    }
    vec3 texels[4];
    int index[4];
    index[0] = (x*width + y)*nChannel;
    if(y + 1 >= height)
        index[1] = index[0];
    else
        index[1] = (x * width + y + 1) * nChannel;
    if(y + 1 >= height || x + 1 >= width)
        index[2] = index[0];
    else
        index[2] = ((x + 1) * width + y + 1) * nChannel;
    if(x + 1 >= width)
        index[3] = index[0];
    else
        index[3] = ((x + 1) * width + y) * nChannel;

    // left bottom
    texels[0].x = pixelBuffer[index[0] + 0]*COL_SCALE;
    texels[0].y = pixelBuffer[index[0] + 1]*COL_SCALE;
    texels[0].z = pixelBuffer[index[0] + 2]*COL_SCALE;

    // left top
    texels[1].x = pixelBuffer[index[1] + 0]*COL_SCALE;
    texels[1].y = pixelBuffer[index[1] + 1]*COL_SCALE;
    texels[1].z = pixelBuffer[index[1] + 2]*COL_SCALE;

    // right top
    texels[2].x = pixelBuffer[index[2] + 0]*COL_SCALE;
    texels[2].y = pixelBuffer[index[2] + 1]*COL_SCALE;
    texels[2].z = pixelBuffer[index[2] + 2]*COL_SCALE;

    // right bottom
    texels[3].x = pixelBuffer[index[3] + 0]*COL_SCALE;
    texels[3].y = pixelBuffer[index[3] + 1]*COL_SCALE;
    texels[3].z = pixelBuffer[index[3] + 2]*COL_SCALE;

    // bilinear interpolation.
    // horizational
    texels[0] = texels[0] * (1.0 - u) + texels[3] * u;
    texels[1] = texels[1] * (1.0 - u) + texels[2] * u;

    result = texels[0] * (1.0 - v) + texels[1] *v;

    return result;
}
