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
        Vertice(float xp, float yp, float zp);
        float getX();
        float getY();
        float getZ();
        void serialize(int fd);
        void deserialize(int fd);
};

#endif // VERTICE_H