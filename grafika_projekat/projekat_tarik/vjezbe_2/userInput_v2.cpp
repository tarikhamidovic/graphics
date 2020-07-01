#include <GL/glut.h> // Ukljucuje i sve ostale gl* headere
#include <iostream>
#include <math.h>

GLushort patterns[3] = {
    0x0101, /* dotted */
    0x00FF, /* dashed */
    0x1C47  /* dash/dot/dash */
};

int windowWidth = 800;
int windowHeight = 600;

int patternIndex = 0;
GLenum polygonMode = GL_LINE;
GLenum shadingModel = GL_FLAT;

int lineWidth = 1;

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glShadeModel(shadingModel);

  glColor3f(1.0, 1.0, 1.0);
  glEnable(GL_LINE_STIPPLE);
  glLineStipple(2, patterns[patternIndex]);
  glBegin(GL_LINE_LOOP);
  /* previous example coordinates : (0.75,0.75);*/
  glVertex2f(7 / 8.0 * windowWidth, 1 / 8.0 * windowHeight);
  glVertex2f(7 / 8.0 * windowWidth, 7 / 8.0 * windowHeight);
  glVertex2f(1 / 8.0 * windowWidth, 7 / 8.0 * windowHeight);
  glVertex2f(1 / 8.0 * windowWidth, 1 / 8.0 * windowHeight);
  glEnd();
  // glDisable(GL_LINE_STIPPLE);

  glPolygonMode(GL_FRONT_AND_BACK, polygonMode);
  glBegin(GL_POLYGON);
  glColor3f(1.0, 0.0, 1.0);
  /* previous example coordinates : (0.5,0.5);*/
  glVertex2f(3 / 4.0 * windowWidth, 1 / 4.0 * windowHeight);
  glVertex2f(3 / 4.0 * windowWidth, 3 / 4.0 * windowHeight);
  glColor3f(0.0, 0.5, 0.5);
  glVertex2f(1 / 4.0 * windowWidth, 3 / 4.0 * windowHeight);
  glVertex2f(1 / 4.0 * windowWidth, 1 / 4.0 * windowHeight);
  glEnd();
  glFlush();
}

void keyboard(unsigned char key, int x, int y) {
  std::cout << "Keyboard callback" << std::endl;
  int response = 0;
  switch (key) {
  case 27:
    exit(0);
    break;
  case 'n':
  case 'N':
    patternIndex = (patternIndex + 1) % 3;
    break;
  default:
    break;
  }
  glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
  std::cout << "special Keyboard callback" << std::endl;
  int response = 0;
  switch (key) {
  case GLUT_KEY_UP:
    patternIndex = (patternIndex + 1) % 3;
    break;
  default:
    break;
  }
  glutPostRedisplay();
}

void mouseMotion(int x, int y) {
  std::cout << x << " " << y << std::endl;
  polygonMode = (x > 1 / 4.0 * windowWidth && x < 3 / 4.0 * windowWidth &&
                 y < 3 / 4.0 * windowHeight && y > 1 / 4.0 * windowHeight)
                    ? GL_FILL
                    : GL_LINE;
  glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON) {
    std::cout << "mouse callback" << std::endl;
    shadingModel = state == GLUT_DOWN ? GL_SMOOTH : GL_FLAT;
  }
  glutPostRedisplay();
}

void init() {
  /*To do this, we need to tell OpenGL how we want to “project” our picture onto
    the display window because generating a two-dimensional picture is treated
    by OpenGL as a special case of three-dimensional viewing. So, although we
    only want to produce a very simple two-dimensional line, OpenGL processes
    our picture through the full three-dimensional viewing operations. We can
    set the projection type (mode) and other viewing parameters that we need
    with the following two functions:*/
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0, windowWidth, windowHeight, 0);
  /*For now, we
    will use a world-coordinate rectangle with the same aspect ratio as the
    display window*/

  glClearColor(0.0, 0.0, 0.0, 0.0);
  glLineWidth(2.0);
}

void reshape(int width, int height) {
  windowWidth = width;
  windowHeight = height;
  std::cout << "reshape " << windowWidth << " " << windowHeight << std::endl;
  /* trebamo li jos nesto setovati?*/
  // glViewport(0, 0, windowWidth, windowHeight);

  glMatrixMode(GL_PROJECTION);
  /*The glLoadIdentity command is included in the
  reshape function so that any previous values for the projection parameters
  will not affect the new projection settings.*/
  glLoadIdentity();
  gluOrtho2D(0, windowWidth, windowHeight, 0);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowPosition(100, 200);
  glutInitWindowSize(windowWidth, windowHeight);
  glutCreateWindow("User input");
  init();
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(specialKeys);
  glutPassiveMotionFunc(mouseMotion);
  glutMouseFunc(mouse);
  glutMainLoop();
}
