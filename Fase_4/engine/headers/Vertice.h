#ifndef VERTICE_H
#define VERTICE_H

class Vertice
{
    private:
        float x;
        float y;
        float z;

    public:
        Vertice();
        Vertice(float xp, float yp);
        Vertice(float xp, float yp, float zp);
        float getX();
        float getY();
        float getZ();
};

#endif // VERTICE_H