#include "renderloop.h"

RenderLoop::RenderLoop(int _w, int _h, QObject *parent):
    QObject(parent),
    width(_w),
    height(_h),
    nChannel(4),
    fps(0),
    bStop(false),
    pipeLine(nullptr),
    shader(nullptr),
    camera(nullptr)
{
    pipeLine = new PipeLine(_w,_h);
}

RenderLoop::~RenderLoop()
{
    if(pipeLine)delete pipeLine;
    if(camera)delete camera;
    pipeLine = nullptr;
}

void RenderLoop::processKey(char key)
{
    camera->onKeyPress(key);
}

void RenderLoop::processMouse(float deltaX, float deltaY)
{
    camera->onMouseMove(deltaX, deltaY);
}

void RenderLoop::loop()
{
    fps = 0;
    Mesh mesh;
//    mesh.testSquare(
//                vec3(0,-1.0f,0),
//                vec3(-1.0f,0,0),
//                vec3(0,1.0f,0),
//                vec3(1.0f,0,0),
//                vec4(1.0f,0,0,1.0f),
//                vec4(0,1.0f,0,1.0f),
//                vec4(0,0,1.0f,1.0f),
//                vec4(1.0f,1.0f,1.0f,1.0f));
//    mesh.testTriangle(
//                vec3(0,-1.0f,0),
//                vec3(-1.0f,0,0),
//                vec3(0,1.0f,0),
//                vec4(0.8f,0.3f,0,1.0f),
//                vec4(0,0.5f,0,1.0f),
//                vec4(1.0f,1.0f,1.0f,1.0f));
    mesh.testBox(0.7f,0.7f,0.7f);
    pipeLine->initialize();
    pipeLine->setVertexBuffer(mesh.vertices);
    pipeLine->setIndexBuffer(mesh.indices);

    shader = new MyShader();
    pipeLine->setShader(shader);

    camera = new Camera(vec3(0,0,1));

    float angle = 0;

    while(!bStop){
        pipeLine->clearBuffer(vec4(0.2f,0.5f,0.85f,1.0f));

        mat4x4 model;
//        rotate(model, angle, vec3(0,1.0,0));
        angle+=1.0f;
        if(angle>360.0f)angle = 0;
        shader->setMat4Moedl(model);

        mat4x4 view;
        view= camera->getViewMatrix();
//        view = lookAt(vec3(0,0,1),vec3(0,0,0), vec3(0,1,0));
        shader->setMat4View(view);

        mat4x4 projection = perspective(45.0f, (float)width/(float)height, 0.1f, 100.0f);
        shader->setMat4Projection(projection);

        pipeLine->draw(RenderMode::fill);
        pipeLine->swapBuffer();
        emit frameOut(pipeLine->outPut());
        ++fps;
    }
}
