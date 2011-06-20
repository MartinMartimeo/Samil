#pragma once
#ifndef __graphic_h
#define __graphic_h

#include <iostream>
#include <GL/glut.h>

void render(void);

void idle(void); // if idle, do this

void Resize(int w, int h);

void processNormalKeys(unsigned char key, int x, int y);

#endif
