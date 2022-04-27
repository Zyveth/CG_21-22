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

float Camera::getAngleUpdate()
{
    return angle_update;
}

float Camera::getAlpha()
{
    return alpha;
}

float Camera::getBeta()
{
    return beta;
}

float Camera::getDX()
{
    return dx;
}

float Camera::getDY()
{
    return dy;
}

float Camera::getDZ()
{
    return dz;
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

void Camera::setAlpha(float new_alpha)
{
    alpha = new_alpha;
}

void Camera::setBeta(float new_beta)
{
    beta = new_beta;
}

void Camera::setDX(float new_dx)
{
    dx = new_dx;
}

void Camera::setDY(float new_dy)
{
    dy = new_dy;
}

void Camera::setDZ(float new_dz)
{
    dz = new_dz;
}