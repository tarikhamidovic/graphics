#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <GL/glut.h>
#include <ctime>

void draw_frame();  // crtanje okvira
void draw_hands();  // crtanje kazaljki
void draw_clock();  // crtanje sata

void move_hands(int); // pomijeranje kazaljki

void keyboard(unsigned char, int, int); // ASCII karakteri tastature
bool check_range(const float&, const float &);  // provjera opsega
void special_keys(int, int, int); // specijalni karakteri tastature
void mouse(int, int, int, int); // radnja na klik misa

void init();  // postavljanje novog koordinatnog sistema

#endif
