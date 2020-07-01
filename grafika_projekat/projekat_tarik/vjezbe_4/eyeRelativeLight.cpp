#include <GL/glut.h>

static GLdouble ex, ey, ez=5;

void placeLight(){
GLfloat light_position[] = { 0.0, 0.0, 1.0, 1.0 };
glLightfv(GL_LIGHT0, GL_POSITION, light_position);
glEnable(GL_LIGHT0);
}

void init(void) {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST);
}

void display(void)
{
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glPushMatrix();
gluLookAt(ex, ey, ez, 0.0, 0.0, 0.0, 0, 1, 0);
glutSolidTorus(0.275, 0.85, 8, 15);
glPopMatrix();
glFlush();
}

void reshape(int w, int h) {
GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };
glViewport(0, 0, (GLint) w, (GLint) h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(40.0, (GLfloat) w/(GLfloat) h, 1.0, 100.0);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
placeLight();
}

void specialKeys(int key, int x, int y) {
  int response = 0;
  switch (key) {
  case GLUT_KEY_UP:
    ey += 0.1;
    break;
  case GLUT_KEY_DOWN:
    ey -= 0.1;
    break;
  case GLUT_KEY_RIGHT:
    ex += 0.1;
    break;
  case GLUT_KEY_LEFT:
    ex -= 0.1;
    break;
  default:
    break;
  }
  glutPostRedisplay();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  glutCreateWindow(argv[0]);
  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutSpecialFunc(specialKeys);
  glutMainLoop();
  return 0;
}
