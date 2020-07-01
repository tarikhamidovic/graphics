#include <GL/glut.h>

static bool double_click = false;
static bool secondary_light_on = false;

// Crtanje cajnika ciji materijal reaguje na difuznu i spekularnu svjetlost.
// Ambijentalna komponenta = default
void draw_teapot()
{
  GLfloat mat_diffuse_teapot[] = {0.2, 1.0, 0.8, 1.0};
  GLfloat mat_specular_teapot[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat mat_shininess[] = {100.0};

  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_teapot);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_teapot);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

  glLoadIdentity();
  glTranslatef(-3, 0.0, -15.0);
  glutSolidTeapot(1.3);
}

// Crtanje sfere ciji materijal reaguje samo na difuznu svjetlost.
// Ambijentalna komponenta = default
void draw_sphere()
{ 
  GLfloat mat_diffuse_sphere[] = {1.0, 1.0, 0.0, 1.0};
  GLfloat mat_specular_sphere[] = {0.0, 0.0, 0.0, 1.0};
  
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_sphere);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_sphere);

  glLoadIdentity();
  glTranslatef(3, 0.0, -15.0);
  glutSolidSphere(1.5, 20, 16);
}

// Postavljanje primarnog svjetla
void primary_light()
{
  GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};
  GLfloat white_light[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat no_light[] = {0, 0, 0, 0};

  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
  glLightfv(GL_LIGHT0, GL_SPECULAR, no_light);
}

// Postavljanje sekundarnog svjetla
void secondary_light()
{
  GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};
  GLfloat white_light[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat no_light[] = {0, 0, 0, 0};

  glLightfv(GL_LIGHT1, GL_POSITION, light_position);
  glLightfv(GL_LIGHT1, GL_SPECULAR, white_light);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, no_light);
}

// Primarno svjetlo se ukljucuje, sekundarno ostaje ugaseno
void init()
{
  primary_light();
  secondary_light();
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);
}

// Crtanje scene
void display()
{
  glMatrixMode(GL_MODELVIEW);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  draw_teapot();
  draw_sphere(); 
  glFlush();
}

// Oblici ostaju proporcionalni pri promjeni velicine prozora
void reshape(int w, int h)
{
  glViewport(0, 0, (GLint)w, (GLint)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(30, (GLfloat)w/h, 5, 15);
}

// Na klik lijevog tastera misa palimo/gasimo sekundarno svjetlo
void mouse(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON) {
    double_click = !double_click;
    if (double_click) {
      secondary_light_on = !secondary_light_on;
      secondary_light_on ? glEnable(GL_LIGHT1) : glDisable(GL_LIGHT1);
      glutPostRedisplay();
    }
  }
}

// Pritiskom na tipku ESC terminiramo program
void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
    case 27:
      exit(0);
      break;
    default:
      break;
  }
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(1000, 700);
  glutCreateWindow("Zadaca 3");
  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  glutMainLoop();
  return 0;
}
