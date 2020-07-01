#include <GL/glut.h>
#include <iostream>

void init (void)
{
  /* Set color of display window to white. */
  glClearColor (1.0, 1.0, 1.0, 0.0);
  /* Set parameters for world-coordinate clipping window. */
  glMatrixMode (GL_PROJECTION);
  gluOrtho2D (-100.0, 100.0, -100.0, 100.0);
  glMatrixMode (GL_MODELVIEW);
}

void drawTriangle ()
{
  glBegin (GL_TRIANGLES);
  glVertex2f(-50.0, 25.0);
  glVertex2f(50.0, -25.0);
  glVertex2f(-50.0, -75.0);
  glEnd ();
}

void displayFcn (void)
{
  glClear (GL_COLOR_BUFFER_BIT); // Clear display window.
  glColor3f (0.0, 0.0, 1.0); // Set fill color to blue.
  glViewport (0, 0, 300, 300); // Set left viewport.
  drawTriangle ();
  /* display in right half of display window. */
  glColor3f (1.0, 0.0, 0.0); // Set fill color to red.
  glViewport (300, 0, 300, 300); // Set right viewport.
  drawTriangle (); 
  glFlush ( );
}



int main (int argc, char ** argv)
{
  glutInit (&argc, argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition (50, 50);
  glutInitWindowSize (600, 300);
  glutCreateWindow ("Split-Screen Example");
  init ( );
  glutDisplayFunc (displayFcn);
  glutMainLoop ( );
  return 0;
}
