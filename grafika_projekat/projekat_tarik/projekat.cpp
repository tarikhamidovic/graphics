#include <GL/glut.h>
#include <math.h>

static float eye_x = 6.5, eye_y = 0, eye_z = 5;
static float angle = 0;
static float rotation = 0;
static float scale_factor = 1.1;
static float delta = 0.002;
static float theta = 0.005;
static bool rotate_animation = false;
static bool translate_animation = false;
static bool scaleAnimation = false;
static bool light_one_on = true;
static bool light_two_on = true;
static bool material_one_on = true;
static bool material_two_on = true;

void ambient_light()
{
  GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};
  GLfloat white_light[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat no_light[] = {0, 0, 0, 0};

  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_AMBIENT, white_light);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
  glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
}

void core_light()
{
  GLfloat light_position[] = {0.0, 0.0, 0.0, 0.1};
  GLfloat white_light[] = {1.0, 1.0, 0.6, 1.0};
  GLfloat no_light[] = {0, 0, 0, 0};

  glLightfv(GL_LIGHT1, GL_POSITION, light_position);
  glLightfv(GL_LIGHT1, GL_AMBIENT, white_light);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, white_light);
  glLightfv(GL_LIGHT1, GL_SPECULAR, no_light);
}

void draw_electron(const float& angle, const float& radius)
{
  GLfloat mat_ambient[] = {0.2, 0.2, 0.2, 1.0};
  GLfloat mat_diffuse[] = {0.6, 0.6, 0.6, 1.0};
  GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat mat_shininess[] = {100.0};

  if (!material_two_on) {
    mat_ambient[0] = mat_diffuse[0] = mat_specular[0] = mat_shininess[0] = 0.0;
    mat_ambient[1] = mat_diffuse[1] = mat_specular[1] = 0.0;
    mat_ambient[2] = mat_diffuse[2] = mat_specular[2] = 0.0;
  }

  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

  float x = cos(angle);
  float y = sin(angle);
  glTranslatef(radius*x, radius*y, 0);
  glutSolidSphere(0.08, 15, 15);
}

void draw_orbit(const float& rotation, const float& radius, const float& angle)
{
  GLfloat mat_ambient[] = {0.0, 0.0, 0.1, 1.0};
  GLfloat mat_diffuse[] = {0.0, 0.0, 0.3, 1.0};
  GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat mat_shininess[] = {100.0};

  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

  glScalef(scale_factor, scale_factor, scale_factor);
  glRotatef(rotation, 1, 0, 0);
  glutSolidTorus(0.01, radius, 30, 30);
  draw_electron(angle, radius);
}

void draw_core()
{
  GLfloat mat_ambient[] = {0.3, 0.1, 0.0, 1.0};
  GLfloat mat_diffuse[] = {0.8, 0.8, 0.0, 1.0};
  GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat mat_shininess[] = {100.0};

  if (!material_one_on) {
    mat_ambient[0] = mat_diffuse[0] = mat_specular[0] = mat_shininess[0] = 0.0;
    mat_ambient[1] = mat_diffuse[1] = mat_specular[1] = 0.0;
    mat_ambient[2] = mat_diffuse[2] = mat_specular[2] = 0.0;
  }

  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

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
  draw_orbit(rotation, 0.75, angle);
  glPopMatrix();

  // Druga orbita
  glPushMatrix();
  draw_orbit(rotation + 120, 0.85, angle + 10);
  glPopMatrix();

  // Treca orbita
  glPushMatrix();
  draw_orbit(rotation - 120, 0.95, angle + 20);
  glPopMatrix();

  glutSwapBuffers();
}

void idle()
{
  if (rotate_animation) rotation += 0.5;
  if (translate_animation) angle += theta;
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

void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
    case 27:
      exit(0);
      break;
    case '0':
      light_one_on ? glDisable(GL_LIGHT0) : glEnable(GL_LIGHT0);
      light_one_on = !light_one_on;
      break;
    case '1':
      light_two_on ? glDisable(GL_LIGHT1) : glEnable(GL_LIGHT1);
      light_two_on = !light_two_on;
      break;
    case '2':
      material_one_on = !material_one_on;
      break;
    case '3':
      material_two_on = !material_two_on;
      break;
    default:
      break;
  }
  glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
  switch (button) {
    case GLUT_LEFT_BUTTON:
      if (state == GLUT_DOWN) rotate_animation = !rotate_animation;
      break;
    case GLUT_RIGHT_BUTTON:
      if (state == GLUT_DOWN) scaleAnimation = !scaleAnimation;
      break;
    case GLUT_MIDDLE_BUTTON:
      if (state == GLUT_DOWN) translate_animation = !translate_animation;
      break;
    default:
      break;
  }
}

void passiveMouseMotion(int x, int y)
{
  if (x < 500 && theta > 0 || x >= 500 && theta < 0) theta *= -1;  
}

void reshape(int w, int h)
{
  glViewport(0, 0, (int) w, (int) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(25.0, (float) w / (float) h, 1.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
}

void init()
{
  ambient_light();
  core_light();
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_SMOOTH);
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
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
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  glutPassiveMotionFunc(passiveMouseMotion);
  glutIdleFunc(idle);
  glutMainLoop();
  return 0;
}
