#include <fstream>
#include <iostream>
#include <string.h>

#include "../headers/Bezier.h"
#include "../headers/Vertice.h"
#include "../headers/Shape.h"

using namespace std;

void Bezier::parseBezier(const char* inputFile)
{
    // ----------------------------------------------------------
    // Parse input file
    // ----------------------------------------------------------

    vector<Vertice> bezierPoints;
    ifstream file(inputFile);
    string line;
    int patches_nr = 0, points_nr = 0;

    if(file.fail())
    {
        cout << "Couldn't find file: " << inputFile << endl;
    }

    // Number of patches
    getline(file, line);
    patches_nr = stoi(line);
    int patch_index[patches_nr][16];

    for(int i = 0; i < patches_nr; i++)
    {
        getline(file, line);

        for(int j = 0; j < 16; j++)
        {
            int split = line.find(",");
            string s = line.substr(0, split);
            patch_index[i][j] = stoi(s);
            line.erase(0, split + 1);
        }
    }

    // Number of points
    getline(file, line);
    points_nr = stoi(line);
    int cr[3];

    for(int i = 0; i < points_nr; i++)
    {
        getline(file, line);
        for(int j = 0; j < 3; j++)
        {
            int split = line.find(",");
            string s = line.substr(0, split);
            cr[j] = stof(s);
            line.erase(0, split + 1);
        }

        bezierPoints.push_back(Vertice(cr[0], cr[1], cr[2]));
    }

    for(int i = 0; i < patches_nr; i++)
    {
        Shape s;

        for(int j = 0; j < 16; j++)
        {
            Vertice auxvertice = bezierPoints.at(patch_index[i][j]);
            s.addVertice(auxvertice);       
        }

        patches.push_back(s);
    }
}

void Bezier::bezierPoints(int tessellation)
{
    float divisions = 1.0 / tessellation, u, u2, v, v2;

    for(int i = 0; i < patches.size(); i++)
    {
        Shape s = patches.at(i);

        for(int vs = 0; vs < tessellation; vs++)
        {
            for(int us = 0; us < tessellation; us++)
            {
                u = us * divisions;
                u2 = (us + 1) * divisions;
                v = vs * divisions;
                v2 = (vs + 1) * divisions;
                Vertice p1 = bezierPatch(u, v, s);
                Vertice p2 = bezierPatch(u2, v, s);
                Vertice p3 = bezierPatch(u, v2, s);
                Vertice p4 = bezierPatch(u2, v2, s);

                this->addVertice(p2);
                this->addVertice(p1);
                this->addVertice(p4);

                this->addVertice(p1);
                this->addVertice(p3);
                this->addVertice(p4);
            }
        }
    }
}

Vertice Bezier::bezierPatch(float u, float v, Shape patch)
{
    Vertice pts_u[4];
    Vertice pts_v[4];

    int j = 0, k = 0;

    for(int i = 0; i < 16; i++)
    {
        Vertice aux = patch.getVertice(i);
        pts_u[j] = aux;
        j++;

        if(j % 4 == 0)
        {
            pts_v[k++] = bValue(u, pts_u[0], pts_u[1], pts_u[2], pts_u[3]);

            j = 0;
        }
    }

    Vertice res = bValue(v, pts_v[0], pts_v[1], pts_v[2], pts_v[3]);

    return res;
}

Vertice Bezier::bValue(float u, Vertice p0, Vertice p1, Vertice p2, Vertice p3)
{
    float b0 = (1.0 - u) * (1.0 - u) * (1.0 - u);
    float b1 = 3.0 * u * (1.0 - u) * (1.0 - u);
    float b2 = 3 * u * u * (1.0 - u);
    float b3 = u * u * u;

    float x = p0.getX() * b0 + p1.getX() * b1 + p2.getX() * b2 + p3.getX() * b3;
    float y = p0.getY() * b0 + p1.getY() * b1 + p2.getY() * b2 + p3.getY() * b3;
    float z = p0.getZ() * b0 + p1.getZ() * b1 + p2.getZ() * b2 + p3.getZ() * b3;

    return Vertice(x, y, z);
}