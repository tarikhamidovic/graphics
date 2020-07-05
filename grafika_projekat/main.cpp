#include "projekat.hpp"

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(1000, 1000);
  glutCreateWindow("Atom sa zanimljivim teksturama");
  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutSpecialFunc(specialKeys);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  glutPassiveMotionFunc(passiveMouseMotion);
  glutIdleFunc(idle);
  glutMainLoop();
  return 0;
}
