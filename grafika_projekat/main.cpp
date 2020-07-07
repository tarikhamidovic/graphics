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
  glutSpecialFunc(special_keys);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  glutPassiveMotionFunc(passive_mouse_motion);
  glutIdleFunc(idle);
  glutMainLoop();
  return 0;
}
