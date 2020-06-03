#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <GL/glut.h>

void draw_teapot(); // crtanje cajnika
void draw_sphere(); // crtanje sfere

void primary_light(); // primarno svjetlo
void secondary_light(); // sekundarno svjetlo

void init();  // postavka svjetala
void display(); // crtanje scene
void reshape(int, int); // promjena prozora

void mouse(int, int, int, int); // radnja na klik misa
void keyboard(unsigned char, int, int); // karakteri tastature

#endif
