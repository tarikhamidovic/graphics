#include "clock.hpp"

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
 
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(800, 800);
  
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutCreateWindow("Clock");
  glClearColor(0.1, 0.1, 0.1, 0);

  init();
  glutDisplayFunc(draw_clock);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(special_keys);
  glutMouseFunc(mouse);

  glutTimerFunc(1000, move_hands, 0);

  glutMainLoop();
  
  return 0;
}
