#ifndef RENDERLOOP_H
#define RENDERLOOP_H

#include <QObject>
#include "pipeline.h"
#include "mesh.h"

class RenderLoop : public QObject
{
    Q_OBJECT
public:
    explicit RenderLoop(int _w, int _h, QObject *parent = nullptr);
    ~RenderLoop();

    int getFps(){return fps;}
    void setFpsZero(){fps = 0;}
    void stop(){bStop = true;}

signals:
    void frameOut(unsigned char* image);
public slots:
    void loop();

private:
    int width,height,nChannel;
    bool bStop;
    int fps;
    PipeLine* pipeLine;



signals:

};

#endif // RENDERLOOP_H
