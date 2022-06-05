#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <vector>

#include "Vertice.h"

using namespace std;

class Transform
{
    private:
        int type = 0; // Type 0 - Translate | 1 - Rotate | 2 - Scale

        // Translate | Rotate
        int id = 0; // Static or dynamic
        // Dynamic
        float time = 0.0;

        // Translate
        // Dynamic
        bool drawCurves = true;
        bool align = false;
        float tg = 0;
        int frame = 0;
        float yt[3] = {0, 1, 0};
        vector<Vertice> points;

        // Rotate

        // Static
        float angle = 0.0;

        // All
        float x = 0.0;
        float y = 0.0;
        float z = 0.0;

        void getGlobalCatmullRomPoint(float gt, float* pos, float* deriv);
        void getCatmullRomPoint(float t, Vertice p0, Vertice p1, Vertice p2, Vertice p3, float* pos, float* deriv);
        void multMatrixVector(float* m, float* v, float* res);

        void cross(float* a, float* b, float* res);
        void normalize(float* a);
        void buildRotMatrix(float* x, float* y, float* z, float* m);
    
    public:
        void setType(int newType);

        void setID(int newID);
        void setTime(float newTime);

        void setAlign(bool newAlign);
        void addPoint(Vertice toAdd);

        void setAngle(float newAngle);

        void setX(float newX);
        void setY(float newY);
        void setZ(float newZ);

        void apply(float fps);
};

#endif // TRANSFORM_H