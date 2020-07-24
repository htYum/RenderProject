#include "framebuffer.h"

FrameBuffer::FrameBuffer(int w, int h):
    width(w),
    heigth(h),
    // RGBA
    nChannel(4)
{
    colorBuffer.resize(w*h*4,0);
}

void FrameBuffer::clearColorBuffer(const vec4 &color)
{
    unsigned char r = static_cast<unsigned char>(color.x*255);
    unsigned char g = static_cast<unsigned char>(color.y*255);
    unsigned char b = static_cast<unsigned char>(color.z*255);
    unsigned char a = static_cast<unsigned char>(color.w*255);
    unsigned char* p = colorBuffer.data();
    for(int i = 0; i < width*heigth*nChannel; i += nChannel){
        *(p+0) = r;
        *(p+1) = g;
        *(p+2) = b;
        *(p+3) = a;
        p+=nChannel;
    }
}

void FrameBuffer::drawPixel(int x, int y, const vec4 &color)
{
    if(x < 0 || y < 0 || x >= width || y >= heigth)
        return;
    int index = y*nChannel*width + x*nChannel;
    unsigned char* p = colorBuffer.data()+index;
    *(p+0) = static_cast<unsigned char>(color.x*255);
    *(p+1) = static_cast<unsigned char>(color.y*255);
    *(p+2) = static_cast<unsigned char>(color.z*255);
    *(p+3) = static_cast<unsigned char>(color.w*255);
}
