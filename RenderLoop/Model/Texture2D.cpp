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
    return pixelBuffer != nullptr;
}

vec4 Texture2D::sampler2D(const vec2 &texCoord)
{
    vec4 result;
    if(pixelBuffer == nullptr)return result;
    float x = texCoord.x;
    float y = texCoord.y;
    float u = 0, v = 0;
    // repeat
    if(x < 0) x = 1 - x;
    if(y < 0) y = 1 - y;
    while(x > 1)x -= 1;
    while(y > 1)y -= 1;

    x *= width - 1;
    y *= height - 1;
    u = x - static_cast<int>(x);
    v = y - static_cast<int>(y);
    x = static_cast<int>(x);
    y = static_cast<int>(y);

    vec3 texels[4];
    int index[4];
    index[0] = (y*width + x)*nChannel;
    if(y + 1 >= height)
        index[1] = index[0];
    else
        index[1] = (y * width + x + 1) * nChannel;
    if(y + 1 >= height || x + 1 >= width)
        index[2] = index[0];
    else
        index[2] = ((y + 1) * width + x + 1) * nChannel;
    if(x + 1 >= width)
        index[3] = index[0];
    else
        index[3] = ((y + 1) * width + x) * nChannel;

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


//***********************************************************
//***********************************************************


//    vec4 result;
//    float x = texCoord.x;
//    float y = texCoord.y;
//    while(x>=1)x-=1;
//    while(y>=1)y-=1;
//    x = x*(width-1);
//    y = y*(height-1);
//    x = static_cast<int>(x);
//    y = static_cast<int>(y);
//    int index = nChannel*(y*width + x);
//    result.x = static_cast<float>(pixelBuffer[index])*COL_SCALE;
//    result.y = static_cast<float>(pixelBuffer[index+1])*COL_SCALE;
//    result.z = static_cast<float>(pixelBuffer[index+2])*COL_SCALE;
//    result.w = 1.0f;

//    return result;
}
