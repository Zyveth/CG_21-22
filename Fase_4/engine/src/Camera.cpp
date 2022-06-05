#include "../headers/Camera.h"

Camera::Camera()
{
    x_pos = 0.0;
    y_pos = 0.0;
    z_pos = 0.0;

    x_lookAt = 0.0;
    y_lookAt = 0.0;
    z_lookAt = 0.0;

    x_up = 0.0;
    y_up = 0.0;
    z_up = 0.0;

    fov = 0.0;
    near = 0.0;
    far = 0.0;
}

// Getters

float Camera::getXPos()
{
    return x_pos;
}

float Camera::getYPos()
{
    return y_pos;
}

float Camera::getZPos()
{
    return z_pos;
}

float Camera::getXLookAt()
{
    return x_lookAt;
}

float Camera::getYLookAt()
{
    return y_lookAt;
}

float Camera::getZLookAt()
{
    return z_lookAt;
}

float Camera::getXDir()
{
    float a = abs(sqrtf((x_pos * x_pos) + (y_pos * y_pos) + (z_pos * z_pos)));
    return -(x_pos - x_lookAt) / a;
}

float Camera::getYDir()
{
    float a = abs(sqrtf((x_pos * x_pos) + (y_pos * y_pos) + (z_pos * z_pos)));
    return -(y_pos - y_lookAt) / a;
}

float Camera::getZDir()
{
    float a = abs(sqrtf((x_pos * x_pos) + (y_pos * y_pos) + (z_pos * z_pos)));
    return -(z_pos - z_lookAt) / a;
}

float Camera::crossX()
{
    return getYDir() * z_up - getZDir() * y_up;
}

float Camera::crossY()
{
    return getZDir() * x_up - getXDir() * z_up;
}

float Camera::crossZ()
{
    return getXDir() * y_up - getYDir() * x_up;
}

float* Camera::normalize(float x, float y, float z)
{
    float* normalized = (float*) malloc(sizeof(float) * 3);

    float a = abs(sqrtf((x * x) + (y * y) + (z * z)));

    normalized[0] = x / a;
    normalized[1] = y / a;
    normalized[2] = z / a;

    return normalized;
}

float Camera::getXUp()
{
    return x_up;
}

float Camera::getYUp()
{
    return y_up;
}

float Camera::getZUp()
{
    return z_up;
}

float Camera::getFov()
{
    return fov;
}

float Camera::getNear()
{
    return near;
}

float Camera::getFar()
{
    return far;
}

float Camera::getMovementSpeed()
{
    return 1.5 * delta;
}

void Camera::setDelta(float d)
{
    delta = d;
}
// Setters

void Camera::setXPos(float x)
{
    x_pos = x;
}

void Camera::setYPos(float y)
{
    y_pos = y;
}

void Camera::setZPos(float z)
{
    z_pos = z;
}

void Camera::setXLookAt(float x)
{
    x_lookAt = x;
}

void Camera::setYLookAt(float y)
{
    y_lookAt = y;
}

void Camera::setZLookAt(float z)
{
    z_lookAt = z;
}

void Camera::setXUp(float x)
{
    x_up = x;
}

void Camera::setYUp(float y)
{
    y_up = y;
}

void Camera::setZUp(float z)
{
    z_up = z;
}

void Camera::setFov(float new_fov)
{
    fov = new_fov;
}

void Camera::setNear(float new_near)
{
    near = new_near;
}

void Camera::setFar(float new_far)
{
    far = new_far;
}
