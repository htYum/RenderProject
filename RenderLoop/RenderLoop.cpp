#include "renderloop.h"

RenderLoop::RenderLoop(int _w, int _h, QObject *parent):
    QObject(parent),
    width(_w),
    height(_h),
    nChannel(4),
    fps(0),
    bStop(false)
{
    pipeLine = new PipeLine(_w,_h);
}

RenderLoop::~RenderLoop()
{
    if(pipeLine)delete pipeLine;
    pipeLine = nullptr;
}

void RenderLoop::loop()
{
    fps = 0;
    Mesh mesh;
    mesh.testSquare(
                vec3(0,-1.0f,0),
                vec3(-1.0f,0,0),
                vec3(0,1.0f,0),
                vec3(1.0f,0,0),
                vec4(0.8f,0.3f,0,1.0f),
                vec4(0,0.5f,0,1.0f),
                vec4(1.0f,1.0f,1.0f,1.0f),
                vec4(0.3f,0.8f,0,1.0f));
//    mesh.testTriangle(
//                vec3(0,-1.0f,0),
//                vec3(-1.0f,0,0),
//                vec3(0,1.0f,0),
//                vec4(0.8f,0.3f,0,1.0f),
//                vec4(0,0.5f,0,1.0f),
//                vec4(1.0f,1.0f,1.0f,1.0f));
    pipeLine->initialize();
    pipeLine->setVertexBuffer(mesh.vertices);
    pipeLine->setIndexBuffer(mesh.indices);
    while(!bStop){
        pipeLine->clearBuffer(vec4(0.2f,0.5f,0.8f,1.0f));
        pipeLine->draw(RenderMode::fill);
        pipeLine->swapBuffer();
        emit frameOut(pipeLine->outPut());
        ++fps;
    }
}
