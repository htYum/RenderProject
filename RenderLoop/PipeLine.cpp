#include "pipeline.h"

#include <QTime>
#include <QDebug>

PipeLine::PipeLine(int _width, int _height):
    width(_width),
    height(_height),
    shader(nullptr),
    frontBuffer(nullptr),
    backBuffer(nullptr),
    texture(nullptr)
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
    if(texture)delete texture;

    frontBuffer = new FrameBuffer(width, height);
    backBuffer = new FrameBuffer(width, height);
    shader = new MyShader();
    texture = new Texture2D();
    texture->loadImage("texture.jpg");
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

void PipeLine::setShader(MyShader* _s)
{
    shader = _s;
    shader->setTexture(texture);
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
        perspectDiv(v1);
        perspectDiv(v2);
        perspectDiv(v3);

        if(backFaceCullint(v1.proPos,v2.proPos,v3.proPos))continue;
//        if(shouleBeClip(v1,v2,v3))continue;

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
    for(int i = 0; i <= length; ++i){
        float factor = static_cast<float>(i)/length;
        current = v2fLerp(left,right,factor);
        current.proPos.x = left.proPos.x + i;
        current.proPos.y = left.proPos.y;

        float depth = backBuffer->getDepth(current.proPos.x,current.proPos.y);
        if(current.proPos.z>depth)continue;
        backBuffer->setDepth(current.proPos.x,current.proPos.y,current.proPos.z);

        float w = 1.0/current.oneDivZ;
        current.worldTransPos *= w;
        current.normal *= w;
        current.color *= w;
        current.texCoord *= w;
        current.color = shader->fragmentShader(current);
        backBuffer->drawPixel(current.proPos.x,current.proPos.y,current.color);

    }
}

void PipeLine::perspectDiv(V2F &v)
{
    v.proPos /= v.proPos.w;
    v.proPos.w = 1.0f;
    v.proPos.z = (v.proPos.z + 1.0)*0.5;
}

bool PipeLine::shouleBeClip(const V2F &v1, const V2F &v2, const V2F &v3)
{
    if(v1.proPos.z>1.0f && v2.proPos.z>1.0f && v3.proPos.z>1.0f)return true;
    if(v1.proPos.z<-1.0f && v2.proPos.z<-1.0f && v3.proPos.z<-1.0f)return true;
    float minx,miny,maxx,maxy;
    minx = fmin(v1.proPos.x,fmin(v2.proPos.x,v3.proPos.x));
    miny = fmin(v1.proPos.y,fmin(v2.proPos.y,v3.proPos.y));
    maxx = fmax(v1.proPos.x,fmax(v2.proPos.x,v3.proPos.x));
    maxy = fmax(v1.proPos.y,fmax(v2.proPos.y,v3.proPos.y));
    if(minx<-1.0f || maxx>1.0f || miny<-1.0f || maxy>1.0f)return true;
    return false;
}

bool PipeLine::backFaceCullint(const vec4 &v1, const vec4 &v2, const vec4 &v3)
{
    vec3 tmp1 = vec3(v2.x-v1.x,v2.y-v1.y,v2.z-v1.z);
    vec3 tmp2 = vec3(v3.x-v1.x,v3.y-v1.y,v3.z-v1.z);
    vec3 normal = cross(tmp1,tmp2);
    vec3 view(0,0,1);
    return dot(view,normal)<0;
}

V2F PipeLine::v2fLerp(const V2F &a, const V2F &b, float factor)
{
    V2F result;
    result.worldTransPos = lerp(a.worldTransPos,b.worldTransPos,factor);
    result.proPos = lerp(a.proPos,b.proPos,factor);
    result.color = lerp(a.color,b.color,factor);
    result.normal = lerp(a.normal,b.normal,factor);
    result.texCoord = lerp(a.texCoord,b.texCoord,factor);
    result.oneDivZ = a.oneDivZ*(1.0f-factor)+b.oneDivZ*factor;
    return result;
}
