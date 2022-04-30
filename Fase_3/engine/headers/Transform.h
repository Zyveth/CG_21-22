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
        bool align = false;
        vector<Vertice> points;

        // Rotate

        // Static
        float angle = 0.0;

        // All
        float x = 0.0;
        float y = 0.0;
        float z = 0.0;
    
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

        void apply();
};

#endif // TRANSFORM_H