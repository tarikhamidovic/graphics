#pragma once

#include <GL/glut.h>
#include <math.h>
#include "textures/hex.c"
#include "textures/ice.c"

void hex_texture();
void ice_texture();
void ambient_light();
void core_light();
void draw_electron(const float&, const float&);
void draw_orbit(const float&, const float&, const float&);
void draw_core();
void display();
void idle();
void specialKeys(int, int, int);
void keyboard(unsigned char, int, int);
void mouse(int, int, int, int);
void passiveMouseMotion(int, int);
void reshape(int, int);
void init();
