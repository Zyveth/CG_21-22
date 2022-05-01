#define _USE_MATH_DEFINES
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "../headers/Transform.h"

void Transform::setType(int newType)
{
    type = newType;
}

void Transform::setID(int newID)
{
    id = newID;
}

void Transform::setTime(float newTime)
{
    time = newTime;
}

void Transform::setAlign(bool newAlign)
{
    align = newAlign;
}

void Transform::addPoint(Vertice toAdd)
{
    points.push_back(toAdd);
}

void Transform::setAngle(float newAngle)
{
    angle = newAngle;
}

void Transform::setX(float newX)
{
    x = newX;
}

void Transform::setY(float newY)
{
    y = newY;
}

void Transform::setZ(float newZ)
{
    z = newZ;
}

void Transform::apply(float fps)
{
    if(type == 0)
    {
        if(id == 0)
        {
            glTranslatef(x, y, z);
        }
        else
        {
            glBegin(GL_LINE_LOOP);

            for(int i = 0; i < 100; i++)
	        {
		        float gt = (float) i / 100.0;

		        float pos[3];
		        float deriv[3];

		        getGlobalCatmullRomPoint(gt, pos, deriv);

		        glVertex3f(pos[0], pos[1], pos[2]);
	        }

            glEnd();

            float pos[3];
		    float deriv[3];

		    getGlobalCatmullRomPoint(tg, pos, deriv);

            glTranslatef(pos[0], pos[1], pos[2]);
            
            if(align)
            {
                float z[3];

                cross(deriv, yt, z);
	            cross(z, deriv, yt);

                normalize(deriv);
	            normalize(yt);
	            normalize(z);

                float m[16];
	            buildRotMatrix(deriv, yt, z, m);

	            glMultMatrixf(m);
            }

            tg += 1 / (time * fps);
        }
    }
    else if (type == 1)
    {
        if(id == 0)
        {
            glRotatef(angle, x, y, z);
        }
        else
        {
            angle += 360.0 / (time * fps);

            glRotatef(angle, x, y, z);
        }
    }
    else
    {
        glScalef(x, y, z);
    }
    
}

void Transform::getGlobalCatmullRomPoint(float gt, float* pos, float* deriv)
{
    float t = gt * points.size();
    int index = floor(t);

    t = t - index;

    int indices[4];
    indices[0] = (index + points.size() - 1) % points.size();	
	indices[1] = (indices[0] + 1) % points.size();
	indices[2] = (indices[1] + 1) % points.size(); 
	indices[3] = (indices[2] + 1) % points.size();

	getCatmullRomPoint(t, points[indices[0]], points[indices[1]], points[indices[2]], points[indices[3]], pos, deriv);
}

void Transform::getCatmullRomPoint(float t, Vertice p0, Vertice p1, Vertice p2, Vertice p3, float* pos, float* deriv)
{
    float m[4][4] = {	{-0.5f,  1.5f, -1.5f,  0.5f},
						{ 1.0f, -2.5f,  2.0f, -0.5f},
						{-0.5f,  0.0f,  0.5f,  0.0f},
						{ 0.0f,  1.0f,  0.0f,  0.0f}};
	
	float tm[4] = { powf(t, 3.0), powf(t, 2.0), t, 1.0};
	float tmd[4] = { powf(t, 2.0), t, 1.0, 0.0};
	
	for(int i = 0; i < 3; i++)
	{
		float P[4];

        if(i == 0)
        {
            P[0] = p0.getX();
            P[1] = p1.getX();
            P[2] = p2.getX();
            P[3] = p3.getX();
        }
        else if(i == 1)
        {
            P[0] = p0.getY();
            P[1] = p1.getY();
            P[2] = p2.getY();
            P[3] = p3.getY();
        }
        else
        {
            P[0] = p0.getZ();
            P[1] = p1.getZ();
            P[2] = p2.getZ();
            P[3] = p3.getZ();
        }

		float a[4];
		multMatrixVector((float*) m, P, a);

		pos[i] = 0.0;
		deriv[i] = 0.0;

		for(int j = 0; j < 4; j++)
		{
			pos[i] += tm[j] * a[j];
			deriv[i] += tmd[j] * a[j];
		}
	}
}

void Transform::multMatrixVector(float *m, float *v, float *res)
{
    for (int j = 0; j < 4; ++j) 
    {
		res[j] = 0;
		for (int k = 0; k < 4; ++k) 
        {
			res[j] += v[k] * m[j * 4 + k];
		}
	}
}

void Transform::cross(float* a, float* b, float* res) {

	res[0] = a[1]*b[2] - a[2]*b[1];
	res[1] = a[2]*b[0] - a[0]*b[2];
	res[2] = a[0]*b[1] - a[1]*b[0];
}

void Transform::normalize(float* a) 
{
	float l = sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
	a[0] = a[0]/l;
	a[1] = a[1]/l;
	a[2] = a[2]/l;
}

void Transform::buildRotMatrix(float* x, float* y, float* z, float* m) 
{
	m[0] = x[0]; m[1] = x[1]; m[2] = x[2]; m[3] = 0;
	m[4] = y[0]; m[5] = y[1]; m[6] = y[2]; m[7] = 0;
	m[8] = z[0]; m[9] = z[1]; m[10] = z[2]; m[11] = 0;
	m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}