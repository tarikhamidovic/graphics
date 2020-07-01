#include <GL/glut.h>
#include <math.h>
#include <iostream>

static float eye_x = 6.5, eye_y = 0, eye_z = 5;
static float angle_one = 0;
static float angle_two = 10;
static float angle_three = 20;
static float rot_one = 0;
static float rot_two = 120;
static float rot_three = -120;
static float scale_factor = 1.1;
static float delta = 0.002;
static bool rotateAnimation = false;
static bool translateAnimation = false;
static bool scaleAnimation = false;
const float cyan[] = {0, 1, 1};
const float blue[] = {0, 0, 1};
const float pink[] = {1, 0, 1};

void draw_electron(const float& angle, const float& radius)
{
  float x = cos(angle);
  float y = sin(angle);
  glTranslatef(radius*x, radius*y, 0);
  glColor3f(1, 1, 1);
  glutSolidSphere(0.08, 15, 15);
}

void draw_orbit(const float& rotation, const float& radius, const float& angle, const float* orbit_color)
{
  glScalef(scale_factor, scale_factor, scale_factor);
  glRotatef(rotation, 1, 0, 0);
  glColor3fv(orbit_color);
  glutSolidTorus(0.01, radius, 30, 30);
  draw_electron(angle, radius);
}

void draw_core()
{
  glColor3f(1, 0.9, 0);
  glutSolidSphere(0.2, 50, 50);
}

void draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity(); 

  // Postavljamo tacku gledanja
  gluLookAt(eye_x, eye_y, eye_z, 0, 0, 0, 0, 1, 0);

  // Jezgro
  draw_core();

  // Prva orbita
  glPushMatrix();
  draw_orbit(rot_one, 0.75, angle_one, cyan);
  glPopMatrix();

  // Druga orbita
  glPushMatrix();
  draw_orbit(rot_two, 0.85, angle_two, blue);
  glPopMatrix();

  // Treca orbita
  glPushMatrix();
  draw_orbit(rot_three, 0.95, angle_three, pink);
  glPopMatrix();

  glutSwapBuffers();
}

// Pri promjeni velicine prozora oblici ostaju proporcionalni
void reshape(int w, int h)
{
  glViewport(0, 0, (int) w, (int) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(40.0, (float) w / (float) h, 1.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
}

void idle()
{
  if (rotateAnimation) {
    rot_one += 0.5;
    rot_two += 0.5;
    rot_three += 0.5;
  }
  if (translateAnimation) {
    angle_one += 0.005;
    angle_two += 0.005;
    angle_three += 0.005;
  }
  if (scaleAnimation) {
    if (scale_factor >= 1.5 || scale_factor <= 1) delta *= -1;
    scale_factor += delta;
  }
  glutPostRedisplay();
}

void specialKeys(int key, int x, int y)
{
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
      return;
  }
  glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
  switch (button) {
    case GLUT_LEFT_BUTTON:
      if (state == GLUT_DOWN) rotateAnimation = !rotateAnimation;
      break;
    case GLUT_RIGHT_BUTTON:
      if (state == GLUT_DOWN) scaleAnimation = !scaleAnimation;
      break;
    case GLUT_MIDDLE_BUTTON:
      if (state == GLUT_DOWN) translateAnimation = !translateAnimation;
      break;
    default:
      break;
  }
}

void init()
{
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_DEPTH_TEST);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(1000, 1000);
  glutCreateWindow("Program");
  init();
  glutDisplayFunc(draw);
  glutReshapeFunc(reshape);
  glutSpecialFunc(specialKeys);
  glutMouseFunc(mouse);
  glutIdleFunc(idle);
  glutMainLoop();
  return 0;
}
