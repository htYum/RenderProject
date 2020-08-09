#include "Camera.h"

#include <QDebug>
Camera::Camera(const vec3 &pos):
    bUpdate(true),
    worldUp(vec3(0,1,0)),
    worldForward(vec3(0,0,-1)),
    worldRight(vec3(1,0,0)),
    translation(pos)
{
    cameraForward = worldForward;
    cameraUp = worldUp;
    cameraRight = worldRight;
    yaw = 0;
    pitch = 0;
}

vec3 Camera::getPostion()
{
    return translation;
}

mat4x4 Camera::getViewMatrix()
{
//    if(bUpdate){
//        bUpdate = false;
//        viewMatrix = rotation.conjugate().toMatrix();
//        mat4x4 trans;
//        translate(trans, -translation);
//        viewMatrix = trans*viewMatrix;
//    }
//    return viewMatrix;
    return lookAt(translation, translation+cameraForward, cameraUp);
}

void Camera::onKeyPress(char key)
{
//    switch (key) {
//    case 'W':
//        this->translateDelta(forward()*KEY_MOVE_SPEED);
//        break;
//    case 'S':
//        this->translateDelta(-forward()*KEY_MOVE_SPEED);
//        break;
//    case 'D':
//        this->translateDelta(right()*KEY_MOVE_SPEED);
//        break;
//    case 'A':
//        this->translateDelta(-right()*KEY_MOVE_SPEED);
//        break;
//    case 'E':
//        this->translateDelta(up()*KEY_MOVE_SPEED);
//        break;
//    case 'Q':
//        this->translateDelta(-up()*KEY_MOVE_SPEED);
//        break;
//    default:
//        break;
//    }
    switch (key) {
    case 'W':
        this->translateDelta(cameraForward*KEY_MOVE_SPEED);
        break;
    case 'S':
        this->translateDelta(-cameraForward*KEY_MOVE_SPEED);
        break;
    case 'D':
        this->translateDelta(cameraRight*KEY_MOVE_SPEED);
        break;
    case 'A':
        this->translateDelta(-cameraRight*KEY_MOVE_SPEED);
        break;
    case 'E':
        this->translateDelta(worldUp*KEY_MOVE_SPEED);
        break;
    case 'Q':
        this->translateDelta(-worldUp*KEY_MOVE_SPEED);
        break;
    default:
        break;
    }
}

void Camera::onMouseMove(float deltaX, float deltaY)
{
    deltaX *= MOUSE_MOVE_SPEED;
    deltaY *= MOUSE_MOVE_SPEED;
//    this->rotate(worldUp, -deltaX);
//    this->rotate(right(), -deltaY);

    yaw -= deltaX;
    pitch -= deltaY;
    vec3 front;
    front.x = -sin(radians(yaw));
    front.y = sin(radians(pitch));
    front.z = -cos(radians(pitch))*cos(radians(yaw));
    cameraForward = normalize(front);
    cameraRight = normalize(cross(cameraForward,worldUp));
    cameraUp = normalize(cross(cameraRight,cameraForward));
}

void Camera::translateDelta(const vec3 &delta)
{
    bUpdate = true;
    translation += delta;
}

void Camera::rotate(const vec3 &axis, float angle)
{
    bUpdate = true;
    Quaternion rot;
    rot.rotate(axis, angle);
    rotation = rot*rotation;
}

void Camera::setTranslation(const vec3 &vec)
{
    bUpdate = true;
    translation = vec;
}

void Camera::setRotation(const Quaternion &quat)
{
    bUpdate = true;
    rotation = quat;
}

vec3 Camera::forward() const
{
    return rotation * worldForward;
}

vec3 Camera::up() const
{
    return rotation * worldUp;
}

vec3 Camera::right() const
{
    return rotation * worldRight;
}
