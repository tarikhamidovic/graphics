#include "projekat.hpp"

static float eye_x = 6.5, eye_y = 0, eye_z = 5;
static float angle = 0;
static float rotation = 0;
static float scale_factor = 1.1;
static float delta = 0.002;
static float theta = 0.005;
static bool rotate_animation = false;
static bool translate_animation = false;
static bool scale_animation = false;
static bool light_one_on = true;
static bool light_two_on = true;
static bool material_one_on = true;
static bool material_two_on = true;

// Ucitava teksture heksagona
void hex_texture()
{
  static int texture = 0;
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, gimp_image_hex.width, gimp_image_hex.height,
                0, GL_RGBA, GL_UNSIGNED_BYTE, gimp_image_hex.pixel_data);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

// Ucitava teksture leda
void ice_texture()
{
  static int texture = 0;
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, gimp_image_ice.width, gimp_image_ice.height,
                0, GL_RGBA, GL_UNSIGNED_BYTE, gimp_image_ice.pixel_data);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

// Svjetlo kamere 
void camera_light()
{
  GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};
  GLfloat white_light[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat no_light[] = {0, 0, 0, 0};

  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_AMBIENT, white_light);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
  glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
}

// Svjetlo jezgra
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

// Funkcija za crtanje elektrona koja je pozvana u draw_orbit()
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

  GLUquadric *quad = gluNewQuadric();
  ice_texture();
  gluQuadricTexture(quad, 1);
  gluSphere(quad, 0.08, 15, 15);
  glDisable(GL_TEXTURE_2D);
}

// Funkcija koja crta orbitu, kao i elektron, kojem proslijedimo radius i ugao
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

// Funkcija koja crta jezgro atoma
void draw_core()
{
  GLfloat mat_ambient[] = {0.3, 0.3, 0.3, 1.0};
  GLfloat mat_diffuse[] = {0.8, 0.8, 0.8, 1.0};
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

  GLUquadric *quad = gluNewQuadric();
  hex_texture();
  gluQuadricTexture(quad, 1);
  gluSphere(quad, 0.23, 50, 50);
  glDisable(GL_TEXTURE_2D);
}

// Funkcija za crtanje scene
void display()
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

// Omoguci odrzavanje animacija kada niti jedna tipka nije pritisnuta
void idle()
{
  if (rotate_animation) rotation += 0.5;
  if (translate_animation) angle += theta;
  if (scale_animation) {
    if (scale_factor >= 1.5 || scale_factor <= 1) delta *= -1;
    scale_factor += delta;
  }
  glutPostRedisplay();
}

// Funkcija za callback pritiskom na specijalne karaktere tastature.
// Omogucava pomijeranje kamere pomocu navigacijskih tipki.
void special_keys(int key, int x, int y)
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

// Omogucava paljenje/gasenje svjetala i materijala
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

// Funkcija za callback pritiskom tastera misa.
// Lijevi klik pokrece rotaciju, desni skaliranje i srednji translaciju.
void mouse(int button, int state, int x, int y)
{
  switch (button) {
    case GLUT_LEFT_BUTTON:
      if (state == GLUT_DOWN) rotate_animation = !rotate_animation;
      break;
    case GLUT_RIGHT_BUTTON:
      if (state == GLUT_DOWN) scale_animation = !scale_animation;
      break;
    case GLUT_MIDDLE_BUTTON:
      if (state == GLUT_DOWN) translate_animation = !translate_animation;
      break;
    default:
      break;
  }
}

// Promjena smijera kretanja elektrona kada kursor predje polovinu
// ekrana po x osi
void passive_mouse_motion(int x, int y)
{
  if (x < 500 && theta > 0 || x >= 500 && theta < 0) theta *= -1;  
}

// Pri promjeni velicine prozora oblici ostaju proporcionalni
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
  camera_light();
  core_light();
  glClearColor(0.07, 0.07, 0.07, 0.0);
  glShadeModel(GL_SMOOTH);
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_DEPTH_TEST);
}
