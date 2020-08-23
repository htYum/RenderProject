#include "renderloop.h"

#include "RenderLoop/Model/Model.h"
#include "Shader/Light/DirectionLight.h"

RenderLoop::RenderLoop(int _w, int _h, QObject *parent):
    QObject(parent),
    width(_w),
    height(_h),
    nChannel(4),
    bStop(false),
    fps(0),
    pipeLine(nullptr)
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
//    Mesh mesh;
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
//    mesh.testBox(0.7f,0.7f,0.7f);
    pipeLine->initialize();
//    pipeLine->setVertexBuffer(mesh.vertices);
//    pipeLine->setIndexBuffer(mesh.indices);

    Model* myModel = new Model("C:\\Users\\侯祖光\\desktop\\Model\\neptune\\neptune.obj");

    Texture2D* bodyTex = new Texture2D();
    bodyTex->loadImage("C:\\Users\\侯祖光\\desktop\\Model\\neptune\\Tex002f_body02.jpg");
    Material* bodyMat = new Material();
    bodyMat->setTexture(bodyTex);
    myModel->meshes[2].setMaterial(bodyMat);

    Texture2D* mouseTex = new Texture2D();
    mouseTex->loadImage("C:\\Users\\侯祖光\\desktop\\Model\\neptune\\Texf_mouse.jpg");
    Material* mouseMat = new Material();
    mouseMat->setTexture(mouseTex);
    myModel->meshes[0].setMaterial(mouseMat);

    Texture2D* eyeTex = new Texture2D();
    eyeTex->loadImage("C:\\Users\\侯祖光\\desktop\\Model\\neptune\\Tex001f_eye.jpg");
    Material* eyeMat = new Material();
    eyeMat->setTexture(eyeTex);
    myModel->meshes[3].setMaterial(eyeMat);

    Texture2D* faceTex = new Texture2D();
    faceTex->loadImage("C:\\Users\\侯祖光\\desktop\\Model\\neptune\\Tex002f_body01.jpg");
    Material* faceMat = new Material();
    faceMat->setTexture(faceTex);
    myModel->meshes[1].setMaterial(faceMat);


    MyShader* shader = new MyShader();

    pipeLine->setModel(myModel);
    pipeLine->setNowShader(shader);
    float angle = 0;

    /*===============================*/
    DirectionLight* dirLight = new DirectionLight();
    shader->setDirLight(dirLight);

    while(!bStop){
        pipeLine->clearBuffer(vec4(0.2f,0.5f,0.85f,1.0f));

        mat4x4 model;
        scale(model, vec3(0.01f, 0.01f, 0.01f));
        rotate(model, angle, vec3(0,1.0,0));
        angle+=1.0f;
        if(angle>360.0f)angle = 0;
        shader->setMat4Moedl(model);
//        qDebug()<<dirLight->dir.x<<" "<<dirLight->dir.y<<" "<<dirLight->dir.z;
//        qDebug()<<camera->getPostion().x<<" "<<camera->getPostion().y<<" "<<camera->getPostion().z;

        mat4x4 view;
        view= camera->getViewMatrix();
        shader->setMat4View(view);

        mat4x4 projection = perspective(45.0f, static_cast<float>(width)/height, 0.1f, 100.0f);
        shader->setMat4Projection(projection);

        pipeLine->draw();
        pipeLine->swapBuffer();
        emit frameOut(pipeLine->outPut());
        ++fps;
    }
}
