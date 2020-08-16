#ifndef RENDERLOOP_H
#define RENDERLOOP_H

#include <QObject>
#include "pipeline.h"
#include "Model/mesh.h"
#include "Control/Camera.h"

class RenderLoop : public QObject
{
    Q_OBJECT
public:
    explicit RenderLoop(int _w, int _h, QObject *parent = nullptr);
    ~RenderLoop();

    int getFps(){return fps;}
    void setFpsZero(){fps = 0;}
    void stop(){bStop = true;}
    void processKey(char key);
    void processMouse(float deltaX, float deltaY);

signals:
    void frameOut(unsigned char* image);
public slots:
    void loop();

private:
    int width,height,nChannel;
    bool bStop;
    int fps;
    PipeLine* pipeLine;
    Camera* camera;



signals:

};

#endif // RENDERLOOP_H
