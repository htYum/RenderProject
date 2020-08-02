#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "Math/mymath.h"
#include <vector>

class FrameBuffer
{
private:
    int width, heigth, nChannel;
    std::vector<unsigned char> colorBuffer;
    std::vector<float> depthBuffer;
public:
    FrameBuffer(int w,int h);
    FrameBuffer(int w,int h,int n);

    int getWidth(){return width;}
    int getHeight(){return heigth;}
    int getnChannel(){return nChannel;}
    float getDepth(int x, int y);
    unsigned char* getColorBuffer(){return colorBuffer.data();}

    void clearColorBuffer(const vec4& color);
    void drawPixel(int x, int y, const vec4& color);
    void setDepth(int x, int y, float d);
};

#endif // FRAMEBUFFER_H
