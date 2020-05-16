#include <GL/glut.h>

static float eye_x, eye_y, eye_z = 5;
static float moveSphere = 0;
static float moveCoeff = 0.005;
static bool stopAnimation = false;

// Crtanje torusa i sfere
void draw(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity(); 

  // Postavljamo tacku gledanja
  gluLookAt(eye_x, eye_y, eye_z, 0, 0, 0, 0, 1, 0);

  // Crtamo torus
  glColor3f(0, 1, 1);
  glutWireTorus(0.275, 0.85, 15, 30);

  // Crtamo sferu i transliramo je po z-osi
  glColor3f(1, 1, 0);
  glTranslatef(0, 0, moveSphere);
  glutWireSphere(0.4, 15, 15);

  glutSwapBuffers();
}

// Pri promjeni velicine prozora oblici ostaju proporcionalni
void reshape(int w, int h) {
  glViewport(0, 0, (int) w, (int) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(40.0, (float) w / (float) h, 1.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
}

// Funkcija koja implementira pomijeranje sfere
void idle()
{
  if (!stopAnimation) {
    moveSphere += moveCoeff;
    if (moveSphere < -1.5 || moveSphere > 1.5)
      moveCoeff *= -1;
    }
  glutPostRedisplay();
}

// Zaustaviti animaciju pritskom tipke 's' ili 'S'
void keyboard(unsigned char key, int x, int y)
{
  if (key == 's' || key == 'S')
    stopAnimation = !stopAnimation;
}

// Mijenjanje pozicije kamere pomocu navigacijskih tipki
void specialKeys(int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_UP:
      eye_y += 0.1;
      break;
    case GLUT_KEY_DOWN:
      eye_y -= 0.1;
      break;
    case GLUT_KEY_RIGHT:
      eye_x += 0.1;
      break;
    case GLUT_KEY_LEFT:
      eye_x -= 0.1;
      break;
    default:
      break;
  }
  glutPostRedisplay();
}

void init(void) {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Program");
  init();
  glutDisplayFunc(draw);
  glutReshapeFunc(reshape);
  glutSpecialFunc(specialKeys);
  glutKeyboardFunc(keyboard);
  glutIdleFunc(idle);
  glutMainLoop();
  return 0;
}
