/*Wrapping GLUT in a class because I'm sick of using global
 * vars.
 */

#pragma once
#ifndef __gui_h
#define __gui_h

#include <iostream>
#include <GL/glut.h>
#include <vector>
#include "world.h"

class Gui;

typedef struct CameraOrientation {
	float afVectEye[3];
	float afVectDest[3];
	float afVectUp[3];
} CameraOrientation;

// Source here

class Gui {
public:

    /**********************************************************************/
    // Konstruktor, Destruktor

    Gui(int argc, char **argv, World *pWorld = NULL);
    ~Gui();

    /**********************************************************************/
    // Functions
    
    void init(int argc, char **argv);
    static void render(void);
    static void idle(void);
    static void resize(int w, int h);
    static void processNormalKeys(unsigned char key, int x, int y);

    /**********************************************************************/
    // Getter



    /**********************************************************************/

private:

    /**********************************************************************/
    // functions


    /**********************************************************************/
    // private Getter



    /**********************************************************************/
    // private Sette

    void SetHeight(unsigned int i);
    unsigned int GetHeight();
    void SetWidth(unsigned int i);
    unsigned int GetWidth();

    CameraOrientation stCamOrient;
    unsigned int m_iWidth, m_iHeight;


};

#endif
