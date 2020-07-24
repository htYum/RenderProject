#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "mymath.h"
#include <vector>

class FrameBuffer
{
private:
    int width, heigth, nChannel;
    std::vector<unsigned char> colorBuffer;
public:
    FrameBuffer(int w,int h);
    FrameBuffer(int w,int h,int n);

    int getWidth(){return width;}
    int getHeight(){return heigth;}
    int getnChannel(){return nChannel;}
    unsigned char* getColorBuffer(){return colorBuffer.data();}

    void clearColorBuffer(const vec4& color);
    void drawPixel(int x, int y, const vec4& color);
};

#endif // FRAMEBUFFER_H
