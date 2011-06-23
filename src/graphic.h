#pragma once
#ifndef __graphic_h
#define __graphic_h

#include <iostream>
#include <GL/glut.h>
#include <vector>
#include "world.h"

void init_gui(int argc, char **argv, World *pWorld = NULL);

void render(void);

void idle(void); // if idle, do this

void resize(int w, int h);

void processNormalKeys(unsigned char key, int x, int y);

#endif
