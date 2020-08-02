#ifndef PIPELINE_H
#define PIPELINE_H

#include "Shader/myshader.h"
#include "RenderLoop/framebuffer.h"
#include "RenderLoop/Texture2D.h"

enum ShadingMode{
    simple
};

enum RenderMode{
    wire,
    fill
};

class PipeLine
{
private:
    int width, height;
    MyShader* shader;
    FrameBuffer* frontBuffer;
    FrameBuffer* backBuffer;
    mat4x4 viewPortMat;
    Texture2D* texture;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

public:
    PipeLine(int _width, int _height);
    ~PipeLine();

    void initialize();
    void clearBuffer(const vec4& color, bool depth = false);
    void setVertexBuffer(const std::vector<Vertex>& _ver);
    void setIndexBuffer(const std::vector<unsigned int> _index);
    void setShader(MyShader* _s);
    void setRenderMode(RenderMode mode);
    void swapBuffer();
    unsigned char* outPut(){return frontBuffer->getColorBuffer();}
    void draw(RenderMode mode);
    void bresenhamLine(const V2F& from, const V2F& to);
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
