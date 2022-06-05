#ifndef CAMERA_H
#define CAMERA_H

#include <math.h>

class Camera
{
    private:
        float x_pos;
        float y_pos;
        float z_pos;

        float x_lookAt;
        float y_lookAt;
        float z_lookAt;

        float x_up;
        float y_up;
        float z_up;

        float fov;
        float near;
        float far;

        float delta;

        float alpha = 0.0;
        float beta = 0.0;

        float dx = 1.0 * cos(beta) * sin(alpha);
        float dy = 1.0 * sin(beta);
        float dz = 1.0 * cos(beta) * cos(alpha);

    public:
        Camera();

        void setXPos(float x);
        void setYPos(float y);
        void setZPos(float z);

        void setXLookAt(float x);
        void setYLookAt(float y);
        void setZLookAt(float z);

        void setXUp(float x);
        void setYUp(float y);
        void setZUp(float z);

        void setFov(float new_fov);
        void setNear(float new_near);
        void setFar(float new_far);

        float getXPos();
        float getYPos();
        float getZPos();

        float getXLookAt();
        float getYLookAt();
        float getZLookAt();

        float getXUp();
        float getYUp();
        float getZUp();

        float getXDir();
        float getYDir();
        float getZDir();

        float crossX();
        float crossY();
        float crossZ();

        float* normalize(float x, float y, float z);

        float getFov();
        float getNear();
        float getFar();

        float getMovementSpeed();

        void setDelta(float d);
};

#endif