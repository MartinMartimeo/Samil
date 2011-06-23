#pragma once
#ifndef __graphic_h
#define __graphic_h

#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <time.h>
#include "world.h"


void init_gui(int argc, char **argv, World *pWorld = NULL);

void render(void);

void idle(void); // if idle, do this

void resize(int w, int h);

void processNormalKeys(unsigned char key, int x, int y);

typedef struct CameraOrientation {
	float afVectEye[3];
	float afVectDest[3];
	float afVectUp[3];
} CameraOrientation;

#endif
