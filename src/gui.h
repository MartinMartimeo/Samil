/*Wrapping GLUT in a class because I'm sick of using global
 * vars.
 */

#pragma once
#ifndef __gui_h
#define __gui_h

#include <iostream>
#include <GL/glut.h>
#include <vector>
#include "game.h"

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

    Gui(int argc, char **argv, Game *m_pGame = NULL);
    virtual ~Gui();

    /**********************************************************************/
    // Functions
    
    void init(int argc, char **argv);
    static void render(void);
    static void idle(void);
    static void resize(int w, int h);
    static void processNormalKeys(unsigned char key, int x, int y);
    static void updatePerspective();
    void renderWater(float x, float y);
    void renderTree(float x, float y);
    void renderMountain(float x, float y);
    void renderEmpty();
    //void transformArraytoCoordinates(int x, y);

    /**********************************************************************/
    // Getter
    static Gui *m_this;


    /**********************************************************************/

private:

    /**********************************************************************/
    // functions


    /**********************************************************************/
    // private Getter



    /**********************************************************************/
    // private Setter

    void SetHeight(unsigned int i);
    unsigned int GetHeight();
    void SetWidth(unsigned int i);
    unsigned int GetWidth();
    void RenderWorld();
    CameraOrientation stCamOrient;
    unsigned int m_iWidth, m_iHeight;
    float m_fFovyAngle;
    float m_fWindowRatio;
    int m_iWindowWidth;
    int m_iWindowHeight;
    Game *m_pGame;


};

#endif
