/*
Programul afiseaza un patrat pe care il translateaza
pe axa x la apasarea sagetilor stanga, dreapta
*/
#include "glos.h"

#include "gl.h"
#include "glu.h"
#include "glaux.h"

#include <stdio.h>

static GLfloat x = 0;
static GLfloat y = 0;
static GLfloat alpha = 0;


void myinit(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0);
}


void CALLBACK MutaStanga(void)
{
    x -= 10;
}

void CALLBACK MutaDreapta(void)
{
    x += 10;
}

void CALLBACK MutaSus(void)
{
    y += 10;
}

void CALLBACK MutaJos(void)
{
    y -= 10;
}

void CALLBACK rotateLeft(void)
{
    alpha -= 10;
}

void CALLBACK rotateRight(void)
{
    alpha += 10;
}


void CALLBACK display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();


    glTranslatef(x, y, 0.0);
    glRotatef(alpha, 1, 1, 1);

    glColor3f(0.0, 0.0, 1.0);


    GLUquadricObj* quadric = gluNewQuadric();

    gluQuadricOrientation(quadric, GLU_OUTSIDE);

    glLineWidth(4);
    // 1. sfera
    {
        gluQuadricDrawStyle(quadric, GLU_FILL);
        glPushMatrix();
        glTranslatef(-180, 0, 0);
        double radius = 30;
        int slices = 30;
        int stacks = 2;
        gluSphere(quadric, radius, slices, stacks);
        glPopMatrix();
    }

    gluDeleteQuadric(quadric);
    glFlush();
}

void CALLBACK myReshape(GLsizei w, GLsizei h)
{
    if (!h) return;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-160.0, 160.0, -160.0 * (GLfloat)h / (GLfloat)w, 160.0 * (GLfloat)h / (GLfloat)w, -200.0, 200.0);
    else
        glOrtho(-160.0 * (GLfloat)w / (GLfloat)h, 160.0 * (GLfloat)w / (GLfloat)h, -160.0, 160.0, -200.0, 200.0);

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    auxInitDisplayMode(AUX_SINGLE | AUX_RGB);
    auxInitPosition(200, 100, 800, 600);
    auxInitWindow("Quadrics");
    myinit();
    auxKeyFunc(AUX_LEFT, MutaStanga);
    auxKeyFunc(AUX_RIGHT, MutaDreapta);
    auxKeyFunc(AUX_UP, MutaSus);
    auxKeyFunc(AUX_DOWN, MutaJos);
    auxKeyFunc(AUX_w, rotateLeft);
    auxKeyFunc(AUX_s, rotateRight);

    auxReshapeFunc(myReshape);
    auxMainLoop(display);
    return(0);
}