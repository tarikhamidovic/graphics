#include "clock.hpp"

unsigned int seconds;
unsigned int minutes;
unsigned int hours;

float scaling_factor = 1;
float translate_factor_x = 1;
float translate_factor_y = 1;

const float blue[] = {0.0, 0.0, 8.0};
const float green[] = {0.0, 1.0, 0.0};
const float pink[] = {1.0, 0.0, 1.0};
const float aqua[] = {0.0, 1.0, 1.0};

// Crtanje okvira sata.
// Svaka stranica okvira je trapez.
// Svake sekunde boje okvira kruze :)
void draw_frame()
{
  const float *first_color;
  const float *second_color;
  const float *third_color;
  const float *fourth_color;

  if (seconds % 4 == 0) {
    first_color = blue;
    second_color = green;
    third_color = pink;
    fourth_color = aqua;
  }
  else if (seconds % 4 == 1) {
    first_color = aqua;
    second_color = blue;
    third_color = green;
    fourth_color = pink;
  }
  else if (seconds % 4 == 2) {
    first_color = pink;
    second_color = aqua;
    third_color = blue;
    fourth_color = green;
  }
  else {
    first_color = green;
    second_color = pink;
    third_color = aqua;
    fourth_color = blue;
  }

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glPushMatrix();
  
    glScalef(scaling_factor, scaling_factor, 1);
    // gornji trapez 
    glBegin(GL_POLYGON);
    glColor3f(0.1, 0.1, 0.1);
    glVertex2f(-50, 50);
    glVertex2f(50, 50);
    glColor3fv(first_color);
    glVertex2f(45, 45);
    glVertex2f(-45, 45);
    glEnd();
    // desni trapez 
    glBegin(GL_POLYGON);
    glColor3f(0.1, 0.1, 0.1);
    glVertex2f(50, 50);
    glVertex2f(50, -50); 
    glColor3fv(second_color);
    glVertex2f(45, -45);
    glVertex2f(45, 45);
    glEnd();
    // donji trapez 
    glBegin(GL_POLYGON);
    glColor3f(0.1, 0.1, 0.1);
    glVertex2f(50, -50);
    glVertex2f(-50, -50);
    glColor3fv(third_color);
    glVertex2f(-45, -45);
    glVertex2f(45, -45);
    glEnd();
    // lijevi trapez
    glBegin(GL_POLYGON);
    glColor3f(0.1, 0.1, 0.1);
    glVertex2f(-50, -50);
    glVertex2f(-50, 50);
    glColor3fv(fourth_color);
    glVertex2f(-45, 45);
    glVertex2f(-45, -45);
    glEnd();

  glPopMatrix();
}

// Crtanje kazaljki na satu.
void draw_hands()
{
  // Sekunde
  glPushMatrix();
    glRotatef(-(seconds*6.f), 0.0, 0.0, 1.0);
    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(0.0, 0.0);
    glVertex2f(0.0, 43);
    glEnd();
  glPopMatrix();

  // Minute
  glPushMatrix();
    glRotatef(-(minutes*6.f), 0.0, 0.0, 1.0);
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(0.0, 0.0);
    glVertex2f(0.0, 40);
    glEnd();
  glPopMatrix();

  // Sati
  float hourAngle = hours * 30.f + minutes * 0.5f;
  glPushMatrix();
    glRotatef(-hourAngle, 0.0, 0.0, 1.0);
    glLineWidth(4);
    glBegin(GL_LINES);
    glColor3f(5.0, 1.0, 0.2);
    glVertex2f(0.0, 0.0);
    glVertex2f(0.0, 25);
    glEnd();
  glPopMatrix();
}

// Crtanje sata
void draw_clock()
{
  glClear(GL_COLOR_BUFFER_BIT);
  
  glPushMatrix();
    glTranslatef(translate_factor_x, translate_factor_y, 1);
    draw_frame();
    draw_hands();
  glPopMatrix();
  
  glFlush();
}

// Funkcija koja inicijalizira globalne varijable seconds, minutes
// i hours na vrijednosti dobivene od sistemskog vremena.
void move_hands(int n)
{
  time_t currentTime = time(0);
  struct tm *localTime = localtime(&currentTime);
  seconds = localTime -> tm_sec;
  minutes = localTime -> tm_min;
  hours = localTime -> tm_hour;
  glutPostRedisplay();
  glutTimerFunc(1000, move_hands, 0);
}

// Pritiskom na tipku 'R' ili 'r' resetuje se pozicija sata,
// okvira, kao i velicina okvira.
// ESC tipka terminira program.
void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
    case 27:
      exit(0);
      break;
    case 'R':
    case 'r':
      scaling_factor = 1;
      translate_factor_x = 1;
      translate_factor_y = 1;
      glutPostRedisplay();
      break;
    default:
      break;
  }
}

// Vrsi se provjera da li primjenom translacije ili skaliranja 
// okvir izlazi iz opsega.
bool check_range(const float& start_value, const float& translate_factor)
{
  if (start_value * scaling_factor + translate_factor <= 100 && 
      start_value * scaling_factor + translate_factor >= -100)
    return true;

  return false;
}

// Funkcija za specijalne tipke. Omogucava pomijeranje sata i
// okvira pomocu navigacijskih tipki. U slucaju da okvir izlazi
// van granica prozora, translacija se zanemaruje.
void special_keys(int key, int x, int y)
{
  switch (key) {
    case GLUT_KEY_UP:
      translate_factor_y++;
      if (check_range(50.f, translate_factor_y))
        glutPostRedisplay();
      else
        translate_factor_y--;
      break;

    case GLUT_KEY_DOWN:
      translate_factor_y--;
      if (check_range(-50.f, translate_factor_y))
        glutPostRedisplay();
      else
        translate_factor_y++;
      break;

    case GLUT_KEY_LEFT:
      translate_factor_x--;
      if (check_range(-50.f, translate_factor_x))
        glutPostRedisplay();
      else
        translate_factor_x++;
      break;

    case GLUT_KEY_RIGHT:
      translate_factor_x++;
      if (check_range(50.f, translate_factor_x))
        glutPostRedisplay();
      else
        translate_factor_x--;
      break;

    default:
      break;
  }
}

// Na klik lijevog tastera misa povecava se okvir.
void mouse(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON) {
    scaling_factor += 0.02f;
    if (!check_range(50.f, translate_factor_y)) {
      scaling_factor -= 0.02f;
      return;
    }
    if (!check_range(-50.f, translate_factor_y)) {
      scaling_factor -= 0.02f;
      return;
    }
    if (!check_range(50.f, translate_factor_x)) {
      scaling_factor -= 0.02f;
      return;
    }
    if (!check_range(-50.f, translate_factor_x)) {
      scaling_factor -= 0.02f;
      return;
    }
    glutPostRedisplay();
  }
}

// Postavljanje novog koordinatnog sistema
void init()
{
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(-100.f, 100.f, -100.f, 100.f);
  glMatrixMode(GL_MODELVIEW);
}
