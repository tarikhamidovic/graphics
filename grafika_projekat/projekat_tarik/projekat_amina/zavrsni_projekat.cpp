#include<GL/glut.h>
#include <thread>         
#include <chrono>  
#include"texture.cpp"
#include"animations.cpp"

void Material1(){
 GLfloat mat_ambient[] = {0.1, 0.1, 0.1, 1.0};
  GLfloat mat_diffuse[] = {1.0, 1.0, 1.0, 1};
  GLfloat mat_specullar[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat mat_shininess[] = {100};

  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specullar);

}



void mainf(){
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0,0,8,0,0,0,0,1,0);
	

	GLUquadricObj *quadric;
	quadric = gluNewQuadric();
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluDeleteQuadric(quadric);

	glRotatef(MoveOnX, 1, 0, 0);  
	glRotatef(MoveOnY, 0, 1, 0);

	//objekat 1 - sredina
	glPushMatrix();
	glScalef(factor,factor,factor);
	glTranslatef(0.0, 0.0, 0.0);
	RedBallTexture();
	gluSphere(quadric, 0.5, 15, 20);
	glPopMatrix();

	//objekat 2 - prvi desno
	glPushMatrix();
	glTranslatef(1.0, 0.0, 0.0);
	if(angle_path) glRotatef(angle,0,1,0);
	else glRotatef(-angle,0,1,0);
	glutWireCube(0.8);
	glPopMatrix();

	//objekat 3 - prvi lijevo
	glPushMatrix();
	glTranslatef(-1.0, 0.0, 0.0);
	if(angle_path) glRotatef(angle,0,1,0);
	else glRotatef(-angle,0,1,0);
	glColor3f(1.0,1.0,1.0);
	glutWireCube(0.8);
	glPopMatrix();

	//objekat 4 - drugi desno
	glPushMatrix();
	glTranslatef(translate_right, translate_right*0.7, 0.0);
	glTranslatef(2.0, 0.0, 0.0);
	BallTexture();
	gluSphere(quadric, 0.5, 15, 20);
	glPopMatrix();

	//objekat 5 - drugi lijevo
	glPushMatrix();
	glTranslatef(translate_left, -translate_left*0.7, 0.0);
	glTranslatef(-2.0, 0.0, 0.0);
	BallTexture();
	gluSphere(quadric, 0.5, 15, 20);
	glPopMatrix();


}

void display(){

	mainf();
	if(material && materialcount%2!=0) Material1();
	glFlush();
	glutSwapBuffers();
}


void idle() {
	scaling();
	translation();
	rotation();
  	display();
}


void init() {
  glColor3f(0.4, 0.0, 1.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-10, 10, -5, 5, -10, 10);
  glMatrixMode(GL_MODELVIEW);
} 

void reshape(GLint w, GLint h) {
	if (h == 0) return;
  	glMatrixMode(GL_PROJECTION);
  	glLoadIdentity();
  	gluPerspective(60.0,(GLdouble)w/(GLdouble)h,0.5,1200.0);
  	glMatrixMode(GL_MODELVIEW);
 	glViewport(0, 0, w, h);
	aspectRatio = (float)w / (float)h;
	display();
}

void mouse(int button, int state, int x, int y){
	
 if(button==GLUT_LEFT_BUTTON) {
 	rotate=true;
 	if(state==GLUT_DOWN) rotate_state=true;
 	else rotate_state=false;
 }
 if(button==GLUT_MIDDLE_BUTTON) {
 	translate=true;
 	if(state==GLUT_DOWN) translate_state=true;
 	else translate_state=false;
 }
 if(button==GLUT_RIGHT_BUTTON) {
 	scale=true;
 	if(state==GLUT_DOWN) scaling_state=true;
 	else scaling_state=false;
	}
 display();
  }


  void motion(int x, int y){

  		if(x>450) angle_path=true;
  		else angle_path=false;
  
  }

void kbd(unsigned char key, int x, int y) {
  switch (key) {
  case 27:
    exit(0);
    break;
   case 'e':
	  glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluLookAt(0.0, 0.0, 1.0, 0.0, -750.0, -1000.0, 0, -5, 4);
      gluPerspective(viewRatio, aspectRatio, 1.0, 30.0);
      glMatrixMode(GL_MODELVIEW);
      display();
    break;
    case 'w':  
      MoveOnX -= 1.0f;
		  break;
	  case 's':  
      MoveOnX += 1.0f;
		  break;
	  case 'a':  
      MoveOnY -= 1.0f;
		  break;
	  case 'd':   
      MoveOnY += 1.0f;
		  break;
	case 'n':
    case 'N':
      glDisable(GL_LIGHTING);
      glDisable(GL_LIGHT0);
      break;
      case 'l':
    case 'L':
      glEnable(GL_LIGHTING);
      glEnable(GL_LIGHT0);
      break;
      case 2:
      material=true;
      materialcount++;
      break;
  }
  glutPostRedisplay();
}


int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(900, 700);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutCreateWindow("Zavrsni projekat");
  init();
  glutDisplayFunc(display);
  glutKeyboardFunc(kbd);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  glutPassiveMotionFunc(motion);
  glutIdleFunc(idle);
  glutMainLoop();
  return 0;
}