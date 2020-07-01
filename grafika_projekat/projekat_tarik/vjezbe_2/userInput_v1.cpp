#include <GL/glut.h> // Ukljucuje i sve ostale gl* headere
#include <iostream>
#include <math.h>

GLushort patterns[3] = {
    0x0101, /* dotted */
    0x00FF, /* dashed */
    0x1C47  /* dash/dot/dash */
};

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
  glVertex2f(0.75, 0.75);
  glVertex2f(0.75, -0.75);
  glVertex2f(-0.75, -0.75);
  glVertex2f(-0.75, 0.75);
  glEnd();

  // glDisable(GL_LINE_STIPPLE);

  glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

  glBegin(GL_POLYGON);
  glColor3f(1.0, 0.0, 1.0);
  glVertex2f(0.5, 0.5);
  glVertex2f(0.5, -0.5);
  glColor3f(0.0, 0.5, 0.5);
  glVertex2f(-0.5, -0.5);
  glVertex2f(-0.5, 0.5);
  glEnd();

  glFlush();
}

void keyboard(unsigned char key, int x, int y) {
  std::cout << "Keyboard callback" << std::endl;
  switch (key) {
  case 27:
    exit(0);
    break;
  case 'n':
  case 'N':
    patternIndex = (patternIndex + 1) % 3;
    glutPostRedisplay();
    break;
  default:
    break;
  }
  /* Da li mozemo optimizirati ovu funkciju?*/
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

void motion(int x, int y){
std::cout << "MOTION: " << x << " " << y << std::endl;
}

/* x and y are display coordinates, we need to translate them back to
 * our [-1,1] coordinate space */
void passiveMotion(int x, int y) {
  std::cout <<"PASSIVE MOTION: " <<  x << " " << y << std::endl;
  float windowWidth = glutGet(GLUT_WINDOW_WIDTH);
  float windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

  /*convert to [-1,1] range*/
  float xCoordinate = x / (windowWidth / 2) - 1;
  float yCoordinate = -(y / (windowHeight / 2) - 1);
  std::cout << xCoordinate << " " << yCoordinate << std::endl;
  polygonMode = (xCoordinate > -0.5 && xCoordinate < 0.5 && yCoordinate < 0.5 &&
                 yCoordinate > -0.5)
                    ? GL_FILL
                    : GL_LINE;
  glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
  std::cout << "MOUSE: " << x << " " << y << std::endl;
  if (button == GLUT_LEFT_BUTTON) {
    shadingModel = state == GLUT_DOWN ? GL_SMOOTH : GL_FLAT;
  }
  glutPostRedisplay();
}

void init() {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glLineWidth(2.0);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowPosition(100, 200);
  glutInitWindowSize(800, 600);
  glutCreateWindow("User input");
  init();

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(specialKeys);
  glutPassiveMotionFunc(passiveMotion);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);

  glutMainLoop();
}
