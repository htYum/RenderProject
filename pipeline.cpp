#include "pipeline.h"

#include <QTime>
#include <QDebug>

PipeLine::PipeLine(int _width, int _height):
    width(_width),
    height(_height),
    shader(nullptr),
    frontBuffer(nullptr),
    backBuffer(nullptr)
{
}

PipeLine::~PipeLine()
{
    if(shader)delete shader;
    if(frontBuffer)delete frontBuffer;
    if(backBuffer)delete backBuffer;
    shader = nullptr;
}

void PipeLine::initialize()
{
    if(shader)delete shader;
    if(frontBuffer)delete frontBuffer;
    if(backBuffer)delete backBuffer;

    frontBuffer = new FrameBuffer(width, height);
    backBuffer = new FrameBuffer(width, height);
    shader = new MyShader();
}

void PipeLine::clearBuffer(const vec4 &color, bool depth)
{
    backBuffer->clearColorBuffer(color);
}

void PipeLine::setVertexBuffer(const std::vector<Vertex> &_ver)
{
    vertices = _ver;
}

void PipeLine::setIndexBuffer(const std::vector<unsigned int> _index)
{
    indices = _index;
}

void PipeLine::setShaderMode(ShadingMode mode)
{
    if(shader)delete shader;
    if(mode == simple){
        shader = new MyShader();
    }
}

void PipeLine::swapBuffer()
{
    FrameBuffer* temp = frontBuffer;
    frontBuffer = backBuffer;
    backBuffer = temp;
}

void PipeLine::draw(RenderMode mode)
{
    if(indices.empty())return;
    viewPortMat = getViewPortMatrix(0,0,width,height);
    QTime t;
    t.start();
    for(int i = 0; i < indices.size();  ){
        Vertex a,b,c;
        a = vertices[indices[i++]];
        b = vertices[indices[i++]];
        c = vertices[indices[i++]];
        V2F v1,v2,v3;
        v1 = shader->vertexShader(a);
        v2 = shader->vertexShader(b);
        v3 = shader->vertexShader(c);
        v1.proPos = viewPortMat*v1.proPos;
        v2.proPos = viewPortMat*v2.proPos;
        v3.proPos = viewPortMat*v3.proPos;
        // mode select
        if(mode == wire){
            bresenhamLine(v1,v2);
            bresenhamLine(v2,v3);
            bresenhamLine(v1,v3);
        }
        else if (mode == fill){
            edgeWalking(v1,v2,v3);
        }
    }
}

void PipeLine::bresenhamLine(const V2F &from, const V2F &to)
{
    int dx = to.proPos.x - from.proPos.x;
    int dy = to.proPos.y - from.proPos.y;
    int stepX = 1, stepY = 1;
    if(dx < 0){
        stepX = -1;
        dx = -dx;
    }
    if(dy < 0){
        stepY = -1;
        dy = -dy;
    }
    int d2x = 2*dx;
    int d2y = 2*dy;
    int d2y_d2x = d2y - d2x;
    int drawX = from.proPos.x;
    int drawY = from.proPos.y;
    V2F temp;
    if(dy <= dx){
        int p = d2y-dx;
        for(int i = 0; i <= dx; ++i){
            // get color
            temp = v2fLerp(from,to,static_cast<float>(i)/dx);
            backBuffer->drawPixel(drawX,drawY,shader->fragmentShader(temp));
            drawX+=stepX;
            if(p<=0){
                p+=d2y;
            }
            else if(p>0){
                drawY+=stepY;
                p+=d2y_d2x;
            }
        }
    }
    else if(dy > dx){
        int p = d2x - dy;
        for(int i = 0; i <= dy; ++i){
            // get color
            temp = v2fLerp(from,to,static_cast<float>(i)/dy);
            backBuffer->drawPixel(drawX,drawY,shader->fragmentShader(temp));
            drawY+=stepY;
            if(p<=0){
                p+=d2x;
            }
            else if(p>0){
                drawX+=stepX;
                p-=d2y_d2x;
            }
        }
    }

}

void PipeLine::edgeWalking(const V2F &v1, const V2F &v2, const V2F &v3)
{
    V2F temp;
    V2F arr[3] = {v1,v2,v3};
    if(arr[0].proPos.y > arr[1].proPos.y){
        temp = arr[0];
        arr[0] = arr[1];
        arr[1] = temp;
    }
    if(arr[0].proPos.y > arr[2].proPos.y){
        temp = arr[0];
        arr[0] = arr[2];
        arr[2] = temp;
    }
    if(arr[1].proPos.y > arr[2].proPos.y){
        temp = arr[1];
        arr[1] = arr[2];
        arr[2] = temp;
    }
    if(arr[0].proPos.y == arr[1].proPos.y){
        downTriangle(arr[0],arr[1],arr[2]);
    }
    else if(arr[1].proPos.y == arr[2].proPos.y){
        upTriangle(arr[0],arr[1],arr[2]);
    }
    else{
        float factor = static_cast<float>(arr[1].proPos.y - arr[0].proPos.y)/(arr[2].proPos.y - arr[0].proPos.y);
        V2F mid = v2fLerp(arr[0],arr[2],factor);
        upTriangle(arr[0],mid,arr[1]);
        downTriangle(mid, arr[1],arr[2]);
    }
}

void PipeLine::downTriangle(const V2F &v1, const V2F &v2, const V2F &v3)
{
    V2F left = v1;
    V2F right = v2;
    V2F bottom = v3;
    V2F temp,newLeft,newRight;
    if(left.proPos.x > right.proPos.x){
        temp = left;
        left = right;
        right = temp;
    }
    int dy = bottom.proPos.y - left.proPos.y + 1;
    float factor = 0;
    for(int i = 0; i < dy; ++i){
        if(dy != 0){
            factor = static_cast<float>(i)/dy;
        }
        newLeft = v2fLerp(left,bottom,factor);
        newRight = v2fLerp(right,bottom,factor);
        newLeft.proPos.y = newRight.proPos.y = left.proPos.y + i-1;
        scanLineDraw(newLeft,newRight);
    }
}

void PipeLine::upTriangle(const V2F &v1, const V2F &v2, const V2F &v3)
{
    V2F left = v2;
    V2F right = v3;
    V2F top = v1;
    V2F temp,newLeft,newRight;
    if(left.proPos.x > right.proPos.x){
        temp = left;
        left = right;
        right = temp;
    }
    int dy = left.proPos.y - top.proPos.y + 1;
    float factor = 0;
    for(int i = 0; i < dy; ++i){
        if(dy != 0){
            factor = static_cast<float>(i)/dy;
        }
        newLeft = v2fLerp(left,top,factor);
        newRight = v2fLerp(right,top,factor);
        newLeft.proPos.y = left.proPos.y - i;
        newRight.proPos.y = left.proPos.y - i;
        scanLineDraw(newLeft, newRight);
    }
}

void PipeLine::scanLineDraw(const V2F &left, const V2F &right)
{
    int length = right.proPos.x - left.proPos.x + 1;
    V2F current;
    vec4 color;
    for(int i = 0; i <= length; ++i){
        float factor = static_cast<float>(i)/length;
        current.proPos.x = left.proPos.x + i;
        current.proPos.y = left.proPos.y;
        current.color = left.color*(1.0f-factor)+right.color*factor;
        color = shader->fragmentShader(current);
        backBuffer->drawPixel(current.proPos.x,current.proPos.y,shader->fragmentShader(current));

    }
}

V2F PipeLine::v2fLerp(const V2F &a, const V2F &b, float factor)
{
    V2F result;
    result.worldPos = lerp(a.worldPos,b.worldPos,factor);
    result.proPos = lerp(a.proPos,b.proPos,factor);
    result.color = lerp(a.color,b.color,factor);
    result.normal = lerp(a.normal,b.normal,factor);
    result.texCoord = lerp(a.texCoord,b.texCoord,factor);
    result.oneDivZ = a.oneDivZ*(1.0f-factor)+b.oneDivZ;
    return result;
}
