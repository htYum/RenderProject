#ifndef CAMERA_H
#define CAMERA_H

#include <string>

#include "Math/MyMath.h"
#include "Math/Quaternion.h"

const float KEY_MOVE_SPEED = 0.05f;
const float MOUSE_MOVE_SPEED = 0.1f;

class Camera
{
private:
    bool bUpdate;   // true:should update viewMatrix when getViewMatrix() is called
    vec3 worldUp;
    vec3 worldForward;
    vec3 worldRight;
    vec3 translation;
    Quaternion rotation;
    mat4x4 viewMatrix;

    vec3 cameraForward;
    vec3 cameraRight;
    vec3 cameraUp;

    float yaw;
    float pitch;

public:
    Camera(const vec3& pos);
    ~Camera() = default;

    vec3 getPostion();
    mat4x4 getViewMatrix();

    void onKeyPress(char key);
    void onMouseMove(float deltaX, float deltaY);

    void translateDelta(const vec3& delta);          // translate base on translation
    void rotate(const vec3& axis, float angle);
    void setTranslation(const vec3& vec);       //reset translation
    void setRotation(const Quaternion& quat);

    vec3 forward()const;
    vec3 up()const;
    vec3 right()const;
};

#endif // CAMERA_H
