#ifndef PIPELINE_H
#define PIPELINE_H

#include "Shader/myshader.h"
#include "framebuffer.h"
#include "Model/Texture2D.h"
#include "Model/Model.h"

enum ShadingMode{
    simple
};

class PipeLine
{
private:
    int width, height;
    FrameBuffer* frontBuffer;
    FrameBuffer* backBuffer;
    mat4x4 viewPortMat;
    Model* model;
    MyShader* nowShader;

    int meshIndex;

public:
    PipeLine(int _width, int _height);
    ~PipeLine();

    void setNowShader(MyShader* _shader){nowShader = _shader;}

    void initialize();
    void clearBuffer(const vec4& color, bool depth = false);
    void swapBuffer();
    unsigned char* outPut(){return frontBuffer->getColorBuffer();}
    void setModel(Model* _model);

    void draw();
//    void bresenhamLine(const V2F& from, const V2F& to);
    void edgeWalking(const V2F& v1, const V2F& v2, const V2F& v3);
    void downTriangle(const V2F& v1,const V2F& v2, const V2F& v3);
    void upTriangle(const V2F& v1, const V2F& v2, const V2F& v3);
    void scanLineDraw(const V2F& left, const V2F& right);
    void perspectDiv(V2F& v);
    bool shouleBeClip(const V2F& v1, const V2F& v2, const V2F& v3);
    bool backFaceCullint(const vec4& v1, const vec4& v2, const vec4& v3);

    V2F v2fLerp(const V2F& a, const V2F& b, float factor);
};

#endif // PIPELINE_H
