#ifndef VERTICE_H
#define VERTICE_H

class Vertice
{
    private:
        float x;
        float y;
        float z;

        Vertice subVertice(Vertice v);
        void cross(Vertice v);

    public:
        Vertice();
        Vertice(float xp, float yp);
        Vertice(float xp, float yp, float zp);
        float getX();
        float getY();
        float getZ();
        Vertice normalize();
        Vertice normalizeB(Vertice v1, Vertice v2);
};

#endif // VERTICE_H